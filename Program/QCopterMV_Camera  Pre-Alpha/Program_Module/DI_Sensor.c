////////////////////////////////////////////////////////////
      /* 
       guanfu_wang  
       http://mcudiy.taobao.com/
      */
///////////////////////////////////////////////////////////
#include "stm32f4_system.h"
#include "DI_Sensor.h"
#include "module_ssd1963.h"

u16 ImageBuf[FULL_IMAGE_SIZE];

void OV7725_Init( void )
{
  u16 OV7725_ID = 0;

  // SCCB Init
  SCCB_Init();
  Delay_1ms(2);

  // Read ID & Check
  OV7725_ID = OV_ReadID();
  while(OV7725_ID != 0x7721) {

  }

  // OV7725 Init
  while(1==OV_Init());
  
}
void Cam_Init( void )
{
  GPIO_InitTypeDef GPIO_InitStruct;
  DCMI_InitTypeDef DCMI_InitStructure;
  DMA_InitTypeDef  DMA_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_DCMI, ENABLE);//DCMI 
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//DMA2
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | 
                         RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOE, ENABLE);//使能DCMI的GPIO時鐘

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

  DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot;
  DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
  DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
  DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_High;
  DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;
  DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_All_Frame;
  DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
  DCMI_Init(&DCMI_InitStructure); 

/* DCMI Interrupts config ***************************************************/ 
  DCMI_ITConfig(DCMI_IT_FRAME, ENABLE); 

  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1); 
  NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn; 
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;   
  NVIC_Init(&NVIC_InitStructure);  

  DMA_DeInit(DMA2_Stream1);
  DMA_InitStructure.DMA_Channel = DMA_Channel_1;  
  DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;	
  DMA_InitStructure.DMA_Memory0BaseAddr = (u32)ImageBuf;//FSMC_LCD_ADDRESS;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = FULL_IMAGE_SIZE/2;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;  
  DMA_Init(DMA2_Stream1, &DMA_InitStructure);
}

unsigned char   OV_Init(void)
{
  	unsigned char  i;

  Cam_Init();
	SCCB_Init();
	if(OV_WriteReg(0x12, 0x80)) //Reset SCCB
	{
          return 1 ;//錯誤返回
	}
	Delay_1ms(5);
  
  	for(i=0;i<OV_REG_NUM;i++)
  	{
          if(OV_WriteReg(OV_reg[i][0],OV_reg[i][1])){return 1;}
  	}
	return 0; 
}
void Cam_Start(void)
{
  TFT_SetWindow(0, 319, 0, 239);

  DMA_Cmd(DMA2_Stream1, ENABLE);
  DCMI_Cmd(ENABLE);
  DCMI_CaptureCmd(ENABLE);
  TFT_REG = (Com_WriteMemoryStart);
}

