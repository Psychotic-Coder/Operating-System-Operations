#include<semaphore.h>
#include<stdio.h>
#include<pthread.h>
# include<bits/stdc++.h>
using namespace std;

void *reader(void *);
void *writer(void *);

int readcount=0,sh_var=5,bsize[5];
sem_t x,wsem;
pthread_t r[4],w;

void *reader(void *i)
{

        sem_wait(&x);
        readcount++;
        if(readcount==1)
            sem_wait(&wsem);
        sem_post(&x);
        cout <<"Reader "<< (int *)i<< " updated value :" << sh_var<<endl;
        sem_wait(&x);
        readcount--;
        if(readcount==0)
            sem_post(&wsem);
        sem_post(&x);
}

void *writer(void *i)
{
        sem_wait(&x);
		cout << "writer-"<< "is writing"<<endl;
        sh_var=sh_var+5;
        sem_post(&x);
}

int main()
{
        sem_init(&x,0,1);
        sem_init(&wsem,0,1);
        
        pthread_create(&r[0],NULL,reader,(void *)0);
        pthread_create(&w,NULL,writer,NULL);
        pthread_create(&r[1],NULL,reader,(void *)1);
        pthread_create(&r[2],NULL,reader,(void *)2);
        pthread_create(&r[3],NULL,reader,(void *)3);
        pthread_create(&r[4],NULL,reader,(void *)4);

        pthread_join(r[0],NULL);
        pthread_join(w,NULL);
        pthread_join(r[1],NULL);
        pthread_join(r[2],NULL);
        pthread_join(r[3],NULL);
        pthread_join(r[4],NULL);

        return(0);
}    
