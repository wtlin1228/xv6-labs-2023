#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  int n;

  if (argc <= 1)
  {
    fprintf(2, "sleep expects an argument\n");
    exit(1);
  }

  n = atoi(argv[1]);
  if (n < 0)
  {
    n = 0;
  }
  sleep(n);
  exit(0);
}
