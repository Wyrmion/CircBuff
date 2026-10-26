/**
 ****************************************************************************
 * @file     CmdCircBuff.C
 * @author   Wyrm
 * @brief    cthis file provides code for Circl Buffer 
 * @version  V1.0.4
 * @date     26. Oct. 2026
 *************************************************************************
 */
#include <string.h>
#include <stdlib.h>

#include "CircBuff.h"
#include "wheap.h"

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
 * @brief cthis func provide code for CircBuff constructor
 * 
 * @param size CircBuff buffer size
 * @param depth circ buff depth
 * @return mem addr if mem allocated, NULL - else
 */
CircBuff_t* CircBuff_ctor(uint32_t size,uint32_t depth)
{
  if((depth==0)||(size == 0))
    return NULL;

  CircBuff_t* cthis = NULL;

  if((cthis = (CircBuff_t*)heap_malloc(sizeof(CircBuff_t)))==NULL)
    while(1); /* Bug catch */
  
  if((cthis->payload = heap_malloc(size*depth))==NULL)
    while(1); /* Bug catch*/
    
  if((cthis->info = heap_malloc(sizeof(sPayloadInfo)*depth))==NULL)
    while(1);
    
  cthis->max_size = size;
  
  cthis->depth = depth;
  cthis->head = 0;
  cthis->tail = 0;

  return cthis;
}

/**
 * @brief cthis is destructor
 * 
 * @param cthis is pointer to @ref CircBuff_t
 */
void  CircBuff_dctor(CircBuff_t* cthis)
{
  heap_free(cthis->payload);
  heap_free(cthis->info);
  heap_free(cthis);
  
  return; 
}

/**
 * @brief cthis func provide code for push data in CircBuff class
 * 
 * @param cthis pointer to @ref CircBuff 
 * @param src   pointer to data
 * @param len   data len
 * @return true  if successful push
 * @return false if circular buffer is overflow
 */
bool  CircBuff_push(CircBuff_t* cthis,const uint8_t* src,const size_t len)
{
  if(len>cthis->max_size)
    return false;

  int next;
   
  next = cthis->head + 1;              /* next is where head will point to after cthis write. */
  if (next >= cthis->depth) 
    next=0;

  if (next == cthis->tail)             /* if the head + 1 == tail, circular buffer is full  */
    return false;
  
  cthis->info[cthis->head].leng = len;  /* Save data leng information */
  memcpy(cthis->payload+(cthis->head*cthis->max_size),src,len);

  cthis->head = next;                  /* head to next data offset. */
  return true;                        /* return success to indicate successful push. */
}

/**
 * @brief Push data from CircBuff class
 * 
 * @param cthis   pointer to @ref CircBuff 
 * @param dst     pointer to output data
 * @param len     pointer to leng of data
 * @return true   if successful pop
 * @return false  if we don't have any data
 */
bool  CircBuff_pop(CircBuff_t* cthis,uint8_t *dst,size_t* len)
{
  int next;

  if (cthis->head == cthis->tail)  // if the head == tail, we don't have any data
    return false;

  next = cthis->tail + 1;  // next is where tail will point to after cthis read.
  if(next >= cthis->depth)
    next = 0;

  *len = cthis->info[cthis->tail].leng; 
  memcpy(dst,cthis->payload+(cthis->tail*cthis->max_size),cthis->info[cthis->tail].leng);
    
  cthis->tail = next;              // tail to next offset.
  return true;  // return success to indicate successful pop.
}

/**
 * @brief cthis code code for get buffer free state
 * 
 * @param cthis pointer to @ref CircBuff 
 * @return true is buffer free
 * @return false is have some data
 */
bool  CircBuff_IsFree(const CircBuff_t* cthis)
{
    if (cthis->head == cthis->tail)  
      return true;
    else
      return false;
}
/**
 * @brief Return data leng if Circbuff is not free
 * 
 * @param cthis pointer to @ref CircBuff 
 * @return size_t data leng if buffer not empty and 0 if empty
 */
size_t CircBuff_getLastDataleng(CircBuff_t* cthis)
{
  if(!CircBuff_IsFree(cthis))
    return cthis->info[cthis->tail].leng;
  else  
    return 0;
}

/**
 * @brief Returns the amount of pushed message stored
 * 
 * @param cthis pointer to @ref CircBuff 
 * @return size_t msg count
 */
size_t CircBuff_getPushedMsgCount(const CircBuff_t* cthis){return cthis->head - cthis->tail;};
/**/


/** @}*/