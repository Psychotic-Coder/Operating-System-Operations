#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

pthread_t odd,even;
pthread_mutex_t lock;
int mem = 0;

void *oddT(void *arg){
	pthread_mutex_lock(&lock);
	while(1){
		if(mem%2 != 0){
			sleep(1);
			printf("ODD %d\n",mem);
			mem++;
		}
		else{
			pthread_mutex_unlock(&lock);
		}	
	}
	
}
void *evenT(void *arg){
	pthread_mutex_lock(&lock);
	while(1){
		if(mem%2 == 0){
			sleep(1);
			printf("eVEN %d\n",mem);
			mem++;
		}
		else{
			pthread_mutex_unlock(&lock);
		}
	}
}

int main(){
	pthread_mutex_init(&lock, NULL);
	pthread_create(&even,NULL,evenT,NULL);
	pthread_create(&odd,NULL,oddT,NULL);
	pthread_join(odd, NULL);
	pthread_join(even, NULL);	
}
