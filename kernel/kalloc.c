// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

struct kmem {
  struct spinlock lock;
  struct run *freelist;
};

struct kmem kmems[NCPU];

void
kinit()
{
  struct kmem *kmemp;
  for(kmemp = kmems; kmemp < kmems+NCPU; kmemp++){
    initlock(&kmemp->lock, "kmem");
  }
  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
  p = (char*)PGROUNDUP((uint64)pa_start);
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
}

// Free the page of physical memory pointed at by pa,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  // pa could be borrowed by another CPU, so kfree returns this page to 
  // its original CPU instead of the current CPU.
  acquire(&kmems[((uint64)pa / PGSIZE) % NCPU].lock);
  r->next = kmems[((uint64)pa / PGSIZE) % NCPU].freelist;
  kmems[((uint64)pa / PGSIZE) % NCPU].freelist = r;
  release(&kmems[((uint64)pa / PGSIZE) % NCPU].lock);
}

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;
  int i;

  push_off();
  int hart = cpuid();
  pop_off();
  
  for(i = 0; i < NCPU; i++){
    acquire(&kmems[(hart + i) % NCPU].lock);
    r = kmems[(hart + i) % NCPU].freelist;
    if(r)
      kmems[(hart + i) % NCPU].freelist = r->next;
    release(&kmems[(hart + i) % NCPU].lock);
    if(r)
      break;
  }

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}
