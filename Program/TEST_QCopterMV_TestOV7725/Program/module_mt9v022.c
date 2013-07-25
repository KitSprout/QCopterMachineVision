/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_i2c.h"
#include "module_mt9v022.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
//extern vu8 Image_Buf[FULL_IMAGE_SIZE];
//extern u8 PrintImage_Buf[FULL_IMAGE_SIZE];
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : SCCB_Read
**功能 : SCCB 讀資料
**輸入 : SlaveAddr, ReadAddr, ReadBuf
**輸出 : None
**使用 : SCCB_Read(SlaveAddr, ReadAddr, &ReadBuf);
**=====================================================================================================*/
/*=====================================================================================================*/
void SCCB_Read( u8 SlaveAddr, u8 ReadAddr, u16* ReadBuf )
{
  u8 ReadData[2] = {0};

  I2C_DMA_ReadReg(SlaveAddr, ReadAddr, ReadData, 2);

  *ReadBuf = (u16)(ReadData[0]<<8 | ReadData[1]);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : SCCB_Write
**功能 : SCCB 寫資料
**輸入 : SlaveAddr, WriteAddr, WriteBuf
**輸出 : None
**使用 : SCCB_Write(SlaveAddr, WriteAddr, WriteBuf);
**=====================================================================================================*/
/*=====================================================================================================*/
void SCCB_Write( u8 SlaveAddr, u8 WriteAddr, u16 WriteBuf )
{
  u8 WriteData[2] = {0};

  WriteData[0] = (u8)(WriteBuf >> 8);
  WriteData[1] = (u8)(WriteBuf);

  I2C_DMA_WriteReg(SlaveAddr, WriteAddr, WriteData, 2);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MT9V022_Config
**功能 : MT9V022 設定
**輸入 : None
**輸出 : None
**使用 : MT9V022_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
#define DCMI_DR_ADDRESS         0x50050028
#define FSMC_LCD_ADDRESS      	0x60020000
void MT9V022_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStruct;
  	DCMI_InitTypeDef DCMI_InitStructure;
  	DMA_InitTypeDef  DMA_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);//DCMI 
  	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//DMA2
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
                           RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);//妏夔DCMI腔GPIO奀笘

  /* AF Config **************************************************************/
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);    // MCO
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_PIXCLK
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);   // DCMI_HSYNC
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);   // DCMI_VSYNC
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_D0
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);   // DCMI_D1
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI);   // DCMI_D2
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI);   // DCMI_D3
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);   // DCMI_D4
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_D5
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);   // DCMI_D6
  GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_D7

  /* DCMI GPIO Config *******************************************************/
  /* DCMI_HSYNC PA4 */  /* DCMI_PIXCLK PA6 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStruct);
  /* DCMI_D5 PB6 */  /* DCMI_VSYNC PB7 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
  /* DCMI_D0 PC6 */  /* DCMI_D1 PC7 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOC, &GPIO_InitStruct);
  /* DCMI_D2 PE0 */  /* DCMI_D3 PE1 */  /* DCMI_D4 PE4 */  /* DCMI_D6 PE5 */  /* DCMI_D7 PE6 */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStruct);

  	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
  	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
  	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_Low;
  	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;
  	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
  	DCMI_Init(&DCMI_InitStructure);

/* DCMI Interrupts config ***************************************************/ 
    //DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE); 
    //DCMI_ITConfig(DCMI_IT_LINE, ENABLE); 
    DCMI_ITConfig(DCMI_IT_FRAME, ENABLE); 
    //DCMI_ITConfig(DCMI_IT_ERR, ENABLE); 
       
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
    NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn; 
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
    NVIC_Init(&NVIC_InitStructure);  
	
  	DMA_DeInit(DMA2_Stream1);
  	DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  	DMA_InitStructure.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;
  	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  	DMA_InitStructure.DMA_BufferSize = 1;
  	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
  	DMA_Init(DMA2_Stream1, &DMA_InitStructure);

  CAM_OE = 0;
  CAM_STANDBY = 0;
}
//void MT9V022_Config( void )
//{
//  GPIO_InitTypeDef GPIO_InitStruct;
//  DCMI_InitTypeDef DCMI_InitStruct;
//  NVIC_InitTypeDef NVIC_InitStruct;
//  DMA_InitTypeDef  DMA_InitStruct;

