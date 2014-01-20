/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_usart.h"
#include "stm32f4_i2c.h"
#include "module_rs232.h"
#include "module_ssd1963.h"
#include "DI_Sensor.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define KEY   PBI(2)
#define LED_R PCO(15)
#define LED_G PCO(14)
#define LED_B PCO(13)
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );

void TFT_SetWindows( u16 CoordiX_START, u16 CoordiX_END, u16 CoordiY_START, u16 CoordiY_END );
/*=====================================================================================================*/
/*=====================================================================================================*/
#define ReadReg_Size 32

int main( void )
{
  u32 Point = 0;
  u16 OV7725_ID = 0;

  SystemInit();
  GPIO_Config();

  Delay_1ms(1);
  SSD1963_Config();
  Delay_1ms(50);
  SSD1963_Init();
  Delay_1ms(20);
  TFT_Clear(WHITE);

  // SCCB Init
  SCCB_Init();
  Delay_1ms(2);

  // Read ID & Check
  OV7725_ID = OV_ReadID();
  while(OV7725_ID != 0x7721) {
    LED_R = ~LED_R;
    Delay_100ms(1);
  }

  // OV7725 Init
  while(1==OV_Init());
  Cam_Start();

  while(1) {
    LED_G = ~LED_G;
    Delay_100ms(1);
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
