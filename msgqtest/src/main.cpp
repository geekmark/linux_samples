#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>
#include <sys/ipc.h>

#include "main.hpp"

int msgInit()
{

    DerivedA dataA;
    dataA.printval();

    printf("msgInit start\n");
    int key = ftok("./markkey2",10);

    int msgId = msgget(key,0600|IPC_CREAT);
    if(msgId < 0)
    {
        perror("msgget error\n");
    }
    printf("key %d id %d\n",key,msgId);

    return msgId;

} 


void threadA(void)
{
    int msgid = msgInit();
    char msgtext[10]={'A'};
    int flag = 0;

    for(int i =0;i<10;i++)
    {
        msgtext[i] = 'A'+i;
        printf("%c",msgtext[i]);
    }
 
    printf("ThreadA start\n");
    while(1)
    {
        flag = msgsnd(msgid,msgtext,10,0);
        if(flag < 0)
        {
            perror("A msgsnd error\n");
        }
        else
        {
            printf("threadA send\n");
        }
        sleep(1);
    }
}

void threadB(void)
{
    int msgid = msgInit();
    char msgtext[10]={'B'};
    int flag = 0;

    for(int i =0;i<10;i++)
    {
        msgtext[i] = 'B'+i;
        printf("%c",msgtext[i]);
    }
 
    printf("ThreadB start\n");

    while(1)
    {
        flag = msgsnd(msgid,msgtext,10,0);
        if(flag < 0)
        {
            perror("B msgsnd error\n");
        }
        else
        {
            printf("threadB send\n");
        }
        sleep(1);
    }
}


void threadC(void)
{
    int msgid = msgInit();
    char msgtext[10]={'C'};
    int flag = 0;

    for(int i =0;i<10;i++)
    {
        msgtext[i] = 'C'+i;
        printf("%c",msgtext[i]);
    }
 
    printf("ThreadC start\n");

    while(1)
    {
        flag = msgsnd(msgid,msgtext,10,0);
        if(flag < 0)
        {
            perror("C msgsnd error\n");
        }
        else
        {
            printf("threadC send\n");
        }
        sleep(1);
    }
}




int main(void)
{    
    int msgid = msgInit();
    char msgtext[100] = {0};
    int flag = 0;
    pid_t pid;
     
    
    pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        threadA();
    }

    pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        threadB();
    }

    pid = fork();
    if(pid < 0)
    {
        printf("fork error\n");
    }
    else if(pid == 0)
    {
        threadC();
    }

    printf("main start\n");
    while(1)
    {
        flag = msgrcv(msgid,msgtext,100,0,0);
        if(flag < 0)
        {
            perror("msgrcv error\n");
        }
        else
        {
            printf("main msgrcv msg len %d \n",flag);
            for(int i =0;i<flag;i++)
            {
                printf("%c",msgtext[i]);
            }
        }
        
    }
    
}

