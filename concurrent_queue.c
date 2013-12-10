#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node
{
    int value;
    struct node *next;
}*dummy=NULL,*head=NULL,*tail=NULL;

pthread_mutex_t lock;

void initialize_queue(){
    head=(struct node *)malloc(sizeof(struct node));
    tail=(struct node *)malloc(sizeof(struct node));
    dummy=(struct node *)malloc(sizeof(struct node));
    dummy -> next = NULL;
    head = dummy;
    tail = dummy;
    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\n mutex init failed\n");
    }
}

void enqueue(int val)
{
    pthread_mutex_lock(&lock);

    struct node *tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    if(tmp==NULL)
    {
        printf("Error\n");
        free(tmp);
    }
    tmp->value = val;
    tmp->next = NULL;
    tail->next = tmp;
    tail=tmp;
    pthread_mutex_unlock(&lock);
}

int dequeue(int *extractedValue)
{
    pthread_mutex_lock(&lock);
    struct node *h, *n;
    
    h = head;
    n = h->next;
    if(n == NULL){
        pthread_mutex_unlock(&lock);
        return 1;
    }
    head = n;
    extractedValue=&(n->value);
    pthread_mutex_unlock(&lock);
    if (head == dummy){
        enqueue(h->value);
    }
    return 0;

}

int isEmpty()
{
    if(head==NULL)
        return 1;
    else if(head->next==NULL)
        return 1;
    else
        return 0;

}
