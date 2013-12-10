#include <stdio.h>
#include "lab2.h"
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
  printf("Empty?: %d\n",isEmpty());
  initialize_queue();
  int i, NTHREADS=atoi(argv[1]);

  //for(i = 0; i<10; i++){
  //   enqueue(i);
  //}
        
  display();
  printf("Empty?: %d\n",isEmpty());
  struct timeval t1, t2;
  double elapsedTime;
  gettimeofday(&t1, NULL);

  pthread_t threads[NTHREADS];
  int k, j;
        
  for(k=0; k < NTHREADS; k++){
    pthread_create( &threads[k], NULL, runThread2, NULL );
  }
        
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
  int x = 50;
  int i;

  //for(i=0;i<60;i++){
    enqueue(123);
  //}
  printf("Empty?: %d\n",isEmpty());
  display();


  //for(i=0;i=x;i++){
    dequeue(extractedValue);
    dequeue(extractedValue);
    dequeue(extractedValue);
    dequeue(extractedValue);
    dequeue(extractedValue);
    dequeue(extractedValue);

    enqueue(100);
    enqueue(101);
    enqueue(102);
    enqueue(103);
    display();
    dequeue(extractedValue);

  //}
    printf("Empty?: %d\n",isEmpty());
 

 /* printf("Empty?: %d\n",isEmpty());
    for(i=40;i<x;i++){
    enqueue(i);
  }
  printf("Empty?: %d\n",isEmpty());
    for(i=0;i=x;i++){
    dequeue(extractedValue);
  }*/

  return NULL;

}