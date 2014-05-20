#include <stdio.h>
#include "ThreadPool.hpp"

void doJob(int jobNo)
{
        printf("Thread [%u] doing job[%d]\n",(int)pthread_self(),jobNo);
}

int main()
{
        int i = 0;

        ThreadPool tp;
        tp.initialize(4);

        printf(" created thread pool\n");

        for(i=0; i < 20; i++)
        {
                tp.submitJob(doJob,i);
        }

}
