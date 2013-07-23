/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_spi.h"
#include "module_camspi.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : CamSPI_Config
**功能 : CamSPI 配置 & 設定
**輸入 : None
**輸出 : None
**使用 : CamSPI_Config();
**=====================================================================================================*/
/*=====================================================================================================*/
void CamSPI_Config( void )
{
  GPIO_InitTypeDef GPIO_InitStructure;
  SPI_InitTypeDef  SPI_InitStructure;
  DMA_InitTypeDef DMA_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_SPI2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_SPI2);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_SPI2);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  SPI_I2S_DeInit(SPI2);
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Slave;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(SPI2, &SPI_InitStructure);

  DMA_DeInit(DMA1_Stream3);
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(SPI2->DR));
  DMA_InitStructure.DMA_Memory0BaseAddr =(u32)0;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = 0xFFFF;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream3, &DMA_InitStructure);

  DMA_DeInit(DMA1_Stream4);
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&(SPI2->DR));
  DMA_InitStructure.DMA_Memory0BaseAddr =(u32)0;
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStructure.DMA_BufferSize = 0xFFFF;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream4, &DMA_InitStructure);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : CamSPI_RW
**功能 : 讀寫暫存器
**輸入 : WriteData, ReadData, BufSize
**輸出 : None
**使用 : CamSPI_RW( WriteData, ReadData, BufSize );
**=====================================================================================================*/
/*=====================================================================================================*/
void CamSPI_RW( u8* WriteData, u8* ReadData, u16 BufSize )
{
  DMA_InitTypeDef DMA_InitStruct;

  DMA_DeInit(DMA1_Stream3);
  DMA_InitStruct.DMA_Channel = DMA_Channel_0;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&(SPI2->DR));
  DMA_InitStruct.DMA_Memory0BaseAddr =(u32)(ReadData);
  DMA_InitStruct.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStruct.DMA_BufferSize = BufSize;
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;
  DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
  DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream3, &DMA_InitStruct);

  DMA_DeInit(DMA1_Stream4);
  DMA_InitStruct.DMA_Channel = DMA_Channel_0;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (u32)(&(SPI2->DR));
  DMA_InitStruct.DMA_Memory0BaseAddr =(u32)(WriteData);
  DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
  DMA_InitStruct.DMA_BufferSize = BufSize;
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
  DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;
  DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;
  DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream4, &DMA_InitStruct);

  DMA_Cmd(DMA1_Stream4, ENABLE);
  DMA_Cmd(DMA1_Stream3, ENABLE);
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, ENABLE);
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, ENABLE);
  SPI_Cmd(SPI2, ENABLE);
  while (DMA_GetFlagStatus(DMA1_Stream4, DMA_FLAG_TCIF4)==RESET);
  while (DMA_GetFlagStatus(DMA1_Stream3, DMA_FLAG_TCIF3)==RESET);
  DMA_ClearFlag(DMA1_Stream4, DMA_FLAG_TCIF4);
  DMA_ClearFlag(DMA1_Stream3, DMA_FLAG_TCIF3);
  DMA_Cmd(DMA1_Stream4, DISABLE);
  DMA_Cmd(DMA1_Stream3, DISABLE);
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx, DISABLE);
  SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Rx, DISABLE);
  SPI_Cmd(SPI2, DISABLE);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
