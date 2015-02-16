#include "stm32f10x_conf.h"
#include "USART_USER.h"
#include "dbg_print.h"




int main(void)
{
    USART::GetInstance()->UsartInit(USART1, speed_115200);  // dbg usart
    USART::GetInstance()->EnableInputRingBuffer(USART1);

    DBG_PRINT_0("Hello!");

    while(1)
    {

    }

    return 0;
}
