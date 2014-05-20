#include <stdio.h>
#include <pthread.h>

#include <iostream>
#include <queue>


using namespace std;

class Job
{
         public:                               
                void (*mFunction)(int);
                int mArg;
};

class ThreadPool
{
        private:
                pthread_t *mThreads;       
                static queue<Job*> mJobQueue;      
                static pthread_mutex_t mPoolLock;  
                 
                static void* run(void* arg);
        
        public:
                ThreadPool();
                ~ThreadPool();
                void initialize(int numOfThreads);
                void submitJob(void (*function_p)(int),int arg);
    
};  
