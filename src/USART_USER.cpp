#include "RingBuffer.h"
#include <stm32f10x_gpio.h>
#include "USART_USER.h"
#include "string.h"
#include "GPIO.h"
#include "dbg_print.h"


USART* USART::pInstance = 0;
static volatile unsigned char iddleInterruptFlag = 0;
RingBuffer RBuffer(100);



//--------------------------------------------------------------------------------------


USART::USART()
{

}

//--------------------------------------------------------------------------------------


USART::USART(USART& usartCl)
{

}

//--------------------------------------------------------------------------------------


USART& USART::operator = (USART& usartCl)
{


}

//--------------------------------------------------------------------------------------


USART::~USART()
{

}

//--------------------------------------------------------------------------------------




USART* USART::GetInstance(void)
{
    if(!pInstance)
    {
        pInstance = new USART();
    }
    return pInstance;
}

//--------------------------------------------------------------------------------------


void USART::UsartInit(USART_TypeDef* USARTx, USARTspeed speed)
{
    USART_InitTypeDef   USART_InitStructure;
    GPIO_InitTypeDef    GPIOInitStructure;

    if (USARTx == USART2)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

        GPIOInitStructure.GPIO_Pin = GPIO_Pin_2;
        GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;

        GPIO_Init(GPIOA, &GPIOInitStructure);

        GPIOInitStructure.GPIO_Pin = GPIO_Pin_3;
        GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;
        GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;

        GPIO_Init(GPIOA, &GPIOInitStructure);

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
    }

    if (USARTx == USART1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

        GPIOInitStructure.GPIO_Pin = GPIO_Pin_9;
        GPIOInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
        GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;

        GPIO_Init(GPIOA, &GPIOInitStructure);

        GPIOInitStructure.GPIO_Pin = GPIO_Pin_10;
        GPIOInitStructure.GPIO_Mode = GPIO_Mode_IPU;//GPIO_Mode_IN_FLOATING;
        GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;

        GPIO_Init(GPIOA, &GPIOInitStructure);

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
    }

    if (USARTx == USART3)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

        GPIOInitStructure.GPIO_Pin   = GPIO_Pin_11;
        GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIOInitStructure.GPIO_Mode  = GPIO_Mode_IPU;
        GPIO_Init(GPIOB, &GPIOInitStructure);

        GPIOInitStructure.GPIO_Pin   = GPIO_Pin_10;
        GPIOInitStructure.GPIO_Speed = GPIO_Speed_2MHz;
        GPIOInitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
        GPIO_Init(GPIOB, &GPIOInitStructure);

        RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
    }

    switch(speed)
    {
    case speed_9600:
        USART_InitStructure.USART_BaudRate = 9600;
    break;
    case speed_19200:
        USART_InitStructure.USART_BaudRate = 19200;
    break;
    case speed_57600:
        USART_InitStructure.USART_BaudRate = 57600;
    break;
    case speed_115200:
        USART_InitStructure.USART_BaudRate = 115200;
    break;
    default:
        USART_InitStructure.USART_BaudRate = 115200;
    break;
    }
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;

    USART_Init(USARTx, &USART_InitStructure);

    USART_Cmd(USARTx, ENABLE);
}

//--------------------------------------------------------------------------------------


void USART::USARTSend(char *data, USART_TypeDef* USARTx)
{
    unsigned int length;

    length = strlen(data);

    FlushRingBuffer();
    while (length)
    {
        USART_ClearFlag(USARTx, USART_FLAG_TC);
        USART_SendData(USARTx, *data);
        while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
        data++;
        length--;
    }
}

//--------------------------------------------------------------------------------------


void USART::EnableInputRingBuffer(USART_TypeDef* USARTx)
{
    if(USARTx == USART1)
    {
        USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
        USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
        NVIC_EnableIRQ(USART1_IRQn);
    }

    if(USARTx == USART2)
    {
        USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
        USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
        NVIC_EnableIRQ(USART2_IRQn);
    }

    if(USARTx == USART3)
    {
        USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
        USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
        NVIC_EnableIRQ(USART3_IRQn);
    }
}

//-------------------------------------------------------------


void USART::DisableInputRingBuffer(USART_TypeDef* USARTx)
{
    USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART1, USART_IT_IDLE, DISABLE);
    NVIC_DisableIRQ(USART1_IRQn);
    USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART2, USART_IT_IDLE, DISABLE);
    NVIC_DisableIRQ(USART2_IRQn);
    USART_ITConfig(USART3, USART_IT_RXNE, DISABLE);
    USART_ITConfig(USART3, USART_IT_IDLE, DISABLE);
    NVIC_DisableIRQ(USART3_IRQn);
}

//--------------------------------------------------------------------------------------


unsigned int USART::ReadDataFromRxBuffer(unsigned char *data)
{
    return RBuffer.ReadData(data);
}

//--------------------------------------------------------------------------------------


void USART::FlushRingBuffer(void)
{
    RBuffer.FlushRingBuffer();
}

//--------------------------------------------------------------------------------------

unsigned char USART::CheckIdleInterruptFlag(void)
{
    if(iddleInterruptFlag)
    {
        return 1;
    }

    return 0;
}

//--------------------------------------------------------------------------------------


void USART::ResetIdleInterruptFlag(void)
{
    iddleInterruptFlag = 0;
}

//--------------------------------------------------------------------------------------


extern "C" void USART1_IRQHandler(void)
{

}

//--------------------------------------------------------------------------------------


extern "C" void USART2_IRQHandler(void)
{
    if (USART2->SR & USART_SR_RXNE)
    {
        RBuffer.WriteData(USART2->DR);
    }
    if (USART2->SR & USART_SR_IDLE)
    {
        USART2->DR;
        iddleInterruptFlag = 1;
    }
}

//--------------------------------------------------------------------------------------


extern "C" void USART3_IRQHandler(void)
{

}

//--------------------------------------------------------------------------------------
