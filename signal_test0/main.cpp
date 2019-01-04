#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <string.h>

 
pid_t task0_pid = 0;
pid_t task1_pid = 0;

void signal_process0(int aSigNum, siginfo_t *apSigInfo, void *aUnused)
{
	printf("%s 000000 received\n",__func__);
}

void signal_process1(int aSigNum, siginfo_t *apSigInfo, void *aUnused)
{
	printf("%s 111111 received\n",__func__);
}


void signal_init()
{
	int lRetVal = 0;
    //prepare internal signal handler
    struct sigaction sig;
    sig.sa_flags = SA_SIGINFO;
	
	//setup signal handler0
    sig.sa_sigaction = signal_process0;
    if(sigaction(62, &sig, NULL) != 0)
    {
       printf("Failed to register signal0 handler.\n");
       lRetVal = 1;
    }

    //setup signal handler1
    sig.sa_sigaction = signal_process1;
    if(sigaction(63, &sig, NULL) != 0)
    {
       printf("Failed to register signal1 handler.\n");
       lRetVal = 1;
    }
}


int apex_irq_send_to_pid(pid_t aPid, int aValue,int signalnum)
{
	int lRet = -1;
	struct siginfo lInfo;
	struct pid *lpPidStruct;
	struct task_struct *lpTask;

	
	// Send the signal to user space
	memset(&lInfo, 0, sizeof(struct siginfo));
	lInfo.si_signo = signalnum;
	lInfo.si_code  = SI_QUEUE;
	lInfo.si_int   = aValue;

	lpPidStruct    = find_get_pid(aPid);
	lpTask         = pid_task(lpPidStruct,PIDTYPE_PID);
	if(lpTask == NULL)
	{
		printf("No such pid %u. Signal not sent.\n", (unsigned) aPid);
		lRet = -1;
	} // If no such pidRegisterred
	else
	{
		printf("   Sending the signal to user space.\n");
		lRet = send_sig_info(signalnum, &lInfo, lpTask);    //send the signal
	if (lRet < 0) {
		printf("Error sending signal to user space.\n");
	} // If sending signal failed
	}
	return lRet;
} 


void *thread0(void*)
{
	task0_pid = syscall(SYS_gettid);
	printf("%s created pid %d\n",__func__,task0_pid);
	
	while(1)
	{
		
		usleep(500*1000);
		apex_irq_send_to_pid(task0_pid, 0, 62);
		printf("00000000 send \n");
	}
	
}

void *thread1(void*)
{
	task1_pid = syscall(SYS_gettid);
	printf("%s created pid %d\n",__func__,task1_pid);
	
	while(1)
	{
		
		usleep(500*1000);
		apex_irq_send_to_pid(task1_pid, 0, 63);
		printf("11111111 send \n");
	}
	
}
  

int main(void)
{
	int ret = 0;
	signal_init();
	
	pthread_t p0;
	pthread_t p1;
	
	printf("Start Create Threads.\n");
	
	if((ret = pthread_create(&p0,NULL,thread0,NULL)))
	{
		printf("thread0 create failed: %d\n",ret);
		return 0;
	}
	
	if((ret = pthread_create(&p1,NULL,thread1,NULL)))
	{
		printf("thread1 create failed: %d\n",ret);
		return 0;
	}
	
	
	pthread_join(p0,NULL);
	pthread_join(p1,NULL);
	return 0;
}