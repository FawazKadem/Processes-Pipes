#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/*
Program for working with Parent/Child processes and demonstrating fork(), execl(), wait() commands.
Program accomplishes following objectives:
  a) A Parent process will create two Child processes
  b) Child_1 will create its own child Child_1.1
  c) Parent will wait for Child_1 to complete before creating Child_2
  d) Child_2 will make a system call to external_program.out
*/

int main()
{
    pid_t pid;

    pid = fork(); //a) - part 1: parent creates first child process

    if (pid<0)
    {
      perror("Fork unsuccessful");
      exit(-1);
    }

    if (pid>0)
    {
      printf("parent process (PID %d) created child_1 (PID %d)\n", getpid(), pid);
      wait(NULL); //c) Parent will wait for Child 1 to complete before creating Child_2
      printf("child_1 (%d) is now completed\n", pid);
      pid_t pid2 = fork(); //a) - part 2: parent creates second bhild process

      if (pid2 > 0) {
        printf("parent (PID %d) created child_2 (PID %d)\n", getpid(), pid2);
      }

      if (pid2==0) //child 2. first call > 0 (parent), nested call = 0.
      {
        printf("child_2 (PID %d) is calling an external program external_program.out and leaving child_2\n", getpid());
        execl("external_program.out","external_program.out", NULL);
      }


    } else
    {
      printf("parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", getppid(), getpid());
      pid_t pid1_1 = fork(); //b) child_1 will create its own child_1.1 process


      if (pid1_1>0) {
        printf("child_1 (PID %d) created child_1.1 (PID %d)\n", getpid(), pid1_1);
      }


    }
return 0;

}
