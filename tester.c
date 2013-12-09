#include <stdio.h>
#include "lab2.h"
#include <sys/time.h>
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
  }
        
  display();
  
  struct timeval t1, t2;
  double elapsedTime;
  gettimeofday(&t1, NULL);

  pthread_t threads[NTHREADS];
  int k, j;
        
  for(k=0; k < NTHREADS; k++){
    pthread_create( &threads[k], NULL, runThread, NULL );
  }
  
  runThread();
        
  for(j=0; j < NTHREADS; j++){
    pthread_join( threads[j], NULL);
  }
  
  gettimeofday(&t2, NULL);

  display();
  
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
  //cout << elapsedTime << " ms.\n";
  printf("%.4lf ms elapsed\n", elapsedTime); 
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
                                enqueue(r % 343);
                                printf("Switch enqueued %d\n",r % 343);
                                r= rand();
                                break;
                }
        }

        return NULL;        
}
