#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct node
{
    int value;
    struct node *next;
}*dummy=NULL,*head=NULL,*tail=NULL;


pthread_mutex_t head_lock, tail_lock;


void initialize_queue(){
    head=(struct node *)malloc(sizeof(struct node));
    tail=(struct node *)malloc(sizeof(struct node));
    dummy=(struct node *)malloc(sizeof(struct node));
    dummy -> next = NULL; //dummy = NULL => nollor
    head = tail = dummy;
    head->next = NULL;
    if (pthread_mutex_init(&head_lock, NULL) != 0){
        printf("\n mutex init failed\n");
    }
    if (pthread_mutex_init(&tail_lock, NULL) != 0){
        printf("\n mutex init failed\n");
    }
}


struct node* createNode(int val){
    struct node *tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    if(tmp==NULL)
    {
        printf("Error\n");
        free(tmp);
        return;
    }
    else{
        tmp->value = val;
        tmp->next=NULL;
    }
    return tmp;
}


void enqueue(int val)
{
    pthread_mutex_lock(&tail_lock);

    struct node *tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    if(tmp==NULL)
    {
        printf("Error\n");
        free(tmp);
    }
    else{
        tmp->value = val;
        tmp->next=NULL;
    }

    tail->next = tmp;
    if(head!=tail){
    	tail=tmp;
    }
    printf("Enqueued: %d\n", (tail->value));
    pthread_mutex_unlock(&tail_lock);
}

int dequeue(int *extractedValue)
{
    pthread_mutex_lock(&head_lock);
    struct node *tmp;
    int ret = -1;
    if(isEmpty())
    {
        //printf("Queue Empty\n");
        tail=dummy;
        pthread_mutex_unlock(&head_lock);
        
    }else{
        tmp=head->next;
        extractedValue=&(tmp->value);
        //printf("Extracted value: %d\n",tmp->value);
        printf("Extracted value: %d\n",*extractedValue);
        free(head);
        head=tmp;
        pthread_mutex_unlock(&head_lock);
        ret = *extractedValue;
    }
    //printf("Dequeue end\n");
    return ret;

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
     printf("\nQueue is Empty\n");
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