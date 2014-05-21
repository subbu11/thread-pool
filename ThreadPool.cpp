#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#include <iostream>
#include <queue>

#include "ThreadPool.hpp"

pthread_mutex_t ThreadPool ::  mPoolLock = PTHREAD_MUTEX_INITIALIZER;
queue<Job*> ThreadPool ::  mJobQueue ;


ThreadPool :: ThreadPool()
{
}

ThreadPool :: ~ThreadPool()
{
}



void ThreadPool :: initialize(int numOfThreads)
{
    mThreads = (pthread_t *)malloc(sizeof(pthread_t) * numOfThreads);
    int i = 0 ;
    for(i=0; i< numOfThreads; i++)
    {
        pthread_create(&mThreads[i], NULL, &run, NULL);
        printf("created thread %u\n",(int)mThreads[i]);
    }
}

void ThreadPool :: submitJob(void (*function_p)(int), int arg)
{
    Job *j = new Job();
    j->mFunction = function_p;
    j->mArg      = arg;

    /* add the job to the jobQueue */
    pthread_mutex_lock(&mPoolLock);
    
    mJobQueue.push(j);
    
    pthread_mutex_unlock(&mPoolLock);

}

void* ThreadPool :: run (void *arg)
{

	while(1)
	{
		pthread_mutex_lock(&mPoolLock);
		if(!mJobQueue.empty())
		{	
			printf("\n");
			printf("\nThread[%u] acquired the lock on jobQueue\n",(int)pthread_self());

			Job *j = mJobQueue.front();
			mJobQueue.pop();
			
			printf("job found : %d %p %d\n",j->mArg,j->mFunction, (int)mJobQueue.size());
			
			j->mFunction(j->mArg);
			delete j;
			j = NULL;

			printf("Thread[%u] released the lock on jobQueue\n",(int)pthread_self());
			printf("\n");
		}
		pthread_mutex_unlock(&mPoolLock);
	}

}

