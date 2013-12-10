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

    struct node *tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    if(tmp==NULL)
    {
        printf("Error\n");
        free(tmp);
    }
    tmp->value = val;
    tmp->next = NULL;
    pthread_mutex_lock(&lock);    
    tail->next = tmp;
    tail=tmp;
    pthread_mutex_unlock(&lock);
}

int dequeue(int *extractedValue)
{

    struct node *currHead, *nextHead;
    pthread_mutex_lock(&lock);
    currHead = head;
    nextHead = currHead->next;
    if(nextHead == NULL){
        pthread_mutex_unlock(&lock);
        return 1;
    }
    free(head);
    head = nextHead;
    *extractedValue=nextHead->value;
    pthread_mutex_unlock(&lock);
    return 0;

}


void display()
{
     struct node *var=head->next;
     if(var!=NULL)
     {
           printf("\nElements are as: ");
           while(var!=NULL)
           {
                printf("\t%d",var->value);
                var=var->next;
           }
           
     printf("\n");
     }
     else
     printf("\ndisplay: Queue is Empty\n");
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
