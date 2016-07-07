/*=====================================================================================================*/
/*=====================================================================================================*/
#include "drivers\stm32f4_system.h"
#include "drivers\stm32f4_i2cSimu.h"
#include "modules\otm8009.h"
#include "modules\ov7725.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define DCMI_DR_ADDRESS   0x50050028
#define FSMC_LCD_ADDRESS  0x60020000

static SimuI2C_InitTypeDef SimuI2C;
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : OV7725_Config
**功能 : OV7725 Config
**輸入 : None
**輸出 : None
**使用 : OV7725_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void OV7725_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  DCMI_InitTypeDef DCMI_InitStruct;
  DMA_InitTypeDef  DMA_InitStruct;
//  I2C_InitTypeDef  I2C_InitStruct;
  NVIC_InitTypeDef NVIC_InitStruct;

  /* OV7725 Clk ****************************************************************/
  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);  // DCMI 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);  // DMA2
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

  /* OV7725 AF *****************************************************************/
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7,  GPIO_AF_DCMI);  // DCMI_VSYN
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4,  GPIO_AF_DCMI);  // DCMI_HSYN
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6,  GPIO_AF_DCMI);  // DCMI_PCLK
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6,  GPIO_AF_DCMI);  // DCMI_D0
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7,  GPIO_AF_DCMI);  // DCMI_D1
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF_DCMI);  // DCMI_D2
  GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_DCMI);  // DCMI_D3
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource4,  GPIO_AF_DCMI);  // DCMI_D4
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource3,  GPIO_AF_DCMI);  // DCMI_D5
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource5,  GPIO_AF_DCMI);  // DCMI_D6
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource6,  GPIO_AF_DCMI);  // DCMI_D7
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource5,  GPIO_AF_TIM2);  // DCMI_XCLK
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource8,  GPIO_AF_I2C1);  // SCCB_SCL
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9,  GPIO_AF_I2C1);  // SCCB_SDA

  /* OV7725 GPIO ***************************************************************/
  /* DCMI */
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4  | GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_7;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_6  | GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_3;
  GPIO_Init(GPIOD, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_6;
  GPIO_Init(GPIOE, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_Init(GPIOG, &GPIO_InitStruct);

  /* SCCB */
//  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_2MHz;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
//  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_NOPULL;

//  GPIO_InitStruct.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9;
//  GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* OV7725 SCCB ***************************************************************/
//  I2C_DeInit(I2C1);
//  I2C_Cmd(I2C1, ENABLE);
//  I2C_InitStruct.I2C_Mode                = I2C_Mode_I2C;
//  I2C_InitStruct.I2C_DutyCycle           = I2C_DutyCycle_2;
//  I2C_InitStruct.I2C_OwnAddress1         = 0xFE;
//  I2C_InitStruct.I2C_Ack                 = I2C_Ack_Enable;
//  I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
//  I2C_InitStruct.I2C_ClockSpeed          = 30000;
//  I2C_Init(I2C1, &I2C_InitStruct);

  /* OV7725 DCMI ***************************************************************/
  DCMI_InitStruct.DCMI_CaptureMode      = DCMI_CaptureMode_Continuous;  //DCMI_CaptureMode_SnapShot
  DCMI_InitStruct.DCMI_SynchroMode      = DCMI_SynchroMode_Hardware;
  DCMI_InitStruct.DCMI_PCKPolarity      = DCMI_PCKPolarity_Rising;
  DCMI_InitStruct.DCMI_VSPolarity       = DCMI_VSPolarity_High;
  DCMI_InitStruct.DCMI_HSPolarity       = DCMI_HSPolarity_Low;
  DCMI_InitStruct.DCMI_CaptureRate      = DCMI_CaptureRate_All_Frame;
  DCMI_InitStruct.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
  DCMI_Init(&DCMI_InitStruct); 

  /* OV7725 DCMI DMA ***********************************************/ 
  DMA_DeInit(DMA2_Stream1);
  DMA_InitStruct.DMA_Channel            = DMA_Channel_1;  
  DMA_InitStruct.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStruct.DMA_Memory0BaseAddr    = (uint32_t)FSMC_LCD_ADDRESS;//SDRAM_BANK_ADDR;//FSMC_LCD_ADDRESS;
  DMA_InitStruct.DMA_DIR                = DMA_DIR_PeripheralToMemory;
  DMA_InitStruct.DMA_BufferSize         = 1;  //FRAME_W * FRAME_H >> 1;
  DMA_InitStruct.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc          = DMA_MemoryInc_Disable;  //DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStruct.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;
  DMA_InitStruct.DMA_Mode               = DMA_Mode_Circular;
  DMA_InitStruct.DMA_Priority           = DMA_Priority_High;
  DMA_InitStruct.DMA_FIFOMode           = DMA_FIFOMode_Enable;  //DMA_FIFOMode_Disable;
  DMA_InitStruct.DMA_FIFOThreshold      = DMA_FIFOThreshold_Full;
  DMA_InitStruct.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
  DMA_InitStruct.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
  DMA_Init(DMA2_Stream1, &DMA_InitStruct);

  /* DCMI Interrupts config ***************************************************/ 
  DCMI_ITConfig(DCMI_IT_FRAME, ENABLE); 

  NVIC_InitStruct.NVIC_IRQChannel                   = DCMI_IRQn; 
  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1; 
  NVIC_InitStruct.NVIC_IRQChannelSubPriority        = 1; 
  NVIC_InitStruct.NVIC_IRQChannelCmd                = ENABLE;   
  NVIC_Init(&NVIC_InitStruct);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
#define TIMx                    TIM14
#define TIMx_CLK_ENABLE()       RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE)
#define TIMx_OCxInit            TIM_OC1Init
#define TIMx_OCxPreloadConfig   TIM_OC1PreloadConfig

#define TIMx_GPIO_PIN           GPIO_Pin_7
#define TIMx_GPIO_PORT          GPIOA
#define TIMx_GPIO_AF            GPIO_AF_TIM14
#define TIMx_GPIO_SOURCE        GPIO_PinSource7

void OV7725_XCLK_ON( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStruct;
  TIM_OCInitTypeDef TIM_OCInitStruct;

  /* TIMX Clk *****************************************************************/
  TIMx_CLK_ENABLE();

  /* GPIO AF Config ***********************************************************/
  GPIO_PinAFConfig(TIMx_GPIO_PORT, TIMx_GPIO_SOURCE, TIMx_GPIO_AF);

  /* GPIO Config **************************************************************/
  GPIO_InitStruct.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd  = GPIO_PuPd_UP;

  GPIO_InitStruct.GPIO_Pin   = TIMx_GPIO_PIN;
  GPIO_Init(TIMx_GPIO_PORT, &GPIO_InitStruct);

  /* TIM Base Config ***********************************************************/
  TIM_TimeBaseStruct.TIM_Prescaler     = 0;
  TIM_TimeBaseStruct.TIM_Period        = 2 - 1;
  TIM_TimeBaseStruct.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStruct.TIM_CounterMode   = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStruct);

  /* TIM OC Config *************************************************************/
  TIM_OCInitStruct.TIM_OCMode      = TIM_OCMode_PWM1;
  TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStruct.TIM_Pulse       = 1;
  TIM_OCInitStruct.TIM_OCPolarity  = TIM_OCPolarity_High;
  TIMx_OCxInit(TIMx, &TIM_OCInitStruct);
  TIMx_OCxPreloadConfig(TIMx, TIM_OCPreload_Enable);

  /* TIM Enable ****************************************************************/
  TIM_ARRPreloadConfig(TIMx, ENABLE);
  TIM_Cmd(TIMx, ENABLE);
  TIM_CtrlPWMOutputs(TIMx, ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : OV7725_Init
**功能 : OV7725 Init
**輸入 : None
**輸出 : state
**使用 : OV7725_Init();
**=====================================================================================================*/
/*=====================================================================================================*/
#define OV_REG_NUM 79 
static const uint8_t OV_reg[OV_REG_NUM][2] = {

  {0x32,0x00},
  {0x2a,0x00},
  {0x11,0x03},
#ifdef RESOLUTION_VGA
  {0x12,0x06},  // VGA RGB565, 640*480
#else
  {0x12,0x46},  // QVGA RGB565, 320*240
#endif

  {0x42,0x7f},
  {0x4d,0x00},//0x09
  {0x63,0xf0},
  {0x64,0x1f},
  {0x65,0x20},
  {0x66,0x00},
  {0x67,0x00},
  {0x69,0x50},  
 
   
  {0x13,0xff},
  {0x0d,0x41},//PLL
  {0x0f,0x01},////////////////////////
  {0x14,0x06},

  {0x24,0x75},
  {0x25,0x63},
  {0x26,0xd1},
  {0x2b,0xff},
  {0x6b,0xaa},
  
  {0x8e,0x10},
  {0x8f,0x00},
  {0x90,0x00},//
  {0x91,0x00},//
  {0x92,0x00},//
  {0x93,0x00},
  
  {0x94,0x2c},
  {0x95,0x24},
  {0x96,0x08},
  {0x97,0x14},
  {0x98,0x24},
  {0x99,0x38},
  {0x9a,0x9e},
  {0x15,0x00},
  {0x9b,0x00},//set luma 
  {0x9c,0x20},//set contrast
  {0xa7,0x40},//set saturation  
  {0xa8,0x40},//set saturation 
  {0xa9,0x80},//set hue 
  {0xaa,0x80},//set hue 
  
  {0x9e,0x81},
  {0xa6,0x06},

  {0x7e,0x0c},
  {0x7f,0x16},
  {0x80,0x2a},
  {0x81,0x4e},
  {0x82,0x61},
  {0x83,0x6f},
  {0x84,0x7b},
  {0x85,0x86},
  {0x86,0x8e},
  {0x87,0x97},
  {0x88,0xa4},
  {0x89,0xaf},
  {0x8a,0xc5},
  {0x8b,0xd7},
  {0x8c,0xe8},
  {0x8d,0x20},

  {0x33,0x40},
  {0x34,0x00},//7f
  //{0x23,0x01},
  {0x22,0xaf},
  {0x23,0x01},
  
  {0x49,0x10},
  {0x4a,0x10},
  {0x4b,0x14},
  {0x4c,0x17},
  {0x46,0x05},
  
  {0x47,0x08},
  {0x0e,0x01},
  {0x0c,0x60},
  {0x09,0x03},

#ifdef RESOLUTION_VGA
  {0x29,0xA0},  // VGA
  {0x2C,0xF0},  // VGA
#else
  {0x29,0x50},  // QVGA
  {0x2C,0x78},  // QVGA
#endif

  //{0x0c,0x00},
  {0x00,0x00},
  {0x00,0x00},
  {0x00,0x60},
};

static uint8_t SCCB_Read( uint8_t readAddr, uint8_t *readByte )
{
  return SimuI2C_ReadReg(&SimuI2C, 0x42, readAddr, readByte);
}

static uint8_t SCCB_Write( uint8_t writeAddr, uint8_t writeByte )
{
  return SimuI2C_WriteReg(&SimuI2C, 0x42, writeAddr, writeByte);
}

static uint16_t OV_readDeviceID( void )
{
  uint8_t deviceID[2] = {0};
  SCCB_Read(0x0A, &deviceID[0]);
  SCCB_Read(0x0B, &deviceID[1]);
  return ((deviceID[0] << 8) | deviceID[1]);
}

uint8_t OV7725_Init( void )
{
  OV7725_Config();
  OV7725_XCLK_ON();

  // SCCB Init
  SimuI2C.PinSCL    = GPIO_Pin_8;
  SimuI2C.PortSCL   = GPIOB;
  SimuI2C.PinSDA    = GPIO_Pin_9;
  SimuI2C.PortSDA   = GPIOB;
  SimuI2C.Freguency = 16;
  SimuI2C_Config(&SimuI2C);
  delay_ms(20);

  // Read ID & Check
  uint16_t deviceID = OV_readDeviceID();
  if(deviceID != 0x7721)
    return ERROR;
  delay_ms(10);

  // OV7725 Init
  if(SCCB_Write(0x12, 0x80) != SUCCESS) // Reset SCCB
    return ERROR;
  delay_ms(5);
  
  for(uint8_t i = 0; i < OV_REG_NUM; i++) {
    delay_ms(1);
    if(SCCB_Write(OV_reg[i][0], OV_reg[i][1]) != SUCCESS)
      return ERROR;
  }

  return SUCCESS;
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : OV7725_Start
**功能 : OV7725 Start
**輸入 : None
**輸出 : None
**使用 : OV7725_Start();
**=====================================================================================================*/
/*=====================================================================================================*/
void OV7725_Start( void )
{
  DMA_Cmd(DMA2_Stream1, ENABLE);
  DCMI_Cmd(ENABLE);
  DCMI_CaptureCmd(ENABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
