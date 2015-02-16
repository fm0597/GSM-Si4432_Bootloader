#include <GPIO.h>
#include <stm32f10x_gpio.h>


GPIO_InitTypeDef GPIO_InitStructure;

//--------------------------------------------------------------------------------------


void GpioInit(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = (LED_GSM_PIN | FLASH_CS_PIN);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(LED_GSM_PORT , &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = (LED_TRANS_TX_PIN | LED_TRANS_RX_PIN | LM_PWR_PIN | GSM_PWR_PIN);
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(MODEM_PORT , &GPIO_InitStructure);
}

//--------------------------------------------------------------------------------------


void SpiInit(void){
    SPI_InitTypeDef SPI_Init_var;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

    //вывод управлени€ SS: выход двухтактный, общего назначени€,50MHz
    GPIO_InitStructure.GPIO_Pin = CS_SPI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_PORT , &GPIO_InitStructure);


    //вывод SCK: выход двухтактный, альтернативна€ функци€, 50MHz
    GPIO_InitStructure.GPIO_Pin = SCK_SPI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_PORT , &GPIO_InitStructure);


    //вывод MISO: вход цифровой с подт€гивающим резистором, подт€жка к плюсу
    GPIO_InitStructure.GPIO_Pin = MISO_SPI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_PORT , &GPIO_InitStructure);

    //вывод MOSI: выход двухтактный, альтернативна€ функци€, 50MHz
    GPIO_InitStructure.GPIO_Pin = MOSI_SPI;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SPI_PORT , &GPIO_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2ENR_SPI1EN, ENABLE);
    SPI_Init_var.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_8; //for 72MHz
    SPI_Init_var.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_Init_var.SPI_CPOL = SPI_CPOL_Low;
    SPI_Init_var.SPI_DataSize = SPI_DataSize_8b;
    SPI_Init_var.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_Init_var.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_Init_var.SPI_Mode = SPI_Mode_Master;
    SPI_Init_var.SPI_NSS = SPI_NSS_Soft;
    SPI_Init(SPI1, &SPI_Init_var);
    SPI_Cmd(SPI1, ENABLE);
}

//--------------------------------------------------------------------------------------


void ModemGpioInit(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = MODEM_SDN_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(MODEM_PORT , &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = MODEM_IRQ_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(MODEM_PORT , &GPIO_InitStructure);
}

//--------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------
