/*=====================================================================================================*/
/*=====================================================================================================*/
#include "drivers\stm32f4_system.h"
#include "modules\otm8009.h"
#include "algorithms\string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LCD_LIG_PIN                 GPIO_Pin_8
#define LCD_LIG_GPIO_PORT           GPIOA

#define BLIGHT_PWM
#ifdef BLIGHT_PWM
  #define LCD_LIG_TIMx              TIM1
  #define LCD_LIG_TIMx_CHANNEL      TIM_CHANNEL_1
  #define LCD_TIMx_CLK_ENABLE()     RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE)
  #define LCD_LIG_AF                GPIO_AF_TIM1
  #define LCD_LIG_SOURCE            GPIO_PinSource8
  #define LCD_LIG                   LCD_LIG_TIMx->CCR1
  #define LCD_OCxInit               TIM_OC1Init
  #define LCD_OCxPreloadConfig      TIM_OC1PreloadConfig

  #define BLIGHT_MAX                255
  #define BLIGHT_MIN                0
  #define BLIGHT_DEFAULT            200
  #define BLIGHT_STEP               5
#else
  #define LCD_LIG_H()               __GPIO_SET(LCD_LIG_GPIO_PORT, LCD_LIG_PIN)
  #define LCD_LIG_L()               __GPIO_RST(LCD_LIG_GPIO_PORT, LCD_LIG_PIN)
  #define BLIGHT_MAX                1
  #define BLIGHT_MIN                0
  #define BLIGHT_DEFAULT            1
#endif