void OV_HW(unsigned int  hstart,unsigned int vstart,unsigned int hstop,unsigned int vstop)
{
	u8 v;
	OV_WriteReg(0x17,(hstart>>3)&0xff);//HSTART
	OV_WriteReg(0x18,(hstop>>3)&0xff);//HSTOP
	OV_ReadReg(0x32,&v);
	v=(v&0xc0)|((hstop&0x7)<<3)|(hstart&0x7);
	OV_WriteReg(0x32,v);//HREF
	
	OV_WriteReg(0x19,(vstart>>2)&0xff);//VSTART 開始高8位
	OV_WriteReg(0x1a,(vstop>>2)&0xff);//VSTOP	結束高8位
	OV_ReadReg(0x03,&v);
	v=(v&0xf0)|((vstop&0x3)<<2)|(vstart&0x3);	
	OV_WriteReg(0x03,v);//VREF																 
	OV_WriteReg(0x11,0x00);
}
/////////////////////////////////////
void SCCB_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SCCB_SID_OUT(void)//設置SCCB_SID為輸出
{
  	GPIO_InitTypeDef  GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;               
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
void SCCB_SID_IN(void)//設置SCCB_SID為輸入
{
  	GPIO_InitTypeDef  GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void SCCB_Start(void)
{
    SCCB_SID_H();     //數據線高電平
    Delay_1us(2);
    SCCB_SIC_H();	   //在時鐘線高的時候數據線由高至低
    Delay_1us(2);
    SCCB_SID_L();
    Delay_1us(2);
    SCCB_SIC_L();	 //數據線恢復低電平，單操作函數必要
    Delay_1us(2);
}

void SCCB_Stop(void)
{
    SCCB_SID_L();
    Delay_1us(2);
    SCCB_SIC_H();	
    Delay_1us(2);  
    SCCB_SID_H();	
    Delay_1us(2);  
}

void noAck(void)
{	
	SCCB_SID_H();	
	Delay_1us(2);	
	SCCB_SIC_H();	
	Delay_1us(2);	
	SCCB_SIC_L();	
	Delay_1us(2);	
	SCCB_SID_L();	
	Delay_1us(2);
}

unsigned char  SCCB_Write(unsigned char  m_data)
{
	unsigned char  j,tem,K;
        K=m_data;
	for(j=0;j<8;j++) //循環8次發送數據
	{
		if((K&0x80)==0x80)
		{
			SCCB_SID_H();	
		}
		else
		{
			SCCB_SID_L();	
		}
		Delay_1us(4);
		SCCB_SIC_H();	
		Delay_1us(3);
                K<<=1;
		SCCB_SIC_L();	
		Delay_1us(1);
	}
	Delay_1us(2);
	SCCB_DATA_IN;
	Delay_1us(2);
	SCCB_SIC_H();	
	Delay_1us(2);
	if(SCCB_SID_STATE)tem=0;//SDA=1發送失敗
	else tem=1;//SDA=0發送成功，返回1
	SCCB_SIC_L();	
	Delay_1us(2);	
        SCCB_DATA_OUT;
	return tem;  
}

unsigned char SCCB_Read(void)
{
	unsigned char read,j;
	read=0x00;
	
	SCCB_DATA_IN;
	Delay_1us(2);
	for(j=8;j>0;j--) //循環8次接收數據
	{		     
		Delay_1us(2);
		SCCB_SIC_H();
		Delay_1us(2);
		read=read<<1;
		if(SCCB_SID_STATE)read=read+1; 
		SCCB_SIC_L();
		Delay_1us(2);
	}	
        SCCB_DATA_OUT;
	return read;
}

//寫OV7670寄存器
unsigned char  OV_WriteReg(unsigned char  regID, unsigned char  regDat)
{
	SCCB_Start();//發送SCCB 總線開始傳輸命令
	if(SCCB_Write(0x42)==0)//寫地址
	{
		SCCB_Stop();//發送SCCB 總線停止傳輸命令
		return 1;//錯誤返回
	}
	Delay_1us(10);
  	if(SCCB_Write(regID)==0)//積存器ID
	{
		SCCB_Stop();//發送SCCB 總線停止傳輸命令
		return 2;//錯誤返回
	}
	Delay_1us(10);
  	if(SCCB_Write(regDat)==0)//寫數據到積存器
	{
		SCCB_Stop();//發送SCCB 總線停止傳輸命令
		return 3;//錯誤返回
	}
  	SCCB_Stop();//發送SCCB 總線停止傳輸命令	
  	return 0;//成功返回
}

//讀OV7660寄存器
unsigned char  OV_ReadReg(unsigned char  regID, unsigned char  *regDat)
{
	//通過寫操作設置寄存器地址
	SCCB_Start();
	if(SCCB_Write(0x42)==0)//寫地址
	{
		SCCB_Stop();//發送SCCB 總線停止傳輸命令
		return 1;//錯誤返回
	}
	Delay_1us(10);
  	if(SCCB_Write(regID)==0)//積存器ID
	{
		SCCB_Stop();//發送SCCB 總線停止傳輸命令
		return 2;//錯誤返回
	}
	SCCB_Stop();//發送SCCB 總線停止傳輸命令	
	Delay_1us(10);	
	//設置寄存器地址後，才是讀
	SCCB_Start();
	if(SCCB_Write(0x43)==0)//讀地址
	{
		SCCB_Stop();//發送SCCB 總線停止傳輸命令
		return 3;//錯誤返回
	}
	Delay_1us(10);
  	*regDat=SCCB_Read();//返回讀到的值
  	noAck();//發送NACK命令
  	SCCB_Stop();//發送SCCB 總線停止傳輸命令
  	return 0;//成功返回
}



unsigned short  OV_ReadID(void)    // 0x21
{
	unsigned char  tempH, tempL;
	OV_ReadReg(0x0A,&tempH);
  OV_ReadReg(0x0B,&tempL);
  return (tempH<<8 | tempL);
}
