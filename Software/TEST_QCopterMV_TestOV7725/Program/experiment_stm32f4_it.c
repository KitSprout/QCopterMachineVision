/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_i2c.h"
#include "module_ssd1963.h"
#include "module_mt9v022.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define KEY   PBI(2)
#define LED_R PCO(15)
#define LED_G PCO(14)
#define LED_B PCO(13)

//extern u8 Image_Buf[FULL_IMAGE_SIZE];
//extern u8 Image_Buf2[FULL_IMAGE_SIZE];
//extern u16 PrintImage_Buf[FULL_IMAGE_SIZE];
//extern u16 dcmi_val[FULL_IMAGE_SIZE];
/*=====================================================================================================*/
/*=====================================================================================================*/
void SysTick_Handler( void )
{
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void DCMI_IRQHandler(void)
{
  if( DCMI_GetITStatus(DCMI_IT_FRAME)!= RESET) {
    LED_B = ~LED_B;

    TFT_SetWindow(0, 319, 0, 239);
    TFT_REG = (Com_WriteMemoryStart);
    DCMI_ClearITPendingBit(DCMI_IT_FRAME);
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void DMA1_Stream0_IRQHandler( void )
{
	I2C1_Recv_DMA_IRQ();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void DMA1_Stream6_IRQHandler( void )
{
	I2C1_Send_DMA_IRQ();
}
/*=====================================================================================================*/
/*=====================================================================================================*/
//void DMA2_Stream1_IRQHandler(void)
//{
//	if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_TCIF1) != RESET) {
//		DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_TCIF1);

//		return;
//	}

//	if(DMA_GetITStatus(DMA2_Stream1, DMA_IT_HTIF1) != RESET) {
//		DMA_ClearITPendingBit(DMA2_Stream1, DMA_IT_HTIF1);
//	}

//	if(DMA_GetCurrentMemoryTarget(DMA2_Stream1)) {
//    DMA_MemoryTargetConfig(DMA2_Stream1, (u32)Image_Buf, DMA_Memory_0);
//	}
//	else {
//    DMA_MemoryTargetConfig(DMA2_Stream1, (u32)Image_Buf, DMA_Memory_1);
//	}

//	return;
//}
/*=====================================================================================================*/
/*=====================================================================================================*/
void HardFault_Handler( void )
{
  while(1);
}
void MemManage_Handler( void )
{
  while(1);
}
void BusFault_Handler( void )
{
  while(1);
}
void UsageFault_Handler( void )
{
  while(1);
}
void SVC_Handler( void )
{
  while(1);
}
void DebugMon_Handler( void )
{
  while(1);
}
void PendSV_Handler( void )
{
  while(1);
}
void NMI_Handler( void )
{
  while(1);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
