#include "kernel/types.h"
#include "user/user.h"

// usage: schedtest [work]
// Forks 4 children with different priorities. Each does the same CPU-bound
// work and reports the tick at which it finished.
int
main(int argc, char *argv[])
{
  int prios[] = {10, 40, 20, 30};
  int n = 4;
  int work = 50;
  int start, i;

  if(argc > 1)
    work = atoi(argv[1]);

  setpriority(49);   // so the parent can finish forking before children run
  start = uptime();
  for(i = 0; i < n; i++){
    if(fork() == 0){
      volatile int x = 0;
      long k;
      setpriority(prios[i]);
      for(k = 0; k < work * 1000000L; k++)
        x++;
      printf("prio %d finished at tick %d (started at %d)\n",
             prios[i], uptime(), start);
      exit(0);
    }
  }
  for(i = 0; i < n; i++)
    wait(0);
  exit(0);
}
