#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int p1[2];
  pipe(p1);

  int p2[2];
  pipe(p2);

  int pid = fork();
  if (pid > 0)
  {
    // parent process will ping child process by p1[1]
    // then wait for a pong from child process by p2[0]

    close(p1[0]); // close the read side of p1
    close(p2[1]); // close the write side of p2

    write(p1[1], "ping", 1);
    char c;
    read(p2[0], &c, 1);
    printf("%d: received pong\n", getpid());

    close(p1[1]);
    close(p2[0]);
  }
  else if (pid == 0)
  {
    // child process will wait for a ping from parent process by p1[0]
    // then response with a pong by p2[1]

    close(p1[1]); // close the write side of p1
    close(p2[0]); // close the read side of p2

    char c;
    read(p1[0], &c, 1);
    printf("%d: received ping\n", getpid());
    write(p2[1], "pong", 1);

    close(p1[0]);
    close(p2[1]);
  }
  else
  {
    printf("fork error\n");
  }

  exit(0);
}
