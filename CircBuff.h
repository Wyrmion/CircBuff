/**
  ******************************************************************************
  * @file     CircBuff.h
  * @author   Wyrm
  * @brief    Header file for CircBuff.c
  * @version  V1.0.2
  * @date     26 Oct .2026
  ******************************************************************************
  */ 

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CircBuff_H__
#define __CircBuff_H__


#ifdef __cplusplus
extern "C"{
#endif

#include <stdint.h>
#include <stdlib.h>
#include "stdbool.h"

/**
 * @addtogroup Interface
 * @{
 */

/**
 * @defgroup CircBuff Cmd Circular buffer
 * @{
 */

/* Public macro -------------------------------------------------------------*/
/* Public typedef -----------------------------------------------------------*/
typedef struct CircBuff CircBuff_t; /*!< CircBuff class declaration*/
/* Public constants ---------------------------------------------------------*/
/* Public function prototypes -----------------------------------------------*/
/* Public variables ---------------------------------------------------------*/


/**
 * @defgroup CircBuff_public_func CircBuff public function
 * @{
 */

  /**
   * @defgroup CircBuff_public_ctor_dtor CircBuff constructor/destructor
   * @{
   */
  CircBuff_t* CircBuff_ctor(uint32_t size,uint32_t dept);
  void        CircBuff_dctor(CircBuff_t* cthis);
  /** @}*/

  /**
   * @defgroup CircBuff_public_push CircBuff push function
   * @{
   */
  bool  CircBuff_push(CircBuff_t* cthis,const uint8_t* src,const size_t len);
  /** @}*/
  
  /**
   * @defgroup CircBuff_public_pop CircBuff pop function
   * @{
   */
  bool    CircBuff_pop(CircBuff_t* cthis,uint8_t *dst,size_t* len);
  /** @}*/

  /**
   * @defgroup CircBuff_public_getsize CircBuff get size/free function
   * 
   */
  bool    CircBuff_IsFree(const CircBuff_t* cthis);
  size_t  CircBuff_getPushedMsgCount(const CircBuff_t* cthis);
  /** @}*/ /*End of CircBuff get size/free function group*/
/** @}*/


/** @}*/
/** @}*/

#ifdef __cplusplus
}
#endif

#endif