//  /* Clk Enable *************************************************************/
//  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB |
//                         RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);

//  /* AF Config **************************************************************/
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);    // MCO
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_PIXCLK
//  GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_DCMI);   // DCMI_HSYNC
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_DCMI);   // DCMI_VSYNC
//  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_D0
//  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_DCMI);   // DCMI_D1
//  GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_DCMI);   // DCMI_D2
//  GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_DCMI);   // DCMI_D3
//  GPIO_PinAFConfig(GPIOE, GPIO_PinSource4, GPIO_AF_DCMI);   // DCMI_D4
//  GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_D5
//  GPIO_PinAFConfig(GPIOE, GPIO_PinSource5, GPIO_AF_DCMI);   // DCMI_D6
//  GPIO_PinAFConfig(GPIOE, GPIO_PinSource6, GPIO_AF_DCMI);   // DCMI_D7

//  /* DCMI GPIO Config *******************************************************/
//  /* DCMI_XCLK PA8 */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;  
//  GPIO_Init(GPIOA, &GPIO_InitStruct);	     
//  RCC_MCO2Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_3);
//  /* DCMI_HSYNC PA4 */  /* DCMI_PIXCLK PA6 */
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_6;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOA, &GPIO_InitStruct);
//  /* DCMI_D5 PB6 */  /* DCMI_VSYNC PB7 */
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOB, &GPIO_InitStruct);
//  /* DCMI_D0 PC6 */  /* DCMI_D1 PC7 */
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOC, &GPIO_InitStruct);
//  /* DCMI_D2 PE0 */  /* DCMI_D3 PE1 */  /* DCMI_D4 PE4 */  /* DCMI_D6 PE5 */  /* DCMI_D7 PE6 */
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOE, &GPIO_InitStruct);
///* DCMI_D2 PE0 */  /* DCMI_D3 PE1 */  /* DCMI_D4 PE4 */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
//  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
//  GPIO_Init(GPIOE, &GPIO_InitStruct);

//  CAM_OE = 1;
//  CAM_STANDBY = 1;

//  /* DCMI Config ************************************************************/
//  DCMI_InitStruct.DCMI_CaptureMode = DCMI_CaptureMode_Continuous;
//  DCMI_InitStruct.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
//  DCMI_InitStruct.DCMI_PCKPolarity = DCMI_PCKPolarity_Falling;
//  DCMI_InitStruct.DCMI_VSPolarity = DCMI_VSPolarity_Low;
//  DCMI_InitStruct.DCMI_HSPolarity = DCMI_HSPolarity_Low;
//  DCMI_InitStruct.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
//  DCMI_InitStruct.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
//  DCMI_Init(&DCMI_InitStruct);

//  DCMI_ITConfig(DCMI_IT_FRAME, ENABLE); 

//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
//  NVIC_InitStruct.NVIC_IRQChannel = DCMI_IRQn;
//  NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
//  NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
//  NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
//  NVIC_Init(&NVIC_InitStruct);

//  /* DCMI DMA Config ********************************************************/
//  DMA_DeInit(DMA2_Stream1);
//  DMA_InitStruct.DMA_Channel = DMA_Channel_1;
//  DMA_InitStruct.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;
//  DMA_InitStruct.DMA_Memory0BaseAddr = FSMC_LCD_ADDRESS;//(u32)&Image_Buf;
//  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
//  DMA_InitStruct.DMA_BufferSize = 1;
//  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
//  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Disable;
//  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
//  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
//  DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
//  DMA_InitStruct.DMA_Priority = DMA_Priority_High;
//  DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Enable;
//  DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
//  DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
//  DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
//  DMA_Init(DMA2_Stream1, &DMA_InitStruct);

//	DMA_DoubleBufferModeConfig(DMA2_Stream1, (u32)Image_Buf2, DMA_Memory_0);
//	DMA_DoubleBufferModeCmd(DMA2_Stream1, ENABLE);

//  DMA_Init(DMA2_Stream1, &DMA_InitStruct);

