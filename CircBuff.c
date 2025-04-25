/**
 ****************************************************************************
 * @file     CmdCircBuff.C
 * @author   Kukushkin A.V.
 * @brief    This file provides code for Circl Buffer 
 * @version  V1.0.1
 * @date     29. Oct. 2024
 *************************************************************************
 */
 
#include "CircBuff.h"
#include "string.h"
#include <stdlib.h>
#include "../../Memory/MyHeap/my_heap.h"

/**
 * @addtogroup CircBuff 
 * @{
 */


/* Private constants ---------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/

/**
 * @brief Current payload information class
 * 
 */
typedef struct
{
  size_t  leng;
}sPayloadInfo;

/**
 * @brief CmdCircBuff  class 
 * 
 */
struct CircBuff{
    
    
    sPayloadInfo    *info;   
    uint8_t         *payload;

    uint32_t        max_size;     /*!< CircBuff max data size*/
    uint32_t        depth;    /*!< CircBuff dept*/
    
    int             head;     /*!< CircBuff head*/  
    int             tail;     /*!< CircBuff tail*/
};


/* Private constants ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Exported functions -------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/


/**
 * @brief this func provide code for CircBuff constructor
 * 
 * @param size CircBuff buffer size
 * @param depth circ buff depth
 * @return mem addr if mem allocated, NULL - else
 */
CircBuff_t* CircBuff_ctor(size_t size,uint32_t depth)
{
  if((depth==0)||(size == 0))
    return NULL;

  CircBuff_t* this = NULL;

  if((this = (CircBuff_t*)heap_malloc(sizeof(CircBuff_t)))==NULL)
    while(1); /* Bug catch */
  
  if((this->payload = heap_malloc(size*depth))==NULL)
    while(1); /* Bug catch*/
    
  if((this->info = heap_malloc(sizeof(sPayloadInfo)*depth))==NULL)
    while(1);
    
  this->max_size = size;
  
  this->depth = depth;
  this->head = 0;
  this->tail = 0;

  return this;
}

/**
 * @brief this is destructor
 * 
 * @param this is pointer to @ref CircBuff_t
 */
void  CircBuff_dctor(CircBuff_t* this)
{
  heap_free(this->payload);
  heap_free(this->info);
  heap_free(this);
  
  return; 
}

/**
 * @brief this func provide code for push data in CircBuff class
 * 
 * @param this pointer to @ref CircBuff 
 * @param src   pointer to data
 * @param len   data len
 * @return true  if successful push
 * @return false if circular buffer is overflow
 */
bool  CircBuff_push(CircBuff_t* this,const uint8_t* src,const size_t len)
{
  if(len>this->max_size)
    return false;

  int next;
   
  next = this->head + 1;              /* next is where head will point to after this write. */
  if (next >= this->depth) 
    next=0;

  if (next == this->tail)             /* if the head + 1 == tail, circular buffer is full  */
    return false;
  
  this->info[this->head].leng = len;  /* Save data leng information */
  memcpy(this->payload+(this->head*this->max_size),src,len);

  this->head = next;                  /* head to next data offset. */
  return true;                        /* return success to indicate successful push. */
}

/**
 * @brief Push data from CircBuff class
 * 
 * @param this   pointer to @ref CircBuff 
 * @param dst     pointer to output data
 * @param len     pointer to leng of data
 * @return true   if successful pop
 * @return false  if we don't have any data
 */
bool  CircBuff_pop(CircBuff_t* this,uint8_t *dst,size_t* len)
{
  int next;

  if (this->head == this->tail)  // if the head == tail, we don't have any data
    return false;

  next = this->tail + 1;  // next is where tail will point to after this read.
  if(next >= this->depth)
    next = 0;

  *len = this->info[this->tail].leng; 
  memcpy(dst,this->payload+(this->tail*this->max_size),this->info[this->tail].leng);
    
  this->tail = next;              // tail to next offset.
  return true;  // return success to indicate successful pop.
}

/**
 * @brief this code code for get buffer free state
 * 
 * @param this pointer to @ref CircBuff 
 * @return true is buffer free
 * @return false is have some data
 */
bool  CircBuff_IsFree(const CircBuff_t* this)
{
    if (this->head == this->tail)  
      return true;
    else
      return false;
}
/**
 * @brief Return data leng if Circbuff is not free
 * 
 * @param this pointer to @ref CircBuff 
 * @return size_t data leng if buffer not empty and 0 if empty
 */
size_t CircBuff_getLastDataleng(CircBuff_t* this)
{
  if(!CircBuff_IsFree(this))
    return this->info[this->tail].leng;
  else  
    return 0;
}

/**
 * @brief Returns the amount of pushed message stored
 * 
 * @param this pointer to @ref CircBuff 
 * @return size_t msg count
 */
size_t CircBuff_getPushedMsgCount(const CircBuff_t* this){return this->head - this->tail;};
/**/


/** @}*/