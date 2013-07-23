/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "stm32f4_i2c.h"
#include "module_mt9v022.h"
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : SCCB_Read
**功能 : 
**輸入 : 
**輸出 : 
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
**功能 : 
**輸入 : 
**輸出 : 
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
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
void MT9V022_Config( void )
{

}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MT9V022_Init
**功能 : 
**輸入 : 
**輸出 : 
**使用 : 
**=====================================================================================================*/
/*=====================================================================================================*/
#define MT9V022_RegSize 161
u32 MT9V022_Init( void )
{
  /* Monochrome */
  u16 i = 0;
  u16 ReadID[2] = {0};
  uc16 MT9V022_Reg[MT9V022_RegSize][2]= {
/*
    // [Reset]
    { 0x0C, 0x0001 },   // RESET_REG
    { 0x0C, 0x0000 },   // RESET_REG
*/
    { 0x15, 0x7F32 },   // 
    { 0x20, 0x01D1 },   // 
    { 0x70, 0x0004 },   // ROW_NOISE_CONTROL
    { 0x73, 0x02F7 },   // DARK_COL_START
    { 0xC2, 0x0040 },   // 

    { 0x1C, 0x0003 },   // DATA_COMPRESSION
    { 0x31, 0x001F },   // V1_CONTROL
    { 0x32, 0x001A },   // V2_CONTROL
    { 0x33, 0x0012 },   // V3_CONTROL
    { 0xAF, 0x0000 },   // AUTO_BLOCK_CONTROL
    { 0x2B, 0x0003 },   // 
    { 0x10, 0x0040 },   // 

    // Default software settings
    // STATE=Filter, 3
    // STATE=Relative Red Gain, 1000
    // STATE=Relative Blue Gain, 1000
    // STATE=Monochrome, 1
    // STATE=True Black Enable, 0

/*
    //[High Dynamic Settings]
    { 0x0F, 0x0051 },   // PIXEL_OPERATION_MODE
    { 0x10, 0x001C },   // 
    { 0x15, 0x2832 },   // 
    { 0x1C, 0x0003 },   // DATA_COMPRESSION
    { 0x2B, 0x0000 },   // 
    { 0x48, 0x0000 },   // TARGET_CALIB_VALUE
    { 0x70, 0x0004 },   // ROW_NOISE_CONTROL
    { 0x73, 0x02F7 },   // DARK_COL_START
    { 0xAB, 0x0000 },   // GAIN_LPF_H
    { 0xBF, 0x0014 },   // INTERLACE_VBLANK
*/

    // [Linear Settings]
    { 0x0F, 0x0011 },   // PIXEL_OPERATION_MODE
    { 0x15, 0x7F32 },   // 
    { 0x1C, 0x0002 },   // DATA_COMPRESSION

    // [Reset Registers]
    { 0x01,     1 },   // COL_WINDOW_START_REG
    { 0x02,     4 },   // ROW_WINDOW_START_REG
    { 0x03,   480 },   // ROW_WINDOW_SIZE_REG
    { 0x04,   752 },   // COL_WINDOW_SIZE_REG
    { 0x05,    94 },   // HORZ_BLANK_REG 
    { 0x06,    45 },   // VERT_BLANK_REG
    { 0x07,   904 },   // CONTROL_MODE_REG
    { 0x08,   443 },   // SHUTTER_WIDTH_REG_1
    { 0x09,   473 },   // SHUTTER_WIDTH_REG_2
    { 0x0A,   356 },   // SHUTTER_WIDTH_CONTROL
    { 0x0B,   480 },   // INTEG_TIME_REG
    { 0x0C,     0 },   // RESET_REG
    { 0x0D,   768 },   // READ_MODE_REG
    { 0x0E,     0 },   // MONITOR_MODE_CONTROL
    { 0x0F,    17 },   // PIXEL_OPERATION_MODE
    { 0x10,    45 },   // 
    { 0x11, 32834 },   // 
    { 0x12,    34 },   // 
    { 0x13,  3634 },   // 
    { 0x14,  3586 },   // 
    { 0x15,  3634 },   // 
    { 0x16, 10242 },   // 
    { 0x17, 15928 },   // 
    { 0x18, 15928 },   // 
    { 0x19, 10242 },   // 
    { 0x1A,  1064 },   // 
    { 0x1B,     0 },   // LED_OUT_CONTROL
    { 0x1C,     2 },   // DATA_COMPRESSION
    { 0x1D,     0 },   // 
    { 0x1E,     0 },   // 
    { 0x1F,     0 },   // 
    { 0x20,    17 },   // 
    { 0x21,    32 },   // 
    { 0x22,    32 },   // 
    { 0x23,    16 },   // 
    { 0x24,    16 },   // 
    { 0x25,    32 },   // 
    { 0x26,    16 },   // 
    { 0x27,    16 },   // 
    { 0x28,    16 },   // 
    { 0x29,    16 },   // 
    { 0x2A,    32 },   // 
    { 0x2B,     4 },   // 
    { 0x2C,     4 },   // 
    { 0x2D,     4 },   // 
    { 0x2E,     7 },   // 
    { 0x2F,     4 },   // 
    { 0x30,     3 },   // 
    { 0x31,    29 },   // V1_CONTROL
    { 0x32,    24 },   // V2_CONTROL
    { 0x33,    21 },   // V3_CONTROL
    { 0x34,     4 },   // V4_CONTROL
    { 0x35,    16 },   // GLOBAL_GAIN_REG
    { 0x36,    64 },   // MAXIMUM_GAIN_REG
    { 0x37,     0 },   // 
    { 0x38,     0 },   // 

    { 0x46,  8989 },   // DARK_AVG_THRESHOLDS
    { 0x47, 32896 },   // CALIB_CONTROL_REG

    { 0x4C,     2 },   // STEP_SIZE_AVG_MODE

    { 0x60,     0 },   // 
    { 0x61,     0 },   // 
    { 0x62,     0 },   // 
    { 0x63,     0 },   // 
    { 0x64,     0 },   // 
    { 0x65,     0 },   // 
    { 0x66,     0 },   // 
    { 0x67,     0 },   // 
    { 0x6C,     0 },   // 

    { 0x70,    52 },   // ROW_NOISE_CONTROL
    { 0x71,     0 },   // 
    { 0x72,    42 },   // NOISE_CONSTANT
    { 0x73,   759 },   // DARK_COL_START
    { 0x74,     0 },   // PIXCLK_CONTROL

    { 0x7F,     0 },   // TEST_DATA
    { 0x80,   244 },   // TILE_X0_Y0
    { 0x81,   244 },   // TILE_X1_Y0
    { 0x82,   244 },   // TILE_X2_Y0
    { 0x83,   244 },   // TILE_X3_Y0
    { 0x84,   244 },   // TILE_X4_Y0
    { 0x85,   244 },   // TILE_X0_Y1
    { 0x86,   244 },   // TILE_X1_Y1
    { 0x87,   244 },   // TILE_X2_Y1
    { 0x88,   244 },   // TILE_X3_Y1
    { 0x89,   244 },   // TILE_X4_Y1
    { 0x8A,   244 },   // TILE_X0_Y2
    { 0x8B,   244 },   // TILE_X1_Y2
    { 0x8C,   244 },   // TILE_X2_Y2
    { 0x8D,   244 },   // TILE_X3_Y2
    { 0x8E,   244 },   // TILE_X4_Y2
    { 0x8F,   244 },   // TILE_X0_Y3
    { 0x90,   244 },   // TILE_X1_Y3
    { 0x91,   244 },   // TILE_X2_Y3
    { 0x92,   244 },   // TILE_X3_Y3
    { 0x93,   244 },   // TILE_X4_Y3
    { 0x94,   244 },   // TILE_X0_Y4
    { 0x95,   244 },   // TILE_X1_Y4
    { 0x96,   244 },   // TILE_X2_Y4
    { 0x97,   244 },   // TILE_X3_Y4
    { 0x98,   244 },   // TILE_X4_Y4
    { 0x99,     0 },   // X0_SLASH5
    { 0x9A,   150 },   // X1_SLASH5
    { 0x9B,   300 },   // X2_SLASH5
    { 0x9C,   450 },   // X3_SLASH5
    { 0x9D,   600 },   // X4_SLASH5
    { 0x9E,   752 },   // X5_SLASH5
    { 0x9F,     0 },   // Y0_SLASH5
    { 0xA0,    96 },   // Y1_SLASH5
    { 0xA1,   192 },   // Y2_SLASH5
    { 0xA2,   288 },   // Y3_SLASH5
    { 0xA3,   384 },   // Y4_SLASH5
    { 0xA4,   480 },   // Y5_SLASH5
    { 0xA5,    58 },   // DESIRED_BIN
    { 0xA6,     2 },   // EXP_SKIP_FRM
    { 0xA7,     0 },   // 
    { 0xA8,     0 },   // EXP_LPF
    { 0xA9,     2 },   // GAIN_SKIP_FRM_H
    { 0xAA,     0 },   // 
    { 0xAB,     2 },   // GAIN_LPF_H

    { 0xAF,     3 },   // AUTO_BLOCK_CONTROL
    { 0xB0, 44000 },   // PIXEL_COUNT
    { 0xB1,     2 },   // LVDS_MASTER_CONTROL
    { 0xB2,    16 },   // SHFT_CLK_CONTROL
    { 0xB3,    16 },   // LVDS_DATA_CONTROL
    { 0xB4,     0 },   // STREAM_LATENCY_SELECT
    { 0xB5,     0 },   // LVDS_INTERNAL_SYNC
    { 0xB6,     0 },   // USE_10BIT_PIXELS
    { 0xB7,     0 },   // STEREO_ERROR_CONTROL

    { 0xBD,   480 },   // MAX_EXPOSURE
    { 0xBE,    20 },   // 
    { 0xBF,    22 },   // INTERLACE_VBLANK
    { 0xC0,    10 },   // IMAGE_CAPTURE_NUM

    { 0xC2,  6208 },   // 
    { 0xC3,     0 },   // NTSC_FV_CONTROL
    { 0xC4, 17430 },   // NTSC_HBLANK
    { 0xC5, 17441 },   // NTSC_VBLANK

    { 0xF1,     0 },   // BYTEWISE_ADDR_REG
    { 0xFE, 48879 },   // REGISTER_LOCK_REG

/*
    // [NTSC Mode ON]
    BITFIELD=0x07, 0x3,  2  //Turn on two field interlace mode
    REG=0x01, 0x19          //Set Window to 752x480
    REG=0x02, 0x04
    REG=0x03, 0x01E0
    REG=0x04, 0x02BE
    REG=0x06, 0x2D          //Total vertical blank
    REG=0xBF, 0x17          //Vertical blank between even and odd fields
    REG=0x05, 0x91          //Set Horizontal blanking
    REG=0x74, 0x08          //PixClk, FV/LF
    REG=0x1C, 0x03          //ADC Resolution

    // [NTSC Mode OFF]
    BITFIELD=0x07, 0x3,  0  //Restore registers to their defaults
    REG=0x01, 0x01
    REG=0x04, 0x02F0
    REG=0x06, 0x04
    REG=0xBF, 0x14
    REG=0x05, 0xA6
    REG=0x74, 0x00
    REG=0x1C, 0x02
*/
    // [CRT Mode ON]
    { 0x06, 0x001F },
    { 0x74, 0x0008 },

/*
    // [CRT Mode OFF]
    { 0x06, 0x0004 },
    { 0x74, 0x0000 },
*/
  };

  MT9V022_Reset();

  for(i=0; i<MT9V022_RegSize; i++)
    SCCB_Write(MT9V022_I2C_ADDR, MT9V022_Reg[i][0], MT9V022_Reg[i][1]);

  SCCB_Read(MT9V022_I2C_ADDR, 0x00, ReadID);
  SCCB_Read(MT9V022_I2C_ADDR, 0xFF, ReadID+1);

  SCCB_Write(MT9V022_I2C_ADDR, 0x0D, 0x0310);

  return (ReadID[0]<<8 | ReadID[1]);
}
/*=====================================================================================================*/
/*=====================================================================================================*
**函數 : MT9V022_Reset
**功能 : 
**輸入 : 
**輸出 : 
**使用 : MT9V022_Reset();
**=====================================================================================================*/
/*=====================================================================================================*/
void MT9V022_Reset( void )
{
  SCCB_Write(MT9V022_I2C_ADDR, 0x0C, 0x01);
  Delay_1ms(10);
  SCCB_Write(MT9V022_I2C_ADDR, 0x0C, 0x00);
  Delay_1ms(20);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
