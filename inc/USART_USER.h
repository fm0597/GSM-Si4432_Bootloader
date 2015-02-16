#ifndef USART_USER_H_INCLUDED
#define USART_USER_H_INCLUDED

#include "RingBuffer.h"

typedef enum
{
    speed_9600 = 0,
    speed_19200,
    speed_57600,
    speed_115200,
}USARTspeed;




class USART
{
public:
    static USART *GetInstance(void);
    void UsartInit(USART_TypeDef* USARTx, USARTspeed speed);
    void USARTSend(char *data, USART_TypeDef* USARTx);
    void EnableInputRingBuffer(USART_TypeDef* USARTx);
    void DisableInputRingBuffer(USART_TypeDef* USARTx);
    void FlushRingBuffer(void);
    unsigned char CheckIdleInterruptFlag(void);
    void ResetIdleInterruptFlag(void);
    unsigned int ReadDataFromRxBuffer(unsigned char *data);

private:
    USART();
    USART(USART& usartCl);
    USART& operator = (USART& usartCl);
    virtual ~USART();
    static USART *pInstance;


};

extern "C" void USART1_IRQHandler(void);
extern "C" void USART2_IRQHandler(void);
extern "C" void USART3_IRQHandler(void);


#endif /* USART_USER_H_INCLUDED */
