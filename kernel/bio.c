// Buffer cache.
//
// The buffer cache is a linked list of buf structures holding
// cached copies of disk block contents.  Caching disk blocks
// in memory reduces the number of disk reads and also provides
// a synchronization point for disk blocks used by multiple processes.
//
// Interface:
// * To get a buffer for a particular disk block, call bread.
// * After changing buffer data, call bwrite to write it to disk.
// * When done with the buffer, call brelse.
// * Do not use the buffer after calling brelse.
// * Only one process at a time can use a buffer,
//     so do not keep them longer than necessary.


#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "riscv.h"
#include "defs.h"
#include "fs.h"
#include "buf.h"

struct bucket {
  struct spinlock lock;
  struct buf head;
};

struct {
  struct spinlock lock;
  struct buf buf[NBUF];

  struct bucket buckets[NBUCKET];
} bcache;

void
binit(void)
{
  struct buf *b;
  struct bucket *bucket;

  initlock(&bcache.lock, "bcache");

  for(bucket = bcache.buckets; bucket < bcache.buckets+NBUCKET; bucket++){
    initlock(&bucket->lock, "bcache.bucket");
    bucket->head.prev = &bucket->head;
    bucket->head.next = &bucket->head;
  }

  // Put all buffers into bucket#0.
  for(b = bcache.buf; b < bcache.buf+NBUF; b++){
    b->next = bcache.buckets[0].head.next;
    b->prev = &bcache.buckets[0].head;
    initsleeplock(&b->lock, "buffer");
    bcache.buckets[0].head.next->prev = b;
    bcache.buckets[0].head.next = b;
  }
}

// Look through buffer cache for block on device dev.
// If not found, allocate a buffer.
// In either case, return locked buffer.
static struct buf*
bget(uint dev, uint blockno)
{
  struct buf *b, *empty_b;
  struct bucket *target_bucket, *other_bucket;
  int i, bucket_idx;

  bucket_idx = blockno % NBUCKET;
  target_bucket = &bcache.buckets[bucket_idx];

  acquire(&target_bucket->lock);

  // Is the block already cached in the target bucket?
  empty_b = 0;
  for(b = target_bucket->head.next; b != &target_bucket->head; b = b->next){
    if(b->dev == dev && b->blockno == blockno){
      b->refcnt++;
      release(&target_bucket->lock);
      acquiresleep(&b->lock);
      return b;
    }
    if(empty_b == 0 && b->refcnt == 0){ // Remember empty slot.
      empty_b = b;
    }
  }
  // Reuse the empty slot in the target bucket.
  if(empty_b != 0){
    empty_b->dev = dev;
    empty_b->blockno = blockno;
    empty_b->valid = 0;
    empty_b->refcnt = 1;
    release(&target_bucket->lock);
    acquiresleep(&empty_b->lock);
    return empty_b;
  }

  for(i = 1; i < NBUCKET; i++){
    other_bucket = &bcache.buckets[(blockno + i) % NBUCKET];
    
    acquire(&other_bucket->lock);

    for(b = other_bucket->head.next; b != &other_bucket->head; b = b->next){
      if(b->refcnt == 0){
        b->dev = dev;
        b->blockno = blockno;
        b->valid = 0;
        b->refcnt = 1;

        // Remove buffer from other bucket.
        b->next->prev = b->prev;
        b->prev->next = b->next;

        // Insert buffer into target bucket.
        b->next = target_bucket->head.next;
        b->prev = &target_bucket->head;
        target_bucket->head.next->prev = b;
        target_bucket->head.next = b;

        release(&other_bucket->lock);
        release(&target_bucket->lock);
        acquiresleep(&b->lock);
        return b;
      }
    }

    release(&other_bucket->lock);
  }

  release(&target_bucket->lock);

  panic("bget: no buffers");
}

// Return a locked buf with the contents of the indicated block.
struct buf*
bread(uint dev, uint blockno)
{
  struct buf *b;

  b = bget(dev, blockno);
  if(!b->valid) {
    virtio_disk_rw(b, 0);
    b->valid = 1;
  }
  return b;
}

// Write b's contents to disk.  Must be locked.
void
bwrite(struct buf *b)
{
  if(!holdingsleep(&b->lock))
    panic("bwrite");
  virtio_disk_rw(b, 1);
}

// Release a locked buffer.
// Move to the head of the most-recently-used list.
void
brelse(struct buf *b)
{
  int bucket_idx = b->blockno % NBUCKET;
  
  if(!holdingsleep(&b->lock))
    panic("brelse");

  releasesleep(&b->lock);

  acquire(&bcache.buckets[bucket_idx].lock);
  b->refcnt--;
  release(&bcache.buckets[bucket_idx].lock);
}

void
bpin(struct buf *b) {
  int bucket_idx = b->blockno % NBUCKET;
  acquire(&bcache.buckets[bucket_idx].lock);
  b->refcnt++;
  release(&bcache.buckets[bucket_idx].lock);
}

void
bunpin(struct buf *b) {
  int bucket_idx = b->blockno % NBUCKET;
  acquire(&bcache.buckets[bucket_idx].lock);
  b->refcnt--;
  release(&bcache.buckets[bucket_idx].lock);
}


