#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node
{
    int value;
    struct node *next;
}*dummy=NULL,*head=NULL,*tail=NULL;

/*struct queue
{
    node *head:
    node *tail;
    node *dummy;
};*/

pthread_mutex_t lock;


void initialize_queue(){
    head=(struct node *)malloc(sizeof(struct node));
    tail=(struct node *)malloc(sizeof(struct node));
    dummy=(struct node *)malloc(sizeof(struct node));
    head->next = dummy;
    tail = dummy;
    dummy= NULL;
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
        return;
    }
    pthread_mutex_lock(&lock);
    tmp->value = val;
    tmp->next=dummy;
    if(head->next==dummy)
        head=tmp;
    tail->next = tmp;
    tail=tmp;
    tail->next = dummy;
    pthread_mutex_unlock(&lock);
}

int dequeue(int *extractedValue)
{
    struct node *tmp;
    if( isEmpty( ) )
    {
        printf("Queue Empty\n");
        exit(1);
    }
    pthread_mutex_lock(&lock);
    tmp=head;
    extractedValue=&(tmp->value);
    printf("Extracted value: %d\n",*extractedValue);
    head=head->next;
    free(tmp);
    pthread_mutex_unlock(&lock);
    return *extractedValue;
}

void display()
{
     struct node *var=head;
     if((var->next)!=NULL)
     {
           printf("\nElements are as:  ");
           while((var->next)!=NULL)
           {
                printf("\t%d",var->value);
                var=var->next;
           }
     printf("\n");
     } 
     else
     printf("\nQueue is Empty");
}

int isEmpty()
{
    if(head->next==dummy)
        return 1;
    else
        return 0;

}
