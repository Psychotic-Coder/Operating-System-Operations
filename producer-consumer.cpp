#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

pthread_t prod,con;
sem_t f,e,mutex;
int buff[5],i=0,r=0,fr=0;

void *producer(void *arg){
	while(1){
		sem_wait(&e);
		sem_wait(&mutex);
		buff[(++r)%5] = i;
		printf("Prod: %d\n",i);
		i++;
		sleep(1);
		sem_post(&mutex);
		sem_post(&f);	
	}		
}

void *cons(void *arg){
	while(1){
		sem_wait(&f);
		sem_wait(&mutex);
		printf("Cons: %d\n",buff[(++fr)%5]);
		sleep(1);
		sem_post(&mutex);
		sem_post(&e);
	}
}

int main(){
	sem_init(&mutex,0,1);
	sem_init(&f,0,0);
	sem_init(&e,0,5);
	pthread_create(&prod,NULL,producer,NULL);
	pthread_create(&con,NULL,cons,NULL);
	pthread_join(prod,NULL);
		
	pthread_join(con,NULL);
}
