#include <stdio.h>

#define QUEUESIZE 0x5  
typedef char QueueIndex;
typedef struct 
{
  int data[QUEUESIZE];
  QueueIndex head_queue;
  QueueIndex tail_queue;
}Queue_type;

Queue_type rQ = {.head_queue = 0, .tail_queue = QUEUESIZE-1};
Queue_type transmitQ = {.head_queue = 0, .tail_queue = QUEUESIZE-1};

typedef enum {OPERATION_OK, OPERATION_ERROR} QueueOpResult;


/* operations: Read queue, write queue */

QueueOpResult QueueRead(Queue_type * queueptr, int * queue_value)
{
   QueueOpResult rtn;
   QueueIndex tailNextValue = (queueptr->tail_queue + 1) % QUEUESIZE;
   if(queueptr->head_queue != tailNextValue) 
   {
      *queue_value = queueptr->data[tailNextValue]; 
      queueptr->tail_queue = tailNextValue;
      rtn = OPERATION_OK;
   }
   else
   {
      rtn = OPERATION_ERROR;
      printf("Queue Empty\n");
   }
   return rtn;
}


QueueOpResult QueueWrite(Queue_type * queueptr, int queue_value)
{
   QueueOpResult rtn;
   
   if(queueptr->head_queue != queueptr->tail_queue)
   {
      queueptr->data[queueptr->head_queue] = queue_value; 
      queueptr->head_queue = ((queueptr->head_queue + 1) % QUEUESIZE);
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
{
  int i, j;
  QueueOpResult rtn;
  int tempdata;
  printf("hello\n");
  /* initialize queue */ 
  /*read empty queue */
  QueueRead(&rQ, &i);

  /* Write into queue  */

  for(i=0;i<=QUEUESIZE;i++)
  {
    rtn = QueueWrite(&rQ, i);
    if(rtn == 0) printf("Queue value %d\n", i);
  }
 
  /*Read first value of queue  */
  QueueRead(&rQ, &j);
  printf("%d\n", j);

  QueueWrite(&rQ, i);
  
  /* read all values from the queue  */
  for(i=0;i<=QUEUESIZE;i++)
  {
    rtn = QueueRead(&rQ, &j);
    if(rtn == 0) printf("Queue value %d\n", j);
  }
 
return (0);
}