#include <stdio.h>
#include "lab2.h"
#include <time.h>
#include <stdlib.h>
#include <pthread.h>



void *runThread();
void *runThread2();
int *extractedValue = 0;

void main(){
	initialize_queue();
	int i;

	pthread_t N1;
	for(i = 1; i<10; i++){
		enqueue(i);
		display();
	}
	if(pthread_create(&N1, NULL, runThread, NULL)) {
		printf("Error creating thread\n");
		//return 1;
	}

	runThread();

	if(pthread_join(N1, NULL)) {
		printf("Error joining thread\n");
		//return 2;
	}

	display();

}

void *runThread(){
	int x = 20;
	srand(time(NULL));
	int r = rand() % x;
	int i = 10;


	for(i; i<x; i++ ){
		switch(r % 2){
			case (1) :
				dequeue(extractedValue);
				r = rand();
				printf("Switch dequeue\n");
				break;
			default :
				enqueue(i);
				r= rand();
				printf("Switch enqueued %d\n",i);
				break;
		}
	}

	return NULL;	
}