//  CAM_OE = 1;
//  CAM_STANDBY = 0;
//}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MT9V022_Init
**功能 : 
**輸入 : 
**輸出 : 
**使用 : MT9V022_Init();
**=====================================================================================================*/
/*=====================================================================================================*/
#define MT9V022_RegSize 28
u8 MT9V022_Init( void )
{
  /* Monochrome */
  u16 i = 0;
  u16 ReadID[2] = {0};
  uc16 MT9V022_Reg[MT9V022_RegSize][2]= {

    // [Chip Control]
    // [2:0] Scan Mode (Progressive scan 0)
    // [3]   Sensor Master/Slave Mode (Master mode 1)
    // [4]   Sensor Snapshot Mode (Snapshot deisble 0)
    // [5]   Stereoscopy Mode (Stereoscopy disable 0)
    // [6]   Stereoscopic Master/Slave mode (Stereoscopic master 0)
    // [7]   Parallel Output Enable (Enable parallel output 1)
    // [8]   Simultaneous/Sequential Mode (Simultaneous mode 1)
    // [9]   Defect Pixel Correction Enable (Disable Defect Pixel Correction feature 0)
    { 0x07, 0x0188 },   // ChipControl Reg

    // [Image Dimentions]
    { 0x04,    752 },   // WindowWidth Reg // windowing off, row + col bin reduce size
    { 0x03,    480 },   // WindowHeight Reg

    // [Blanking Settings]
    { 0x05,     94 },   // HorizontalBlanking Reg
    { 0x06,     45 },   // VerticalBlanking Reg

    // [Read Mode]
    // [1:0] Row Bin (Row bin 2)
    // [3:2] Column Bin (Column bin 2)
    //         0x0 : 752*480/61FPS PCLK27MHZ
    //         ox5 : 376*240/61FPS PCLK13.5MHz
    //         0xA : 188*120/61FPS PCLK6.75MHz
    // [4]   Row Flip (0)
    // [5]   Column Flip (0)
    // [6]   Show Dark Rows (0)
    // [7]   Show Dark Columns (0)
    // [9:8] Reserved (default 3)
    { 0x0D, 0x030A },   // ReadMode Reg

    // [Row/Column Start]
    { 0x01,      1 },   // ColumnStart Reg
    { 0x02,      4 },   // RowStart Reg

    // [Shutter Settings]
    { 0x08, 0x01BB },   // ShutterWidth_1 Reg
    { 0x09, 0x01D9 },   // ShutterWidth_2 Reg
    { 0x0A, 0x0164 },   // ShutterWidthCtrl Reg

{ 0x15, 0x7F32 },
{ 0x20, 0x01D1 },
{ 0x70, 0x0004 },
{ 0x73, 0x02F7 },
{ 0xC2, 0x0840 },

{ 0x1C, 0x0003 },   //DATA_COMPRESSION

// [Shutter Width Settings]
{ 0x31, 0x001F },   // V1_Control Reg
{ 0x32, 0x001A },   // V2_Control Reg
{ 0x33, 0x0012 },   // V3_Control Reg

    // [AEC AGC Settings]
    { 0xAF, 0x0000 },   // AEC_AGC_Enable Reg

{ 0x2B, 0x0003 },
{ 0x10, 0x0040 },

{ 0x0F,  0x0011 },
{ 0x15,  0x7F32 },
{ 0x1C,  0x0002 },

// [CRT Mode ON]
{ 0x06, 0x001F },
{ 0x74, 0x0008 }

  };
   
  // Read Version
  SCCB_Read(MT9V022_I2C_ADDR, MT9V022_Version,     ReadID);
  SCCB_Read(MT9V022_I2C_ADDR, MT9V022_ChipVersion, ReadID+1);

  // Write Reg
  if((ReadID[0] == MT9V022_ID) && (ReadID[1] == MT9V022_ID)) {
    for(i=0; i<13; i++)
      SCCB_Write(MT9V022_I2C_ADDR, MT9V022_Reg[i][0], MT9V022_Reg[i][1]);
  }
  else {
    return ERROR;
  }

  // Reset
  SCCB_Write(MT9V022_I2C_ADDR, MT9V022_ChipReset, 0x01);
  Delay_1ms(10);

  return SUCCESS;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
