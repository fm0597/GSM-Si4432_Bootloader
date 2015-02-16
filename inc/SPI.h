#ifndef SD_SPI
#define SD_SPI

#define CS_ENABLE         GPIOA->BSRR = GPIO_BSRR_BR4;
#define CS_DISABLE    	  GPIOA->BSRR = GPIO_BSRR_BS4;

unsigned char spiSend(unsigned char data);
unsigned char spiRead(void);

#endif /* SD_SPI */
