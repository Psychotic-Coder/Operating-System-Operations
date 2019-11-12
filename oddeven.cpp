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


//#include<stdio.h>
//#include<pthread.h>
//#include<unistd.h>
//pthread_t tid[2];
//unsigned int shared_data = 0;
//pthread_mutex_t mutex;
//unsigned int rc;
////prototypes for callback functions
//
//void* PrintEvenNos(void*);
//void* PrintOddNos(void*);
//
//int main()
//{
//    pthread_create(&tid[0],0,&PrintEvenNos,0);
//    pthread_create(&tid[1],0,&PrintOddNos,0);
//    sleep(3);
//
//    pthread_join(tid[0],NULL);
//    pthread_join(tid[1],NULL);
//}
//
//void* PrintEvenNos(void *ptr)
//{
//     rc = pthread_mutex_lock(&mutex);
//     do
//     {
//         if(shared_data%2 == 0)
//         {
//             printf("Even:%d\n",shared_data);
//             shared_data++;
//         }
//         else
//         {
//             rc=pthread_mutex_unlock(&mutex);//if number is odd, do not print, release mutex
//         }
//     } while (shared_data <= 100);
//}
//
//void* PrintOddNos(void* ptr1)
//{
//    rc = pthread_mutex_lock(&mutex);
//    do
//    {
//        if(shared_data%2 != 0)
//        {
//            printf("odd:%d\n",shared_data);
//            shared_data++;
//        }
//        else
//        {
//            rc = pthread_mutex_unlock(&mutex);//if number is even, do not print, release mutex
//        }
//    } while (shared_data <= 100);
//}
