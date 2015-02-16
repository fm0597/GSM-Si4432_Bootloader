#ifndef DBG_PRINT_H_INCLUDED
#define DBG_PRINT_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <stm32f10x_gpio.h>

#define DBG_USART                       USART1

#define DBGPRINT_COMMON
//#define USING_DBG_MUTEX

#ifdef USING_DBG_MUTEX
    #define TAKE_DBG_MUTEX               xSemaphoreTake(xMutexDBG_USART, 100);
    #define GIVE_DBG_MUTEX               xSemaphoreGive(xMutexDBG_USART);
#else
    #define TAKE_DBG_MUTEX
    #define GIVE_DBG_MUTEX
#endif

#ifdef DBGPRINT_COMMON

#define DBG_PRINT_BUFF_SIZE 128
extern char str[DBG_PRINT_BUFF_SIZE];

#define DBG_PRINT_0(fmt)                {TAKE_DBG_MUTEX;\
                                         memset(str, 0, DBG_PRINT_BUFF_SIZE);\
                                         sprintf(str,fmt);\
                                         USART::GetInstance()->USARTSend(str, DBG_USART);\
                                         GIVE_DBG_MUTEX;}

#define DBG_PRINT_1(fmt,arg1)           {TAKE_DBG_MUTEX;\
                                         memset(str, 0, DBG_PRINT_BUFF_SIZE);\
                                         sprintf(str,fmt,arg1);\
                                         USART::GetInstance()->USARTSend(str, DBG_USART);\
                                         GIVE_DBG_MUTEX;}

#define DBG_PRINT_2(fmt,arg1,arg2)      {TAKE_DBG_MUTEX;\
                                         memset(str, 0, DBG_PRINT_BUFF_SIZE);\
                                         sprintf(str,fmt,arg1,arg2);\
                                         USART::GetInstance()->USARTSend(str, DBG_USART);\
                                         GIVE_DBG_MUTEX;}
#else
    #define DBG_PRINT_0(fmt)
    #define DBG_PRINT_1(fmt,arg1)
    #define DBG_PRINT_2(fmt,arg1,arg2)
#endif //DBGPRINT_COMMON


#endif /* DBG_PRINT_H_INCLUDED */
