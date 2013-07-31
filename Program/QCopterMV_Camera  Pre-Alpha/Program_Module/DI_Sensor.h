
////////////////////////////////////////////////////////////
      /* 
       guanfu_wang  
       http://mcudiy.taobao.com/
      */
///////////////////////////////////////////////////////////

#ifndef __DCMI_H
#define __DCMI_H
#include "stm32f4xx_conf.h"

#define DCMI_DR_ADDRESS       	0x50050028   
#define FSMC_LCD_ADDRESS      	0x60020000
 
#define OV_REG_NUM             79   //OV7725
#define SCCB_SIC_H()     GPIOB->BSRRL=GPIO_Pin_8
#define SCCB_SIC_L()     GPIOB->BSRRH=GPIO_Pin_8
#define SCCB_SID_H()     GPIOB->BSRRL=GPIO_Pin_9
#define SCCB_SID_L()     GPIOB->BSRRH=GPIO_Pin_9
#define SCCB_DATA_IN      SCCB_SID_IN()
#define SCCB_DATA_OUT     SCCB_SID_OUT()
#define SCCB_SID_STATE	 GPIOB->IDR&0x0200

#define MAX_IMAGE_WIDTH         (752)
#define MAX_IMAGE_HEIGHT        (480)

#define FULL_IMAGE_SIZE         (38400) // FULL_IMAGE_ROW_SIZE*FULL_IMAGE_COLUMN_SIZE
#define FULL_IMAGE_ROW_SIZE     (320)
#define FULL_IMAGE_COLUMN_SIZE  (120)

extern u16 ImageBuf[FULL_IMAGE_SIZE];

void OV7725_Init( void );
void Cam_Init(void);
unsigned char  OV_Init(void);
void Cam_Start(void);
void OV_HW(unsigned int  hstart,unsigned int vstart,unsigned int hstop,unsigned int vstop);
void SCCB_Init(void);
void SCCB_SID_OUT(void);
void SCCB_SID_IN(void);
void SCCB_Start(void);
void SCCB_Stop(void);
void noAck(void);
unsigned char  SCCB_Write(unsigned char  m_data);
unsigned char  SCCB_Read(void);
unsigned char  OV_WriteReg(unsigned char  regID, unsigned char  regDat);
unsigned char  OV_ReadReg(unsigned char  regID, unsigned char  *regDat);
void OV_Reset(void);
unsigned short  OV_ReadID(void);

static const unsigned char  OV_reg[OV_REG_NUM][2]=
{	
   
 
      
  ////////////////////////////////////////////////////////////
      /*OV7725 QVGA RGB565把计 
       guanfu_wang  
       http://mcudiy.taobao.com/
      */
  ///////////////////////////////////////////////////////////      
  {0x32,0x00},
  {0x2a,0x00},
  {0x11,0x03},
  {0x12,0x46},//QVGA RGB565

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
  {0x15,0x00}, //璶把计 
  {0x9b,0x00},//set luma 
  {0x9c,0x20},//set contrast //癸ゑ
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
  {0x0c,0x60},///璶
  {0x09,0x03},
  
  {0x29,0x50},
  {0x2C,0x78},
  //{0x0c,0x00},
  {0x00,0x00},
  {0x00,0x00},
  {0x00,0x60},   

};

#endif 

