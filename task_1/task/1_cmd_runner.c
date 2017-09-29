/*
  Write a program which allow you to: 
- run another programs via command line.
- get exit codes of terminated programs

## TIPS:
1. Use "2_fork_wait_exit.c" and "4_exec_dir.c" from examples. Combine them.
2. Parse input string according to the type of exec* (see "man exec").
   a) if execvp is used, string splitting into "path" and "args" is all you need.
3. Collect exit codes via waitpid/WEXITSTATUS.
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char* program, char** arg_list)
{
 pid_t child;
 child = fork();//создание копии текущего процесса
 if(child!=0) return child;//это родитель
 else execvp(program, arg_list);
 fprintf(stderr,"error");
abort();
}

int main ()
{
 char* arg_list[] = {"ls", "-l", "/", NULL};
 spawn ("ls", arg_list);
 printf ("done\n");
 return 0;
}

