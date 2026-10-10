#include "kernel/types.h"
#include "user/user.h"

int
main(void)
{
  printf("initial priority: %d\n", getpriority());
  printf("setpriority(10) -> %d\n", setpriority(10));
  printf("priority now: %d\n", getpriority());
  printf("setpriority(60) -> %d (should be -1)\n", setpriority(60));
  printf("setpriority(-1) -> %d (should be -1)\n", setpriority(-1));
  printf("priority still: %d\n", getpriority());

  if(fork() == 0){
    printf("child inherited priority: %d\n", getpriority());
    exit(0);
  }
  wait(0);
  exit(0);
}
