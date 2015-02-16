#ifndef GPIO_H_INCLUDED
#define GPIO_H_INCLUDED

#include <stm32f10x_gpio.h>

#define ON                  1
#define OFF                 0

#define LED_GSM_PORT            GPIOA
#define LED_GSM_PIN             GPIO_Pin_8
#define LED_GSM_PIN_ON()        LED_GSM_PORT->ODR |= LED_GSM_PIN
#define LED_GSM_PIN_OFF()       LED_GSM_PORT->ODR &= ~LED_GSM_PIN

#define LED_TRANS_TX_PORT       GPIOB
#define LED_TRANS_TX_PIN        GPIO_Pin_15
#define LED_TRANS_TX_ON()       LED_TRANS_TX_PORT->ODR |= LED_TRANS_TX_PIN
#define LED_TRANS_TX_OFF()      LED_TRANS_TX_PORT->ODR &= ~LED_TRANS_TX_PIN

#define LED_TRANS_RX_PORT       GPIOB
#define LED_TRANS_RX_PIN        GPIO_Pin_14
#define LED_TRANS_RX_ON()       LED_TRANS_RX_PORT->ODR |= LED_TRANS_RX_PIN
#define LED_TRANS_RX_OFF()      LED_TRANS_RX_PORT->ODR &= ~LED_TRANS_RX_PIN

#define LM_PWR_PORT             GPIOB
#define LM_PWR_PIN              GPIO_Pin_13
#define LM_PWR_OFF()             LM_PWR_PORT->ODR |= LM_PWR_PIN
#define LM_PWR_ON()            LM_PWR_PORT->ODR &= ~LM_PWR_PIN

#define GSM_PWR_PORT            GPIOB
#define GSM_PWR_PIN             GPIO_Pin_12
#define GSM_PWR_ON()            GSM_PWR_PORT->ODR |= GSM_PWR_PIN
#define GSM_PWR_OFF()           GSM_PWR_PORT->ODR &= ~GSM_PWR_PIN

#define MODEM_PORT              GPIOB
#define MODEM_SDN_PIN           GPIO_Pin_0
#define MODEM_SDN_OFF()         MODEM_PORT->ODR |= MODEM_SDN_PIN
#define MODEM_SDN_ON()          MODEM_PORT->ODR &= ~MODEM_SDN_PIN
#define MODEM_IRQ_PIN           GPIO_Pin_1
#define MODEM_CHECK_EVENT()     !(MODEM_PORT->IDR & MODEM_IRQ_PIN)


#define SPI_PORT                GPIOA
#define CS_SPI                  GPIO_Pin_4
#define SCK_SPI                 GPIO_Pin_5
#define MOSI_SPI                GPIO_Pin_7
#define MISO_SPI                GPIO_Pin_6

#define FLASH_CS_PIN            GPIO_Pin_1
#define FLASH_CS_OFF()          SPI_PORT->ODR |= FLASH_CS_PIN
#define FLASH_CS_ON()           SPI_PORT->ODR &= ~FLASH_CS_PIN




void GpioInit(void);
void ModemGpioInit(void);
void SpiInit(void);

#endif /* GPIO_H_INCLUDED */
