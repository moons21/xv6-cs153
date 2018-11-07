#include "types.h"
#include "user.h"

int main(int argc, char *argv[])
{
	
	int exitWait(void);
	int waitPid(void);
	int PScheduler(void);
        int starvation(void);
	int testTime(int);

  printf(1, "\n This program tests the correctness of your lab#1\n");
  if (atoi(argv[1]) == 1)
	exitWait();
  else if (atoi(argv[1]) == 2)
	waitPid();
  else if (atoi(argv[1]) == 3)
	PScheduler();
  else if (atoi(argv[1]) == 4)
	starvation();
  else if (atoi(argv[1]) == 5)
        testTime(atoi(argv[2]));
  else if (atoi(argv[1]) == 33){
	printf(1, "Testing why setpriority is breaking: \n");
	setpriority(555); // used to test why itsbreaking :/
	printf(1, "Congrats, it didnt break \n");
  }
  else 
   printf(1, "\ntype \"lab1 1\" to test exit and wait, \"lab1 2\" to test waitpid and \"lab1 3\" to test the priority scheduler \n");
  
    // End of test
	 exit(0);
 }
  
  
int exitWait(void) {
	  int pid, ret_pid, exit_status;
       int i;
  // use this part to test exit(int status) and wait(int* status)
 
  printf(1, "\n  Step 1: testing exit(int status) and wait(int* status):\n");

  for (i = 0; i < 2; i++) {
    pid = fork();
    if (pid == 0) { // only the child executed this code
      if (i == 0)
      {
      printf(1, "\nThis is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);
  }
      else
      {
	 printf(1, "\nThis is child with PID# %d and I will exit with status %d\n" ,getpid(), -1);
      exit(-1);
  } 
    } else if (pid > 0) { // only the parent exeecutes this code
      ret_pid = wait(&exit_status);
      printf(1, "\n This is the parent: child with PID# %d has exited with status %d\n", ret_pid, exit_status);
    } else  // something went wrong with fork system call
    {  
	  printf(2, "\nError using fork\n");
      exit(-1);
    }
  }
  return 0;
}

int waitPid(void){
	
  int ret_pid, exit_status;
  int i;
  int pid_a[5]={0, 0, 0, 0, 0};
 // use this part to test wait(int pid, int* status, int options)

 printf(1, "\n  Step 2: testing waitpid(int pid, int* status, int options):\n");

  for (i = 0; i <5; i++) {
    pid_a[i] = fork();
	
    if (pid_a[i] == 0) { // only the child executed this code
     
      
      printf(1, "\n The is child with PID# %d and I will exit with status %d\n", getpid(), 0);
      exit(0);}}
       
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[3]);
      ret_pid = waitpid(pid_a[3], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[1]);
      ret_pid = waitpid(pid_a[1], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[2]);
      ret_pid = waitpid(pid_a[2], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[0]);
      ret_pid = waitpid(pid_a[0], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      sleep(5);
      printf(1, "\n This is the parent: Now waiting for child with PID# %d\n",pid_a[4]);
      ret_pid = waitpid(pid_a[4], &exit_status, 0);
      printf(1, "\n This is the partent: Child# %d has exited with status %d\n",ret_pid, exit_status);
      
      return 0;
  }
      
      
int PScheduler(void){
    // use this part to test the priority scheduler. 
    // Assuming that the priorities range between range between 0 to 63
    // 0 is the highest priority. All processes have a default priority of 20 
    int pid, ret_pid, exit_status;
    int pCount = 10;	// how many processes we want
    int i,j,k;
  
    printf(1,"Step 2: testing priority scheduler and setpriority(int priority)) system call:\n");
    printf(1,"Step 2: Assuming that the priorities range between range between 0 to 63\n");
    printf(1,"Step 2: 0 is the highest priority. All processes have a default priority of 20\n");
    printf(1, "Step 2: The parent processes will switch to priority 0\n");

    setpriority(0);
    for (i = 0; i <  pCount; i++) {
	pid = fork();
	if (pid > 0 ) {	// Parent process
	    continue;
        }
	else if ( pid == 0) {
	  printf(1, "\n Hello! this is child# %d and I will change my priority to %d \n",getpid(),pCount*20-20*i);
	  //printf(1, "\n Hello! this is child# %d and I will change my priority to %d \n",getpid(),i);
		setpriority(pCount*20 - 20*i);	
		for (j=0;j<50000;j++) {
			for(k=0;k<10000;k++) {
				asm("nop"); }}
		printf(1, "\n child# %d with priority %d has finished! \n",getpid(),pCount*20-20*i);	
		//printf(1, "\n child# %d with priority %d has finished! \n",getpid(),i);	
		exit(0);
        }
        else {
	    printf(2," \n Error \n");
	    exit(-1);
        }
    }
    if(pid > 0) {
        for (i = 0; i <  pCount; i++) {
	    ret_pid = wait(&exit_status);
	    printf(1,"\n This is the parent: child with PID# %d has finished with status %d \n",ret_pid,exit_status);
	}
       printf(1,"\n if processes with highest priority finished first then its correct \n");
    }
    return 0;
}

int starvation(void){
  int pid, ret_pid, exit_status;
  int pCount = 3;	// how many processes we want
  //int i,j,k;
  int i;
  int arithmetic;

  printf(1, "\n This will test for starvation in the priority scheduler\n");
  printf(1, "One child will have highest priority, but take a long time to complete\n");
  printf(1, "The other children will have low priority, but be rather fast arithmetic functions\n");
  printf(1, "If properly handled, these other children should finish before the first child\n");

  printf(1, "The parent processes will switch to priority 0\n");
  setpriority(0);
  for (i = 0; i <  pCount; i++) {	// Create the processes
    pid = fork();
    if (pid > 0 ) {	// Parent process
      continue;
    }
    else if ( pid == 0) {
	  //printf(1, "\n Hello! this is child# %d and I will change my priority to %d \n",getpid(),i);
      setpriority(2); // set priority super high
      if (i == 0){
        setpriority(1);	// should be 2nd fastest process
        printf(1, "\n child# %d doing slow operation! \n",getpid());	
	// Do slow stuff if child 0
        /*for (j=0;j<70000;j++) {
          for(k=0;k<10000;k++) {
            asm("nop"); }}
	*/
	sleep(101); // slep for 101 ticks

      }
      else{
        printf(1, "\n child# %d this should be done quick!! \n",getpid());	
        arithmetic = 2+2;
        printf(1, "\n child # %d says: 2 plus 2 = %d \n", getpid(), arithmetic);
        
      }
      if (i == 0){
        printf(1, "\n child# %d with priority 1 has finished! \n",getpid());	
      }
      else
        printf(1, "\n child# %d with priority 100 has finished! \n",getpid());	
      exit(0);
      }
    else {
      printf(2," \n Error \n");
      exit(-1);
    }
  }
  if(pid > 0) {
    for (i = 0; i <  pCount; i++) {
      ret_pid = wait(&exit_status);
      printf(1,"\n This is the parent: child with PID# %d has finished with status %d \n",ret_pid,exit_status);
	}
      printf(1,"\n if processes with highest priority finished first then its correct \n");
  }
  return 0;
}

int testTime(int n){
  uint startTime = uptime(); 
  printf(1,  "Start time %d\n", startTime);
  while (uptime() - startTime < n){};
  printf(1, "End time: %d\n", uptime());
  printf(1, "Lasted %d ticks\n", n);
  return 0;
}
