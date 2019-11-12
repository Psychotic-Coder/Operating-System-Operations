#include<stdio.h>
#include<pthread.h>
#include<unistd.h>>
pthread_t p[5];

pthread_mutex_t chop[5];

void *chopstick(int n){
	printf("P%d THINK",n);
	pthread_mutex_lock(&chop[n-1]);
	pthread_mutex_lock(&chop[n%5]);
	printf("P%d has %d %d", n, n-1, n%5);
	sleep(1);
	pthread_mutex_unlock(&chop[n-1]);
	pthread_mutex_unlock(&chop[n%5]);
	printf("P%d DONE", n);
}

int main(){
	for(int i = 0;i<5;i++){
		pthread_mutex_init(&chop[i],NULL);
	}
	for(int i = 1;i<6;i++){
		pthread_create(&p[i],NULL,chopstick,(int )i);
	}
	for(int i = 1;i<6;i++){
		pthread_join(p[i],NULL);
	}
}
