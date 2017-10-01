#include <stdio.h>
//#include "QueueCfg.h"

/* begin content of Queue Config */
#define QUEUESIZE 0x5  

typedef char QueueIndex;

typedef int QueueData;

/* end content of Queue Config  */

typedef struct 
{
  QueueData  data[QUEUESIZE];
  QueueIndex head_queue;
  QueueIndex tail_queue;
}Queue_type;

typedef enum {OPERATION_OK, OPERATION_ERROR} QueueOpResult;



QueueOpResult QueueInit(Queue_type * queueptr, QueueData invalidValue)
{
   QueueOpResult rtn;
   int i;
   for (i = 0; i < QUEUESIZE; i++)
   queueptr->data[i] = invalidValue;

   queueptr->head_queue = 0;
   queueptr->tail_queue = QUEUESIZE-1;
   rtn = OPERATION_OK;
   return rtn;
}

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

/* Test code */

Queue_type rQ;

int main(void)
{
  int i, j;
  QueueOpResult rtn;
  int tempdata;
  printf("hello\n");
  /* initialize queue */ 
  QueueInit(&rQ, 0xA5A5A5A5);
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