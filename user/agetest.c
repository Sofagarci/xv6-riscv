#include "kernel/types.h"
#include "user/user.h"

// usage: agetest [work]
// One CPU hog (priority 45) and two low-priority jobs (priority 0) do the
// same amount of work. Reports each job's response and turnaround time.
int
main(int argc, char *argv[])
{
  int prios[] = {45, 0, 0};
  int n = 3;
  int work = 2000;
  int fds[2];
  int start, i;
  int rec[3];
  int sumresp = 0, sumturn = 0;

  if(argc > 1)
    work = atoi(argv[1]);

  pipe(fds);
  setpriority(49);   // parent forks everything before any child runs
  start = uptime();
  for(i = 0; i < n; i++){
    if(fork() == 0){
      volatile int x = 0;
      long k;
      int resp;
      setpriority(prios[i]);
      pause(1);                 // go back through the scheduler at our real priority
      resp = uptime() - start;  // response time: first run at our real priority
      for(k = 0; k < work * 1000000L; k++)
        x++;
      rec[0] = prios[i];
      rec[1] = resp;
      rec[2] = uptime() - start;  // turnaround time
      write(fds[1], rec, sizeof(rec));
      exit(0);
    }
  }
  for(i = 0; i < n; i++)
    wait(0);
  for(i = 0; i < n; i++){
    read(fds[0], rec, sizeof(rec));
    printf("prio %d: response %d ticks, turnaround %d ticks\n",
           rec[0], rec[1], rec[2]);
    sumresp += rec[1];
    sumturn += rec[2];
  }
  printf("average response %d, average turnaround %d\n",
         sumresp / n, sumturn / n);
  exit(0);
}

