#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5
#define TQ 15

typedef struct
{
    int id;
    int priority;
    int arrival;
    int burst;

    int remaining;
    int waiting;
    int turnaround;
    int completed;
} Process;

void generate(Process p[])
{
    srand(time(NULL));

    printf("Generated Processes\n");
    printf("---------------------------------------------\n");
    printf("ID\tPri\tAT\tBT\n");

    for(int i=0;i<N;i++)
    {
        p[i].id=i+1;
        p[i].priority=1+rand()%5;
        p[i].arrival=rand()%20;
        p[i].burst=10+rand()%91;

        p[i].remaining=p[i].burst;
        p[i].completed=0;

        printf("%d\t%d\t%d\t%d\n",
              p[i].id,
              p[i].priority,
              p[i].arrival,
              p[i].burst);
    }

    printf("\n");
}

void reset(Process a[],Process b[])
{
    for(int i=0;i<N;i++)
    {
        b[i]=a[i];
        b[i].remaining=b[i].burst;
        b[i].completed=0;
    }
}

void FCFS(Process p[])
{
    int time=0;

    for(int i=0;i<N-1;i++)
        for(int j=i+1;j<N;j++)
            if(p[i].arrival>p[j].arrival)
            {
                Process t=p[i];
                p[i]=p[j];
                p[j]=t;
            }

    double aw=0,at=0;

    printf("\n========== FCFS ==========\n");

    printf("ID\tWT\tTAT\n");

    for(int i=0;i<N;i++)
    {
        if(time<p[i].arrival)
            time=p[i].arrival;

        p[i].waiting=time-p[i].arrival;

        time+=p[i].burst;

        p[i].turnaround=time-p[i].arrival;

        aw+=p[i].waiting;
        at+=p[i].turnaround;

        printf("%d\t%d\t%d\n",
              p[i].id,
              p[i].waiting,
              p[i].turnaround);
    }

    printf("Average Waiting Time = %.2lf\n",aw/N);
    printf("Average Turnaround Time = %.2lf\n",at/N);
}

void Priority(Process p[])
{
    int done=0,time=0;

    double aw=0,at=0;

    printf("\n========== PRIORITY ==========\n");
    printf("ID\tWT\tTAT\n");

    while(done<N)
    {
        int idx=-1;

        for(int i=0;i<N;i++)
        {
            if(!p[i].completed && p[i].arrival<=time)
            {
                if(idx==-1 || p[i].priority<p[idx].priority)
                    idx=i;
            }
        }

        if(idx==-1)
        {
            time++;
            continue;
        }

        p[idx].waiting=time-p[idx].arrival;

        time+=p[idx].burst;

        p[idx].turnaround=time-p[idx].arrival;

        p[idx].completed=1;

        done++;

        aw+=p[idx].waiting;
        at+=p[idx].turnaround;

        printf("%d\t%d\t%d\n",
              p[idx].id,
              p[idx].waiting,
              p[idx].turnaround);
    }

    printf("Average Waiting Time = %.2lf\n",aw/N);
    printf("Average Turnaround Time = %.2lf\n",at/N);
}

void RoundRobin(Process p[])
{
    int queue[500];
    int front=0,rear=0;

    int visited[N]={0};

    int completed=0;
    int time=0;

    double aw=0,at=0;

    printf("\n========== ROUND ROBIN (TQ=15) ==========\n");

    while(completed<N)
    {
        for(int i=0;i<N;i++)
        {
            if(!visited[i] && p[i].arrival<=time)
            {
                queue[rear++]=i;
                visited[i]=1;
            }
        }

        if(front==rear)
        {
            time++;
            continue;
        }

        int i=queue[front++];

        if(p[i].remaining>TQ)
        {
            p[i].remaining-=TQ;
            time+=TQ;

            for(int j=0;j<N;j++)
            {
                if(!visited[j] && p[j].arrival<=time)
                {
                    queue[rear++]=j;
                    visited[j]=1;
                }
            }

            queue[rear++]=i;
        }
        else
        {
            time+=p[i].remaining;
            p[i].remaining=0;

            p[i].turnaround=time-p[i].arrival;
            p[i].waiting=p[i].turnaround-p[i].burst;

            completed++;

            aw+=p[i].waiting;
            at+=p[i].turnaround;
        }
    }

    printf("ID\tWT\tTAT\n");

    for(int i=0;i<N;i++)
    {
        printf("%d\t%d\t%d\n",
              p[i].id,
              p[i].waiting,
              p[i].turnaround);
    }

    printf("Average Waiting Time = %.2lf\n",aw/N);
    printf("Average Turnaround Time = %.2lf\n",at/N);
}

int main()
{
    Process original[N],temp[N];

    generate(original);

    reset(original,temp);
    FCFS(temp);

    reset(original,temp);
    Priority(temp);

    reset(original,temp);
    RoundRobin(temp);

    return 0;
}