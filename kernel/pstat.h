#ifndef _PSTAT_H_
#define _PSTAT_H_
//from pa1
struct rusage{
uint cputime;
};

//pa2
enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };

struct pstat {
  int pid;              // Process ID
  enum procstate state; // Process state
  uint64 size;          // Size of process memory (bytes)
  int ppid;             // Parent process ID
  char name[16];        // Command name
  int priority;		// added task 2 priority
};

#endif