#define LCD_RST_PIN                 GPIO_Pin_7
#define LCD_RST_GPIO_PORT           GPIOG
#define LCD_RST_H()                 __GPIO_SET(LCD_RST_GPIO_PORT, LCD_RST_PIN)
#define LCD_RST_L()                 __GPIO_RST(LCD_RST_GPIO_PORT, LCD_RST_PIN)
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : OTM8009_Config
**功能 : OTM8009 Config
**輸入 : None
**輸出 : None
**使用 : OTM8009_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void OTM8009_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  FMC_NORSRAMInitTypeDef FMC_InitStruct;
  FMC_NORSRAMTimingInitTypeDef TimingInitStruct; 

  /* FMC Clk Init *************************************************************/
  RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);

  /* FMC AF *******************************************************************/
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource0,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource1,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource4,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource5,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource7,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource11, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource7,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource8,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9,  GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FMC);
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FMC);


  /* FMC GPIO *****************************************************************/
	GPIO_InitStruct.GPIO_Pin   = LCD_RST_PIN;
	GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(LCD_RST_GPIO_PORT, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;

  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_7  |
                               GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_14 |
                               GPIO_Pin_15;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 | GPIO_Pin_11 |
                               GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  LCD_BLigConfig();

  TimingInitStruct.FMC_AddressSetupTime      = 0x05;
  TimingInitStruct.FMC_AddressHoldTime       = 0x05;
  TimingInitStruct.FMC_DataSetupTime         = 0x05;
  TimingInitStruct.FMC_BusTurnAroundDuration = 0x00;
  TimingInitStruct.FMC_CLKDivision           = 0x005;
  TimingInitStruct.FMC_DataLatency           = 0x00;
  TimingInitStruct.FMC_AccessMode            = FMC_AccessMode_B;

  FMC_InitStruct.FMC_Bank                  = FMC_Bank1_NORSRAM1;
  FMC_InitStruct.FMC_DataAddressMux        = FMC_DataAddressMux_Disable;
  FMC_InitStruct.FMC_MemoryType            = FMC_MemoryType_NOR;
  FMC_InitStruct.FMC_MemoryDataWidth       = FMC_NORSRAM_MemoryDataWidth_16b;
  FMC_InitStruct.FMC_BurstAccessMode       = FMC_BurstAccessMode_Disable;
  FMC_InitStruct.FMC_AsynchronousWait      = FMC_AsynchronousWait_Disable;
  FMC_InitStruct.FMC_WaitSignalPolarity    = FMC_WaitSignalPolarity_Low;
  FMC_InitStruct.FMC_WrapMode              = FMC_WrapMode_Disable;
  FMC_InitStruct.FMC_WaitSignalActive      = FMC_WaitSignalActive_BeforeWaitState;
  FMC_InitStruct.FMC_WriteOperation        = FMC_WriteOperation_Enable;
  FMC_InitStruct.FMC_WaitSignal            = FMC_WaitSignal_Disable;
  FMC_InitStruct.FMC_ExtendedMode          = FMC_ExtendedMode_Disable;
  FMC_InitStruct.FMC_WriteBurst            = FMC_WriteBurst_Disable;
  FMC_InitStruct.FMC_ReadWriteTimingStruct = &TimingInitStruct;
  FMC_InitStruct.FMC_WriteTimingStruct     = &TimingInitStruct;

  FMC_NORSRAMInit(&FMC_InitStruct);
  FMC_NORSRAMCmd(FMC_Bank1_NORSRAM1, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_BLigConfig
**功能 : Back Light Config
**輸入 : None
**輸出 : None
**使用 : LCD_BLigConfig();
**=====================================================================================================*/
/*=====================================================================================================*/
void LCD_BLigConfig( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;

#ifdef BLIGHT_PWM
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  /* PWM Clk Init *************************************************************/
  LCD_TIMx_CLK_ENABLE();

  GPIO_PinAFConfig(LCD_LIG_GPIO_PORT, LCD_LIG_SOURCE, LCD_LIG_AF);

  /* TFT_LIG */
  GPIO_InitStruct.GPIO_Pin   = LCD_LIG_PIN;
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_Init(LCD_LIG_GPIO_PORT, &GPIO_InitStruct);

  /************************** PWM Output **************************************/
  /* TIM2 Time Base */
  TIM_TimeBaseStruct.TIM_Period        = BLIGHT_MAX;
  TIM_TimeBaseStruct.TIM_Prescaler     = 0;
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(LCD_LIG_TIMx, &TIM_TimeBaseStruct);

  /* TIM2 OC */
  TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse       = BLIGHT_MIN;
  TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;
  LCD_OCxInit(LCD_LIG_TIMx, &TIM_OCInitStruct);
  LCD_OCxPreloadConfig(LCD_LIG_TIMx, TIM_OCPreload_Enable);

  /* Enable */
  TIM_ARRPreloadConfig(LCD_LIG_TIMx, ENABLE);
  TIM_Cmd(LCD_LIG_TIMx, ENABLE);
  TIM_CtrlPWMOutputs(LCD_LIG_TIMx, ENABLE);

#else
  /* LIG Pin *******************************************************************/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

  GPIO_InitStruct.GPIO_Pin   = LCD_LIG_PIN;
  GPIO_Init(LCD_LIG_GPIO_PORT, &GPIO_InitStruct);

  LCD_LIG_L();

#endif
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_WriteCmd
**功能 : Write Command or Address
**輸入 : writeCmd
**輸出 : None
**使用 : LCD_WriteCmd(0x0000);
**====================================================================================================*/
/*====================================================================================================*/
static void LCD_WriteCmd( uint16_t writeCmd )
{
  LCD_REG = writeCmd;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_WriteData
**功能 : Write Data
**輸入 : writeData
**輸出 : None
**使用 : LCD_WriteData(0x0000);
**====================================================================================================*/
/*====================================================================================================*/
static void LCD_WriteData( uint16_t writeData )
{
  LCD_RAM = writeData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_WriteReg
**功能 : Write Register
**輸入 : writeAddr, writeData
**輸出 : None
**使用 : LCD_WriteReg(0x0000, 0x0000);
**=====================================================================================================*/
/*=====================================================================================================*/
static void LCD_WriteReg( uint16_t writeAddr, uint16_t writeData )
{
  LCD_REG = writeAddr;
  LCD_RAM = writeData;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_ReadData
**功能 : Read Data
**輸入 : ReadData
**輸出 : None
**使用 : ReadData = LCD_ReadData();
**=====================================================================================================*/
/*=====================================================================================================*/
static uint16_t LCD_ReadData( void )
{
  return LCD_RAM;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_ReadReg
**功能 : Read Register
**輸入 : ReadAddr
**輸出 : ReadData
**使用 : ReadData = LCD_ReadReg(0x0000);
**=====================================================================================================*/
/*=====================================================================================================*/
//static uint16_t LCD_ReadReg( uint16_t readAddr )
//{
//  LCD_REG = readAddr;
//  return LCD_RAM;
//}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : OTM8009_Init
**功能 : OTM8009 Init
**輸入 : None
**輸出 : None
**使用 : OTM8009_Init();
**=====================================================================================================*/
/*=====================================================================================================*/
int8_t OTM8009_Init( void )
{
  uint16_t tmp[8] = {0};
  uint32_t deviceID = 0;

  //  Hardware Reset
	LCD_RST_L();
	delay_ms(15);
	LCD_RST_H();
	delay_ms(5);

  // Check Device
  LCD_WriteCmd(0xA100);
  tmp[0] = LCD_ReadData(); // default 0x00
  tmp[1] = LCD_ReadData(); // default 0x01
  tmp[2] = LCD_ReadData(); // default 0x8B
  tmp[3] = LCD_ReadData(); // default 0x80
  tmp[4] = LCD_ReadData(); // default 0x09
  tmp[5] = LCD_ReadData(); // default 0xFF
  deviceID = Byte32(uint32_t, tmp[1], tmp[2], tmp[3], tmp[4]);
  if((tmp[0] != 0x00) || (tmp[5] != 0xFF) || (deviceID != OTM8009_ID))
    return ERROR;

  LCD_WriteReg(0xFF00, 0x80);
  LCD_WriteReg(0xFF01, 0x09);
  LCD_WriteReg(0xFF02, 0x01);
  LCD_WriteReg(0xFF80, 0x80);
  LCD_WriteReg(0xFF81, 0x09);
  LCD_WriteReg(0xFF82, 0x01);

  LCD_WriteReg(0xC0B4, 0x50);
  LCD_WriteReg(0xC489, 0x08);
  LCD_WriteReg(0xC0A3, 0x00);
  LCD_WriteReg(0xC582, 0xA3);
  LCD_WriteReg(0xC590, 0x96);
  LCD_WriteReg(0xC591, 0x87);
  LCD_WriteReg(0xC800, 0x73);
  LCD_WriteReg(0xC801, 0x71);

  LCD_WriteReg(0xD900, 0x6A);
  delay_ms(1);

  LCD_WriteReg(0xE100, 0x09);
  LCD_WriteReg(0xE101, 0x0A);
  LCD_WriteReg(0xE102, 0x0E);
  LCD_WriteReg(0xE103, 0x0D);
  LCD_WriteReg(0xE104, 0x07);
  LCD_WriteReg(0xE105, 0x18);
  LCD_WriteReg(0xE106, 0x0D);
  LCD_WriteReg(0xE107, 0x0D);
  LCD_WriteReg(0xE108, 0x01);
  LCD_WriteReg(0xE109, 0x04);
  LCD_WriteReg(0xE10A, 0x05);
  LCD_WriteReg(0xE10B, 0x06);
  LCD_WriteReg(0xE10C, 0x0D);
  LCD_WriteReg(0xE10D, 0x22);
  LCD_WriteReg(0xE10E, 0x20);
  LCD_WriteReg(0xE10F, 0x05);

  LCD_WriteReg(0xE200, 0x09);
  LCD_WriteReg(0xE201, 0x0A);
  LCD_WriteReg(0xE202, 0x0E);
  LCD_WriteReg(0xE203, 0x0D);
  LCD_WriteReg(0xE204, 0x07);
  LCD_WriteReg(0xE205, 0x18);
  LCD_WriteReg(0xE206, 0x0D);
  LCD_WriteReg(0xE207, 0x0D);
  LCD_WriteReg(0xE208, 0x01);
  LCD_WriteReg(0xE209, 0x04);
  LCD_WriteReg(0xE20A, 0x05);
  LCD_WriteReg(0xE20B, 0x06);
  LCD_WriteReg(0xE20C, 0x0D);
  LCD_WriteReg(0xE20D, 0x22);
  LCD_WriteReg(0xE20E, 0x20);
  LCD_WriteReg(0xE20F, 0x05);

  LCD_WriteReg(0xC181, 0x66);

  LCD_WriteReg(0xC1A1, 0x08);
  LCD_WriteReg(0xC0A3, 0x1B);
  LCD_WriteReg(0xC481, 0x83);
  LCD_WriteReg(0xC592, 0x01);
  LCD_WriteReg(0xC5B1, 0xA9);

  LCD_WriteReg(0xCE80, 0x85);
  LCD_WriteReg(0xCE81, 0x03);
  LCD_WriteReg(0xCE82, 0x00);
  LCD_WriteReg(0xCE83, 0x84);
  LCD_WriteReg(0xCE84, 0x03);
  LCD_WriteReg(0xCE85, 0x00);

  LCD_WriteReg(0xCE86, 0x83);

  LCD_WriteReg(0xCE87, 0x03);
  LCD_WriteReg(0xCE88, 0x00);
  LCD_WriteReg(0xCE89, 0x82);
  LCD_WriteReg(0xCE8A, 0x03);
  LCD_WriteReg(0xCE8B, 0x00);

  LCD_WriteReg(0xCEA0, 0x38);
  LCD_WriteReg(0xCEA1, 0x02);
  LCD_WriteReg(0xCEA2, 0x03);
  LCD_WriteReg(0xCEA3, 0x21);
  LCD_WriteReg(0xCEA4, 0x00);
  LCD_WriteReg(0xCEA5, 0x00);
  LCD_WriteReg(0xCEA6, 0x00);
  LCD_WriteReg(0xCEA7, 0x38);
  LCD_WriteReg(0xCEA8, 0x01);
  LCD_WriteReg(0xCEA9, 0x03);
  LCD_WriteReg(0xCEAA, 0x22);
  LCD_WriteReg(0xCEAB, 0x00);
  LCD_WriteReg(0xCEAC, 0x00);
  LCD_WriteReg(0xCEAD, 0x00);

  LCD_WriteReg(0xCEB0, 0x38);
  LCD_WriteReg(0xCEB1, 0x00);
  LCD_WriteReg(0xCEB2, 0x03);
  LCD_WriteReg(0xCEB3, 0x23);
  LCD_WriteReg(0xCEB4, 0x00);
  LCD_WriteReg(0xCEB5, 0x00);
  LCD_WriteReg(0xCEB6, 0x00);
  LCD_WriteReg(0xCEB7, 0x30);
  LCD_WriteReg(0xCEB8, 0x00);
  LCD_WriteReg(0xCEB9, 0x03);
  LCD_WriteReg(0xCEBA, 0x24);
  LCD_WriteReg(0xCEBB, 0x00);
  LCD_WriteReg(0xCEBC, 0x00);
  LCD_WriteReg(0xCEBD, 0x00);

  LCD_WriteReg(0xCEC0, 0x30);
  LCD_WriteReg(0xCEC1, 0x01);
  LCD_WriteReg(0xCEC2, 0x03);
  LCD_WriteReg(0xCEC3, 0x25);
  LCD_WriteReg(0xCEC4, 0x00);
  LCD_WriteReg(0xCEC5, 0x00);
  LCD_WriteReg(0xCEC6, 0x00);
  LCD_WriteReg(0xCEC7, 0x30);
  LCD_WriteReg(0xCEC8, 0x02);
  LCD_WriteReg(0xCEC9, 0x03);
  LCD_WriteReg(0xCECA, 0x26);
  LCD_WriteReg(0xCECB, 0x00);
  LCD_WriteReg(0xCECC, 0x00);
  LCD_WriteReg(0xCECD, 0x00);

  LCD_WriteReg(0xCED0, 0x30);
  LCD_WriteReg(0xCED1, 0x03);
  LCD_WriteReg(0xCED2, 0x03);
  LCD_WriteReg(0xCED3, 0x27);
  LCD_WriteReg(0xCED4, 0x00);
  LCD_WriteReg(0xCED5, 0x00);
  LCD_WriteReg(0xCED6, 0x00);
  LCD_WriteReg(0xCED7, 0x30);
  LCD_WriteReg(0xCED8, 0x04);
  LCD_WriteReg(0xCED9, 0x03);
  LCD_WriteReg(0xCEDA, 0x28);
  LCD_WriteReg(0xCEDB, 0x00);
  LCD_WriteReg(0xCEDC, 0x00);
  LCD_WriteReg(0xCEDD, 0x00);

  LCD_WriteReg(0xCFC0, 0x00);
  LCD_WriteReg(0xCFC1, 0x00);
  LCD_WriteReg(0xCFC2, 0x00);
  LCD_WriteReg(0xCFC3, 0x00);
  LCD_WriteReg(0xCFC4, 0x00);
  LCD_WriteReg(0xCFC5, 0x00);
  LCD_WriteReg(0xCFC6, 0x00);
  LCD_WriteReg(0xCFC7, 0x00);
  LCD_WriteReg(0xCFC8, 0x00);
  LCD_WriteReg(0xCFC9, 0x00);

  LCD_WriteReg(0xCFD0, 0x00);

  LCD_WriteReg(0xCBC0, 0x00);
  LCD_WriteReg(0xCBC1, 0x00);
  LCD_WriteReg(0xCBC2, 0x00);
  LCD_WriteReg(0xCBC3, 0x00);
  LCD_WriteReg(0xCBC4, 0x04);
  LCD_WriteReg(0xCBC5, 0x04);
  LCD_WriteReg(0xCBC6, 0x04);
  LCD_WriteReg(0xCBC7, 0x04);
  LCD_WriteReg(0xCBC8, 0x04);
  LCD_WriteReg(0xCBC9, 0x04);
  LCD_WriteReg(0xCBCA, 0x00);
  LCD_WriteReg(0xCBCB, 0x00);
  LCD_WriteReg(0xCBCC, 0x00);
  LCD_WriteReg(0xCBCD, 0x00);
  LCD_WriteReg(0xCBCE, 0x00);

  LCD_WriteReg(0xCBD0, 0x00);
  LCD_WriteReg(0xCBD1, 0x00);
  LCD_WriteReg(0xCBD2, 0x00);
  LCD_WriteReg(0xCBD3, 0x00);
  LCD_WriteReg(0xCBD4, 0x00);
  LCD_WriteReg(0xCBD5, 0x00);
  LCD_WriteReg(0xCBD6, 0x00);
  LCD_WriteReg(0xCBD7, 0x00);
  LCD_WriteReg(0xCBD8, 0x00);
  LCD_WriteReg(0xCBD9, 0x04);
  LCD_WriteReg(0xCBDA, 0x04);
  LCD_WriteReg(0xCBDB, 0x04);
  LCD_WriteReg(0xCBDC, 0x04);
  LCD_WriteReg(0xCBDD, 0x04);
  LCD_WriteReg(0xCBDE, 0x04);

  LCD_WriteReg(0xCBE0, 0x00);
  LCD_WriteReg(0xCBE1, 0x00);
  LCD_WriteReg(0xCBE2, 0x00);
  LCD_WriteReg(0xCBE3, 0x00);
  LCD_WriteReg(0xCBE4, 0x00);
  LCD_WriteReg(0xCBE5, 0x00);
  LCD_WriteReg(0xCBE6, 0x00);
  LCD_WriteReg(0xCBE7, 0x00);
  LCD_WriteReg(0xCBE8, 0x00);
  LCD_WriteReg(0xCBE9, 0x00);

  LCD_WriteReg(0xCC80, 0x00);
  LCD_WriteReg(0xCC81, 0x00);
  LCD_WriteReg(0xCC82, 0x00);
  LCD_WriteReg(0xCC83, 0x00);
  LCD_WriteReg(0xCC84, 0x0C);
  LCD_WriteReg(0xCC85, 0x0A);
  LCD_WriteReg(0xCC86, 0x10);
  LCD_WriteReg(0xCC87, 0x0E);
  LCD_WriteReg(0xCC88, 0x03);
  LCD_WriteReg(0xCC89, 0x04);

  LCD_WriteReg(0xCC90, 0x00);
  LCD_WriteReg(0xCC91, 0x00);
  LCD_WriteReg(0xCC92, 0x00);
  LCD_WriteReg(0xCC93, 0x00);
  LCD_WriteReg(0xCC94, 0x00);
  LCD_WriteReg(0xCC95, 0x00);
  LCD_WriteReg(0xCC96, 0x00);
  LCD_WriteReg(0xCC97, 0x00);
  LCD_WriteReg(0xCC98, 0x00);
  LCD_WriteReg(0xCC99, 0x00);
  LCD_WriteReg(0xCC9A, 0x00);
  LCD_WriteReg(0xCC9B, 0x00);
  LCD_WriteReg(0xCC9C, 0x00);
  LCD_WriteReg(0xCC9D, 0x00);
  LCD_WriteReg(0xCC9E, 0x0B);

  LCD_WriteReg(0xCCA0, 0x09);
  LCD_WriteReg(0xCCA1, 0x0F);
  LCD_WriteReg(0xCCA2, 0x0D);
  LCD_WriteReg(0xCCA3, 0x01);
  LCD_WriteReg(0xCCA4, 0x02);
  LCD_WriteReg(0xCCA5, 0x00);
  LCD_WriteReg(0xCCA6, 0x00);
  LCD_WriteReg(0xCCA7, 0x00);
  LCD_WriteReg(0xCCA8, 0x00);
  LCD_WriteReg(0xCCA9, 0x00);
  LCD_WriteReg(0xCCAA, 0x00);
  LCD_WriteReg(0xCCAB, 0x00);
  LCD_WriteReg(0xCCAC, 0x00);
  LCD_WriteReg(0xCCAD, 0x00);
  LCD_WriteReg(0xCCAE, 0x00);

  LCD_WriteReg(0xCCB0, 0x00);
  LCD_WriteReg(0xCCB1, 0x00);
  LCD_WriteReg(0xCCB2, 0x00);
  LCD_WriteReg(0xCCB3, 0x00);
  LCD_WriteReg(0xCCB4, 0x0D);
  LCD_WriteReg(0xCCB5, 0x0F);
  LCD_WriteReg(0xCCB6, 0x09);
  LCD_WriteReg(0xCCB7, 0x0B);
  LCD_WriteReg(0xCCB8, 0x02);
  LCD_WriteReg(0xCCB9, 0x01);

  LCD_WriteReg(0xCCC0, 0x00);
  LCD_WriteReg(0xCCC1, 0x00);
  LCD_WriteReg(0xCCC2, 0x00);
  LCD_WriteReg(0xCCC3, 0x00);
  LCD_WriteReg(0xCCC4, 0x00);
  LCD_WriteReg(0xCCC5, 0x00);
  LCD_WriteReg(0xCCC6, 0x00);
  LCD_WriteReg(0xCCC7, 0x00);
  LCD_WriteReg(0xCCC8, 0x00);
  LCD_WriteReg(0xCCC9, 0x00);
  LCD_WriteReg(0xCCCA, 0x00);
  LCD_WriteReg(0xCCCB, 0x00);
  LCD_WriteReg(0xCCCC, 0x00);
  LCD_WriteReg(0xCCCD, 0x00);
  LCD_WriteReg(0xCCCE, 0x0E);

  LCD_WriteReg(0xCCD0, 0x10);
  LCD_WriteReg(0xCCD1, 0x0A);
  LCD_WriteReg(0xCCD2, 0x0C);
  LCD_WriteReg(0xCCD3, 0x04);
  LCD_WriteReg(0xCCD4, 0x03);
  LCD_WriteReg(0xCCD5, 0x00);
  LCD_WriteReg(0xCCD6, 0x00);
  LCD_WriteReg(0xCCD7, 0x00);
  LCD_WriteReg(0xCCD8, 0x00);
  LCD_WriteReg(0xCCD9, 0x00);
  LCD_WriteReg(0xCCDA, 0x00);
  LCD_WriteReg(0xCCDB, 0x00);
  LCD_WriteReg(0xCCDC, 0x00);
  LCD_WriteReg(0xCCDD, 0x00);
  LCD_WriteReg(0xCCDE, 0x00);

  LCD_WriteReg(0x3500, 0x00);
  LCD_WriteReg(0x3A00, 0x55);
  LCD_WriteReg(0x3600, 0xA0);

  LCD_WriteCmd(0x1100);
  delay_ms(1);

  LCD_WriteCmd(0x2900);
  delay_ms(1);

  LCD_WriteReg(0x2A00, 0x00);
  LCD_WriteReg(0x2A01, 0x00);
  LCD_WriteReg(0x2A02, 0x01);
  LCD_WriteReg(0x2A03, 0xDF);
  LCD_WriteReg(0x2B00, 0x00);
  LCD_WriteReg(0x2B01, 0x00);
  LCD_WriteReg(0x2B02, 0x03);
  LCD_WriteReg(0x2B03, 0x1F);

  LCD_WriteCmd(0x2C00);
  delay_ms(1);

  LCD_Clear(WHITE);
  LCD_SetBackLight(BLIGHT_DEFAULT);

  return SUCCESS;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_Clear
**功能 : Clear Windows
**輸入 : color
**輸出 : None
**使用 : LCD_Clear(BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_Clear( uint16_t color )
{
  uint32_t point = LCD_W * LCD_H;

  LCD_SetWindow(0, 0, LCD_W - 1, LCD_H - 1);

  while(point--)
    LCD_WriteData(color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_SetCursor
**功能 : Set Cursor
**輸入 : posX, posY
**輸出 : None
**使用 : LCD_SetCursor(posX, posY);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_SetCursor( uint16_t posX, uint16_t posY )
{
  LCD_WriteReg(0x2A00, posX >> 8);
  LCD_WriteReg(0x2A01, posX & 0x00FF);
  LCD_WriteReg(0x2B00, posY >> 8);
  LCD_WriteReg(0x2B01, posY & 0x00FF);
  LCD_WriteCmd(0x2C00);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_SetWindow
**功能 : Set Window
**輸入 : posX1, posY1, posX2, posY2
**輸出 : None
**使用 : LCD_SetWindow(X1, Y1, X2, Y2);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_SetWindow( uint16_t posX1, uint16_t posY1, uint16_t posX2, uint16_t posY2 )
{
  LCD_WriteReg(0x2A00, posX1 >> 8);
  LCD_WriteReg(0x2A01, posX1 & 0x00FF);
  LCD_WriteReg(0x2A02, posX2 >> 8);
  LCD_WriteReg(0x2A03, posX2 & 0x00FF);
  LCD_WriteReg(0x2B00, posY1 >> 8);
  LCD_WriteReg(0x2B01, posY1 & 0x00FF);
  LCD_WriteReg(0x2B02, posY2 >> 8);
  LCD_WriteReg(0x2B03, posY2 & 0x00FF);
  LCD_WriteCmd(0x2C00);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_SetBackLight
**功能 : Set LCD BackLight
**輸入 : backLight
**輸出 : None
**使用 : LCD_SetBackLight(BLIGHT_DEFAULT);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_SetBackLight( int16_t backLight )
{
#ifdef BLIGHT_PWM
  if(backLight <= BLIGHT_MIN)       LCD_LIG = BLIGHT_MIN;
  else if(backLight >= BLIGHT_MAX)  LCD_LIG = BLIGHT_MAX;
  else                              LCD_LIG = backLight;

#else
  if(backLight == 0)  LCD_LIG_L();
  else                LCD_LIG_H();

#endif
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawPixel
**功能 : Draw a Pixel
**輸入 : posX, posY, color
**輸出 : None
**使用 : LCD_DrawPixel(posX, posY, color);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawPixel( uint16_t posX, uint16_t posY, uint16_t color )
{
  LCD_SetWindow(posX, posY, posX, posY);
  LCD_WriteData(color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawLineX
**功能 : Draw X-Axis Line
**輸入 : posX, posY, length, color
**輸出 : None
**使用 : LCD_DrawLineX(posX, posY, length, color);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawLineX( uint16_t posX, uint16_t posY, uint16_t length, uint16_t color )
{
  LCD_SetWindow(posX, posY, posX + length - 1, posY);
  while(length--)
    LCD_WriteData(color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawLineY
**功能 : Draw Y-Axis Line
**輸入 : posX, posY, length, color
**輸出 : None
**使用 : LCD_DrawLineY(posX, posY, length, color);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawLineY( uint16_t posX, uint16_t posY, uint16_t length, uint16_t color )
{
  LCD_SetWindow(posX, posY, posX, posY + length - 1);
  while(length--)
    LCD_WriteData(color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawLine
**功能 : Draw Line
**輸入 : posX1, posY1, posX2, posY2, color
**輸出 : None
**使用 : LCD_DrawLine(posX1, posY1, posX2, posY2, color);
**====================================================================================================*/
/*====================================================================================================*/
//void LCD_DrawLine( uint16_t posX1, uint16_t posY1, uint16_t posX2, uint16_t posY2, uint16_t color )
//{
//}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawRect
**功能 : Draw Rectangle
**輸入 : posX, posY, width, height, color
**輸出 : None
**使用 : LCD_DrawRect(posX, posY, width, height, color);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawRect( uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t color )
{
  LCD_DrawLineX(posX,             posY,              width,  color);
  LCD_DrawLineX(posX,             posY + height - 1, width,  color);
  LCD_DrawLineY(posX,             posY,              height, color);
  LCD_DrawLineY(posX + width - 1, posY,              height, color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawRectFill
**功能 : Draw Rectangle Fill
**輸入 : posX, posY, Length, width, height, color
**輸出 : None
**使用 : LCD_DrawRectFill(posX, posY, width, height, color);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawRectFill( uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t color )
{
  uint32_t point = width * height;

  LCD_SetWindow(posX, posY, posX + width - 1, posY + height - 1);

  while(point--)
    LCD_WriteData(color);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawCircle
**功能 : Draw Circle
**輸入 : posX, posY, radius, color
**輸出 : None
**使用 : LCD_DrawCircle(posX, posY, radius, color);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawCircle( uint16_t posX, uint16_t posY, uint16_t radius, uint16_t color )
{
  int32_t D = 3 - (radius << 1);
  uint32_t curX = 0;
  uint32_t curY = radius;

  while(curX <= curY) {
    LCD_DrawPixel(posX + curX, posY - curY, color);
    LCD_DrawPixel(posX - curX, posY - curY, color);
    LCD_DrawPixel(posX + curY, posY - curX, color);
    LCD_DrawPixel(posX - curY, posY - curX, color);
    LCD_DrawPixel(posX + curX, posY + curY, color);
    LCD_DrawPixel(posX - curX, posY + curY, color);
    LCD_DrawPixel(posX + curY, posY + curX, color);
    LCD_DrawPixel(posX - curY, posY + curX, color);

    if(D < 0) {
      D += (curX << 2) + 6;
    }
    else {
      D += ((curX - curY) << 2) + 10;
      curY--;
    }
    curX++;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_DrawPic
**功能 : Draw Picture
**輸入 : posX, posY, width, height, *pPic
**輸出 : None
**使用 : LCD_DrawPic(posX, posY, width, height, pic);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_DrawPic( uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, const uint16_t *pic )
{
  uint32_t point = height * width;

  LCD_SetWindow(posX, posY, posX + width - 1, posY + height - 1);

  for(uint32_t i = 0; i < point; i++)
    LCD_WriteData(pic[i]);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_PutChar
**功能 : Put Char
**輸入 : posX, posY, *pFont, word, fontColor, backColor
**輸出 : None
**使用 : LCD_PutChar(posX, posY, pFont, word, WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_PutChar( uint16_t posX, uint16_t posY, sFONT *pFont, uint8_t word, uint16_t fontColor, uint16_t backColor )
{
  uint8_t tmp = 0;
  uint8_t font_h = pFont->height;
  uint8_t font_w = pFont->width;
  uint16_t point = 0;

  if(pFont->type == dirH) {
    point = (word - ' ') * font_h;
    for(uint8_t i = 0; i < font_h; i++) {
      tmp = pFont->table[point + i];
      for(uint8_t j = 0; j < font_w; j++) {
        if((tmp << j) & 0x80)
          LCD_DrawPixel(posX + j, posY + i, fontColor);
        else
          LCD_DrawPixel(posX + j, posY + i, backColor);
      }
    }
  }
  else {
    point = (word - ' ') * font_w;
    for(uint8_t i = 0; i < font_w; i++) {
      tmp = pFont->table[point + i];
      for(uint8_t j = 0; j < font_h; j++) {
        if((tmp >> j) & 0x01)
          LCD_DrawPixel(posX + i, posY + j, fontColor);
        else
          LCD_DrawPixel(posX + i, posY + j, backColor);
      }
    }
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_PutStr
**功能 : Put String
**輸入 : posX, posY, pString, fontColor, backColor
**輸出 : None
**使用 : LCD_PutStr(10, 10, FONT8, "OLED TEST ... ", WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_PutStr( uint16_t posX, uint16_t posY, sFONT *pFont, char *pString, uint16_t fontColor, uint16_t backColor )
{
  uint16_t offsetX = 0;

  while(*pString) {
    LCD_PutChar(posX + offsetX, posY, pFont, *pString, fontColor, backColor);
    pString++;
    offsetX += pFont->width;
  }
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : LCD_PutNum
**功能 : Put Number
**輸入 : posX, posY, *pFont, type, lens, number, fontColor, backColor
**輸出 : None
**使用 : LCD_PutNum(posX, posY, pFont, Type_D, lens, number, WHITE, BLACK);
**====================================================================================================*/
/*====================================================================================================*/
void LCD_PutNum( uint16_t posX, uint16_t posY, sFONT *pFont, StringType type, uint8_t lens, int32_t number, uint16_t fontColor, uint16_t backColor )
{
  char strBuf[16] = {0};

  num2Str(type, lens, strBuf, number);
  LCD_PutStr(posX, posY, pFont, strBuf, fontColor, backColor);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : LCD_TestColoBar
**功能 : Draw Color Bar
**輸入 : None
**輸出 : None
**使用 : LCD_TestColoBar();
**=====================================================================================================*/
/*=====================================================================================================*/
#define COLOR_NUMBER      (20)
#define COLOR_BAR_HEIGHT  (LCD_W / COLOR_NUMBER)  // 96/16 = 6

void LCD_TestColoBar( void )
{
  uint16_t drawColor[COLOR_NUMBER] = {
    WHITE,
    RED,
    GREEN,
    BLUE,
    MAGENTA,
    GRED,
    GBLUE,
    BRED,
    BROWN,
    BRRED,
    CYAN,
    GRAY,
    YELLOW,
    DARKBLUE,
    LIGHTBLUE,
    GRAYBLUE,
    LIGHTGREEN,
    LGRAY,
    LGRAYBLUE,
    LBBLUE
  };

  LCD_SetWindow(0, 0, LCD_W - 1, LCD_H - 1);

  for(uint32_t i = 0; i < COLOR_NUMBER; i++) {
    uint32_t j = (uint32_t)(LCD_H * LCD_W / COLOR_NUMBER);
    while(j--)
      LCD_WriteData(drawColor[i]);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void LCD_TestFunction( void )
{
  LCD_TestColoBar();

  for(uint32_t i = 0; i < 4; i++)
    LCD_DrawRect(i, i, LCD_W - 2 * i, LCD_H - 2 * i, GREEN);
  for(uint32_t i = 4; i < 12; i++)
    LCD_DrawRect(i, i, LCD_W - 2 * i, LCD_H - 2 * i, BLACK);
  for(uint32_t i = 0; i < 4; i++)
    LCD_DrawLineX(0, 200 + i, LCD_W , BLUE);
  for(uint32_t i = 0; i < 4; i++)
    LCD_DrawLineY(400 + i, 0, LCD_H, RED);

  LCD_DrawRect(23, 23,     LCD_W - 2 * 23, LCD_H - 2 * 23, RED);
  LCD_DrawRect(24, 24,     LCD_W - 2 * 24, LCD_H - 2 * 24, YELLOW);
  LCD_DrawRectFill(25, 25, LCD_W - 2 * 25, LCD_H - 2 * 25, RED);

  for(uint32_t i = 0; i < 4; i++)
    LCD_DrawCircle(100, 100, 50 - i, BLACK);

  LCD_PutStr(CENTER(FONT16, "Hello World !!!"), LINE(FONT16, 12), &FONT16, "Hello World !!!", WHITE, RED);
  LCD_PutStr(CENTER(FONT16, "PutNum Test"), LINE(FONT16, 13), &FONT16, "PutNum Test",  WHITE, RED);

  uint32_t num = 0;

  do {
    LCD_PutNum(CENTER(FONT16, "   "), LINE(FONT16, 15), &FONT16, Type_D, 3, num, WHITE, RED);
    delay_ms(5);
  } while(num++ != 255);
  do {
    LCD_PutNum(CENTER(FONT16, "   "), LINE(FONT16, 15), &FONT16, Type_D, 3, num, WHITE, RED);
    delay_ms(5);
  } while(num--);

  while(1) {
    LCD_DrawRectFill(730, 50, 22, 22, RED);
    delay_ms(200);
    LCD_DrawRectFill(730, 50, 22, 22, GREEN);
    delay_ms(200);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
