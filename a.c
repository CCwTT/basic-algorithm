#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
typedef long long ll;

int countFish=0;
int numFish=10;

pthread_mutex_t mtx=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_catchfish_finish=PTHREAD_COND_INITIALIZER; 
pthread_cond_t cond_eatfish_finish=PTHREAD_COND_INITIALIZER;

void *fisherman(){
	int i;
	for(i=0;i<numFish*2;i++){
		pthread_mutex_lock(&mtx);
		if(countFish==numFish){
			pthread_cond_wait(&cond_eatfish_finish,&mtx);
		}
		countFish++;
        printf("Catching Fish!Now there are %d fish,total fish are %d\n",countFish,i+1);
		pthread_cond_signal(&cond_catchfish_finish);
		pthread_mutex_unlock(&mtx);
	}
	pthread_exit(NULL);
}

void *cat(){
	int i;
	for(i=0;i<numFish*2;i++){
		pthread_mutex_lock(&mtx);
		if(countFish==0){
			pthread_cond_wait(&cond_catchfish_finish,&mtx);
		}
		countFish--;
        printf("Eating Fish!Now there are %d fish\n",countFish);
		pthread_cond_signal(&cond_eatfish_finish);
		pthread_mutex_unlock(&mtx);
	}
	pthread_exit(NULL);
}

int main(){
  	pthread_t fishermanThread,catThread;
  	pthread_create(&fishermanThread,NULL,fisherman,NULL);
  	pthread_create(&catThread,NULL,cat,NULL);
  	pthread_join(fishermanThread,NULL);
  	pthread_join(catThread,NULL);
    printf("The cat is full!\n");
    return 0;
}