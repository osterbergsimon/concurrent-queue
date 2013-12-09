#include <stdio.h>
#include "lab2.h"
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

void *runThread();
int *extractedValue = 0;


void main(int argc, char *argv[]){
    if(argc<=1) {
        printf("You did not feed me arguments, I will die now :( \n");
        exit(1);
     } 

	initialize_queue();
	int i, NTHREADS=atoi(argv[1]);

	for(i = 0; i<10; i++){
		enqueue(i);
		display();
	}

  pthread_t threads[NTHREADS];
  int k, j;
	     
  for(k=0; k < NTHREADS; k++){
    pthread_create( &threads[k], NULL, runThread, NULL );
  }
  
  runThread();
	   
  for(j=0; j < NTHREADS; j++){
    pthread_join( threads[j], NULL);
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
				enqueue(r % 100000);
				r= rand();
				printf("Switch enqueued %d\n",i);
				break;
		}
	}

	return NULL;	
}
