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
    dummy -> next = NULL;
    head = dummy;
    tail = dummy;
    if (pthread_mutex_init(&head_lock, NULL) != 0){
        printf("\n mutex init failed\n");
    }
    if (pthread_mutex_init(&tail_lock, NULL) != 0){
        printf("\n mutex init failed\n");
    }
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
    tmp->value = val;
    tmp->next = NULL;
    tail->next = tmp;
    tail=tmp;
    pthread_mutex_unlock(&tail_lock);
}

int dequeue(int *extractedValue)
{
    pthread_mutex_lock(&head_lock);
 	struct node *h, *n;
    
 	h = head;
 	n = h->next;
 	if(n == NULL){
 		pthread_mutex_unlock(&head_lock);
        return 1;
 	}
 	head = n;
 	extractedValue=&(n->value);
 	pthread_mutex_unlock(&head_lock);
 	if (head == dummy){
 		enqueue(h->value);
 	}
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
