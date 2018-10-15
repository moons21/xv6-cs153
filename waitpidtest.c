#include "param.h" 
#include "types.h" 
#include "stat.h" 
#include "user.h" 
#include "fs.h" 
#include "fcntl.h" 
#include "syscall.h" 
#include "traps.h" 
#include "memlayout.h"

int stdout = 1;

int main(void){
   // int i = 0;
    int status;
    /*
    int status2 = -22;

    //execvp stuff
    char* args[4];
    args[0] = "echo";
    args[1] = "This is one giant string";
    args[2] = NULL;
    */

    int pid = fork();  
    
    if (pid == 0){
        printf(stdout, "Child 1 pid: %d\n", (int)getpid());
        //printf("I'm the child, my PID is: %d\n", (int)getpid());
        //printf("Value of int pid: %d \n", pid);
        //printf("sleeping for 5 secs\n");
        sleep(10);
        printf(stdout, "Child 1 done\n");
        /*if (execvp(args[0],args) == -1){
            perror("exec");
            exit(420);
            }
	*/
	exit(420);
	}
    else{
	/*
        int pid2 = fork();
        if (pid2 == 0){
            sleep(1);
            for(i = 0; i < 20; i += 1){	// prints a straight line for clarity when printing
               printf(stdout, "-");
            }
            printf(stdout, "\n");
            printf(stdout, "Child 2, my PID is: %d\n", (int)getpid());
            for(i = 0; i < 20; i += 1){	// prints a straight line for clarity when printing
               printf(stdout, "-");
            }
            printf(stdout, "\n");
        }	 
        else{
            waitpid(pid2, &status, 0);    // choose which child to wait for
            printf(stdout, "I'm the parent, my PID is: %d\n", (int)getpid());            
            printf(stdout, "Parent exiting...\n");
        }
	*/
        printf(stdout, "I'm the parent, my PID is: %d\n", (int)getpid());            
        //waitpid(pid, &status, 0);	
        wait(&status);
	printf(stdout, "Exit status of child: %d\n", status);
        printf(stdout, "Parent exiting...\n");
    }
    exit(0);
}
