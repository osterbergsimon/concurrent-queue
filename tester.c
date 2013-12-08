#include <stdio.h>
#include "lab2.h"
#include <time.h>
#include <stdlib.h>
#include <pthread.h>



void *runThread();
int *extractedValue = 0;

int main(){
	initialize_queue();
	int i;
	int N = 2;
	pthread_t N1;
	for(i = 0; i<100; i++){
		enqueue(i);
	}
	if(pthread_create(&N1, NULL, runThread, NULL)) {
		printf("Error creating thread\n");
		return 1;
	}

	runThread();


	if(pthread_join(N1, NULL)) {
		printf("Error joining thread\n");
		return 2;
}

return *extractedValue;


}

void *runThread(){
	int x = 50;
	srand(time(NULL));
	int r = rand() % x;
	int i;

	for(i=0; i<r; i++ ){
		switch(r){
			case (r % 1) :
				dequeue(extractedValue);
				r = rand() % x;
				break;
			default :
				enqueue(r);
				r= rand() % x;
				break;
			}
		}

	return NULL;	
	}