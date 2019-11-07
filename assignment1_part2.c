#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

/*
Program for practicing InterProcess Communications.
Accomplishes following objectives:
    a) Parent reads X from user (commandline arguments)
    b) Child reads Y from user (commandline arguments)
    c) A pipe is created for communication between Parent and Child
    d) Child writes Y into the pipe
    e) Parent reads Y from the pipe
    f) Parent adding two variables X+Y
*/

int main (int argc, char *argv[])
{
  int fd[2];
  pid_t pid;
  char* Y;
  char* X;




  if (pipe(fd) < 0){ // c) A pipe is created for communication between Parent and Child
    perror("pipe error");
    exit(-1);
  } else {
    printf("A pipe is created for communication between parent (PID %d) and child\n", getpid());
  }

  pid = fork();

  if (pid < 0) {
    perror("Fork error");
    exit(-1);
  } else if (pid > 0) //parent
  {
    printf("parent (PID %d) created a child(PID %d)\n", getpid(), pid);

    X = argv[1]; // a) Parent reads X from user
    printf("parent (PID %d) Reading X = %s from the user\n", getpid(), X);

    wait(NULL);

    read(fd[0], &Y, sizeof(Y)); // e) Parent reads Y from the pipe
    printf("Reading Y from the pipe (Y = %s)\n", Y);

    //TODO add large number handling if Reco says it's necessary

    //will overflow if X and Y are too large
    printf("parent (PID %d) adding X + Y = %d\n", getpid(), atoi(X) + atoi(Y)); // f) Parent adding two variables

  } else //child
  {
    Y = argv[2]; // b) Child reads Y from user
    printf("child (PID %d) Reading Y = %s from the user\n", getpid(), Y);


    printf("child (PID %d) Writing Y into the pipe\n", getpid());
    write(fd[1], &Y, sizeof(Y)); // d) Child writes Y into the pipe
  }
  return 0;
}
