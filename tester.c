#include <stdio.h>
//#include "lab2.h"
#include "concurrent_queue_2locks.h"
#include <sys/time.h>
#include <stdlib.h>
#include <pthread.h>

void *runThread();
void *runThread2();
int *extractedValue = 0;


void main(int argc, char *argv[]){
  if(argc<=1) {
    printf("You did not feed me arguments, I will die now :( \n");
    exit(1);
  }
  
  initialize_queue();
  int i, NTHREADS=atoi(argv[1]);

  //for(i = 0; i<10; i++){
  //   enqueue(i);
  //}
        
  display();
  printf("main: Empty?: %d\n",isEmpty());
  struct timeval start, end;
  long mtime, seconds, useconds;  
  gettimeofday(&start, NULL);

  pthread_t threads[NTHREADS];
  int k, j;
    
  
  for(k=0; k < NTHREADS; k++){
    pthread_create( &threads[k], NULL, runThread2, NULL );
  }
        
  for(j=0; j < NTHREADS; j++){
    pthread_join( threads[j], NULL);
  }
  
  gettimeofday(&end, NULL);

  display();
  
    //seconds  = t2.tv_sec  - t1.tv_sec;
    //useconds = t2.tv_usec - t1.tv_usec;
    printf("%ld usec?\n", ((end.tv_sec * 1000000 + end.tv_usec)
		  - (start.tv_sec * 1000000 + start.tv_usec)));
}

void *runThread(){
        int x = 40;
        srand(time(NULL));
        int r = rand() % x;
        int i = 10;


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



void *runThread2(){
  int x=60, i, y=0;

  for(i=y;i<x;i++){
    enqueue(i);
  }

    display();
  
  for(i=0;i<50;i++) {
    dequeue(extractedValue);
    //printf("HAAAANDS\n");
  }

  return NULL;

}
