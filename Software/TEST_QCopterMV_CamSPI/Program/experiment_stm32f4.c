/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_usart.h"
#include "module_rs232.h"
#include "module_camspi.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define KEY   PBI(2)
#define LED_R PCO(15)
#define LED_G PCO(14)
#define LED_B PCO(13)
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
int main(void)
{
  u8 CAM_CMD = 0x00;

  u8 TxBuffer[100] = {0};
  u8 RxBuffer[100] = {0};

  SystemInit();
  GPIO_Config();
  CamSPI_Config();
  while(1) {
    switch(CAM_CMD) {
      case 0xAF:
        TxBuffer[0]  = 0x0F;
        TxBuffer[99] = 0x0F;
        CamSPI_RW(TxBuffer, RxBuffer, 100);
        break;
      case 0xCD:
        TxBuffer[0]  = 0xF0;
        TxBuffer[99] = 0xF0;
        CamSPI_RW(TxBuffer, RxBuffer, 100);
        break;
      case 0x23:
        TxBuffer[0]  = 0xFF;
        TxBuffer[99] = 0xFF;
        CamSPI_RW(TxBuffer, RxBuffer, 100);
        break;
      case 0x48:
        TxBuffer[0]  = 0x00;
        TxBuffer[99] = 0x00;
        CamSPI_RW(TxBuffer, RxBuffer, 100);
        break;
      default:
        TxBuffer[0] = SUCCESS;
        CamSPI_RW(TxBuffer, RxBuffer, 10);
        break;
    }
    CAM_CMD = RxBuffer[0];
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void )
{
	GPIO_InitTypeDef GPIO_InitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC, ENABLE);

  /* LED_R PC13 */  /* LED_G PC14 */  /* LED_B PC15 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  /* KEY PB2 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  LED_G = 1;
  LED_R = 1;
  LED_B = 1;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
