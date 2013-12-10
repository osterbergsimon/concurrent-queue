#include <stdio.h>
//#include "lab2.h"
#include "concurrent_queue_2locks.h"
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

void *runThread();
void *runThread2();
int *extractedValue = 0;
int NTHREADS = 1;

void main(int argc, char *argv[]){
  if(argc<=1) {
    printf("You did not feed me arguments, I will die now :( \n");
    exit(1);
  }

  
  initialize_queue();
  int i; 
  NTHREADS=atoi(argv[1]);

  for(i = 0; i<100; i++){
    enqueue(i);
  }
        
  //display();
  //printf("main: Empty?: %d\n",isEmpty());
  struct timeval start, end;
  long mtime, seconds, useconds;  
  gettimeofday(&start, NULL);

  pthread_t threads[NTHREADS];
  int k, j;

    
  for(k=0; k < NTHREADS; k++){
    pthread_create( &threads[k], NULL, runThread, &NTHREADS );
  }
        
  for(j=0; j < NTHREADS; j++){
    pthread_join( threads[j], NULL);
  }
  
  gettimeofday(&end, NULL);

  //display();
  
    //seconds  = t2.tv_sec  - t1.tv_sec;
    //useconds = t2.tv_usec - t1.tv_usec;
    printf("%ld usec?\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
}

void *runThread(){
        int y = 10000000;
        int x = y/NTHREADS;
        printf("X: %d\n",x);
        srand(time(NULL));
        int r = rand();
        int i = 0;

        for(i; i<x; i++ ){
                switch(r % 2){
                        case (1) :
                                dequeue(extractedValue);
                                r = rand();
                                //printf("Switch dequeue\n");
                                break;
                        default :
                                enqueue(r % 343);
                                //printf("Switch enqueued %d\n",r % 343);
                                r= rand();
                                break;
                }
        }

        return NULL;        
}