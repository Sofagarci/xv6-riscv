#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  static struct pstat uproc[NPROC];
  int nprocs;
  int i;
  char *state;
  uint now;
  uint age;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  nprocs = getprocs(uproc);
  now = uptime(); 	//added task3
  if (nprocs < 0)
    exit(-1);

  printf("pid\tstate\t\tsize\tage\tppid\tname\tpriority\n");		//added priority(task2), age(task3),  
  for (i=0; i<nprocs; i++) {
    state = states[uproc[i].state];	//added for task 3
    age = (uproc[i].state == RUNNABLE) ? now - uproc[i].readytime : 0;		//added for task 3
    printf("%d\t%s\t%d\t%d\t%d\t%s\t%d\n", uproc[i].pid, state,
           (int)uproc[i].size, (int)age, uproc[i].ppid, uproc[i].name,
           uproc[i].priority);		//added priority for header (task2), age(task3)
  }

  exit(0);
}
