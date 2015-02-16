#include "SPI.h"
#include <GPIO.h>
#include <stm32f10x_spi.h>


//--------------------------------------------------------------------------------------


unsigned char spiSend(unsigned char data)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return (SPI1->DR);
}

//--------------------------------------------------------------------------------------


unsigned char spiRead(void)
{
    return spiSend(0xff);
}

//--------------------------------------------------------------------------------------



