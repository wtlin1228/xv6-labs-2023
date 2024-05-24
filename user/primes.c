#include "kernel/types.h"
#include "user/user.h"

void prime_block(int fd)
{
  int prime;
  if (read(fd, &prime, sizeof(int)) == 0) {
    return;
  }
  printf("prime %d\n", prime);

  int p[2];
  pipe(p);
  if (fork() > 0)
  {
    close(p[0]);
    int n;
    while (read(fd, &n, sizeof(int)) != 0)
    {
      if (n % prime != 0)
      {
        write(p[1], &n, sizeof(int));
      }
    }
    close(p[1]);
    wait(0);
  }
  else
  {
    close(p[1]);
    prime_block(p[0]);
    close(p[0]);
    exit(0);
  }
}


int main(int argc, char *argv[])
{
  int p[2];
  pipe(p);

  if (fork() > 0)
  {
    close(p[0]);
    // write 2..=35 to pipe
    for (int i = 2; i <= 35; ++i)
    {
      write(p[1], &i, sizeof(int));
    }
    close(p[1]);
    wait(0);
    exit(0);
  }
  else
  {
    close(p[1]);
    prime_block(p[0]);
    close(p[0]);
    exit(0);
  }
}

