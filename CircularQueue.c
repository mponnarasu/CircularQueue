#include <stdio.h>

/* allowed values only 3, 7, 0xC and 0xF  */
#define QUEUESIZE 0x0F  

typedef struct 
{
  int data[QUEUESIZE];
  signed char head_queue;
  signed char tail_queue;
}Queue_type;

Queue_type queue1 = {.head_queue = 0, .tail_queue = 0};
Queue_type queue2 = {.head_queue = 0, .tail_queue = 0};

enum {OPERATION_OK, OPERATION_ERROR};


/* operations: Read queue, write queue */

int readqueue(Queue_type * queueptr, int * queue_value)
{
   int rtn;
   if(queueptr->head_queue != queueptr->tail_queue) 
   {
     *queue_value = queueptr->data[queueptr->tail_queue]; 
      queueptr->tail_queue++;
      if (queueptr->tail_queue > QUEUESIZE)
      {
        queueptr->tail_queue = 0;
      }
      rtn = OPERATION_OK;
   }
   else
   {
      rtn = OPERATION_ERROR;
      printf("Queue Empty\n");
   }
   return rtn;
}


int writequeue(Queue_type * queueptr, int queue_value)
{
   int rtn;
   if(((queueptr->head_queue - queueptr->tail_queue) & QUEUESIZE ) != QUEUESIZE)
   {
      queueptr->data[queueptr->head_queue] = queue_value; 
      queueptr->head_queue++;
      if (queueptr->head_queue > QUEUESIZE)
      {
        queueptr->head_queue = 0;
      }
      rtn = OPERATION_OK;
   }
   else
   {
      rtn = OPERATION_ERROR;
      printf("Queue full\n");
   }
   return rtn;
}

int main(void)

  int i, j;
  int tempdata;
  printf("hello\n");
  /* initialize queue */ 
  for(i=0;i<QUEUESIZE;i++)
  {
    queue1.data[i] = i;
    printf("Queue value %d\n", queue1.data[i]);
  }
	
  for(j=17;j>0;j--)
  {
    if(!writequeue(&queue1, j))
    {
     printf("Writen Data \n", j);

    }
  }

  for(i=0;i<QUEUESIZE;i++)
  {
    printf("Queue value %d \n", queue1.data[i]);

  }

  for(j=17;j>0;j--)
  {
     if(!readqueue(&queue1, &tempdata))
     {
      printf(" read data %d  \n", tempdata );
     }
  }

  for(i=0;i<QUEUESIZE;i++)
  {
    printf("Queue value %d \n", queue1.data[i]);
  }

return (0);
}

