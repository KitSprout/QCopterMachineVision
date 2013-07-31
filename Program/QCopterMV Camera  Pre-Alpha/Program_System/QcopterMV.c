/*=====================================================================================================*/
/*=====================================================================================================*/
#include <stdlib.h>
#include "stm32f4_system.h"
#include "stm32f4_usart.h"
#include "stm32f4_i2c.h"
#include "stm32f4_sdio.h"
#include "system_camera.h"
#include "module_rs232.h"
#include "module_ssd1963.h"
#include "algorithm_bitmap.h"
#include "DI_Sensor.h" // #include "module_mt9v022.h"
#include "ff.h"
#include "diskio.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define KEY   PBI(2)
#define LED_R PCO(15)
#define LED_G PCO(14)
#define LED_B PCO(13)
/*=====================================================================================================*/
/*=====================================================================================================*/
FATFS fatfs;
FIL file;
BmpHeader BMP_HEADER;
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
void SDCard_Init( USART_TypeDef* USARTx )
{
  u8 TrData[4][16] = {0};

	// SD Card Init Info
  RS232_Print(USARTx, (u8*)" \r\n");
  RS232_Print(USARTx, (u8*)"----------------------\r\n");
  RS232_Print(USARTx, (u8*)"----------------------\r\n");
  RS232_Print(USARTx, (u8*)" SDIO SD Fatfs demo\r\n");
  RS232_Print(USARTx, (u8*)"----------------------\r\n");
  RS232_Print(USARTx, (u8*)"----------------------\r\n\r\n");
  RS232_Print(USARTx, (u8*)" SD Init ... ");
  while(SD_Init() != SD_OK) {
    RS232_Print(USARTx, (u8*)"Failed!!\r\n");
    while(1) {
      LED_R = ~LED_R;
      Delay_100ms(2);
    }
  }
  RS232_Print(USARTx, (u8*)"OK!!\r\n\r\n");

  RS232_Print(USARTx, (u8*)"-----SD Init Info-----\r\n");
  RS232_Print(USARTx, (u8*)" Capacity : ");
  NumToChar(Type_D, 5, TrData[0], SDCardInfo.CardCapacity>>20);
  RS232_Print(USARTx, TrData[0]);
  RS232_Print(USARTx, (u8*)" MB\r\n");

  RS232_Print(USARTx, (u8*)" CardBlockSize : ");
  NumToChar(Type_D, 5, TrData[1], SDCardInfo.CardBlockSize);
  RS232_Print(USARTx, TrData[1]);
  RS232_Print(USARTx, (u8*)"\r\n");

  RS232_Print(USARTx, (u8*)" CardType : ");
  NumToChar(Type_D, 5, TrData[2], SDCardInfo.CardType);
  RS232_Print(USARTx, TrData[2]);
  RS232_Print(USARTx, (u8*)"\r\n");

  RS232_Print(USARTx, (u8*)" RCA : ");
  NumToChar(Type_D, 5, TrData[3], SDCardInfo.RCA);
  RS232_Print(USARTx, TrData[3]);
  RS232_Print(USARTx, (u8*)"\r\n");
  RS232_Print(USARTx, (u8*)"----------------------\r\n");
  RS232_Print(USARTx, (u8*)"\r\n");
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void SDCard_ReadDirectory( USART_TypeDef* USARTx )
{
  FILINFO finfo;
  DIR dirs;
  FRESULT res;

	// Read Directory File
  RS232_Print(USARTx, (u8*)"----------------------\r\n");
  RS232_Print(USARTx, (u8*)" SD_Card Read Directory File\r\n");
  RS232_Print(USARTx, (u8*)"----------------------\r\n\r\n");

  res = f_opendir(&dirs, "0:/");
  res = f_readdir(&dirs, &finfo);
  while(res!= FR_OK) {
		RS232_Print(USARTx, (u8*)" Fatfs failed!!\r\n");
		while(1) {
      LED_R = ~LED_R;
      Delay_100ms(2);
    }
	}
  RS232_Print(USARTx, (u8*)" File name : \r\n");
 
  while(finfo.fname[0]) {
    f_readdir(&dirs, &finfo);
    if(!finfo.fname[0])
      break;
    RS232_Print(USARTx, (u8*)" ... ");
    RS232_Print(USARTx, (u8*)finfo.fname);
    RS232_Print(USARTx, (u8*)"\r\n");
  }
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void Fatfs_WriteBMP( void )
{
  FRESULT res;

  u32 i = 0;
  u8 BitmapHeader[54] = {0};

  BMP_HEADER.Width           = FULL_IMAGE_ROW_SIZE;
  BMP_HEADER.Height          = FULL_IMAGE_COLUMN_SIZE;
  BMP_HEADER.Identifier      = 0x424D;
  BMP_HEADER.BitsPerPixel    = 16;
  BMP_HEADER.HeaderSize      = 0x28;
  BMP_HEADER.DataOffset      = 54;
  BMP_HEADER.FileSize        = 54 + BMP_HEADER.Width*BMP_HEADER.Height*(BMP_HEADER.BitsPerPixel>>3);
  BMP_HEADER.Reserved        = 0;
  BMP_HEADER.Planes          = 1;
  BMP_HEADER.Compression     = 0;
  BMP_HEADER.DataSize        = BMP_HEADER.Width*BMP_HEADER.Height*(BMP_HEADER.BitsPerPixel>>3);
  BMP_HEADER.H_Resolution    = 0;
  BMP_HEADER.V_Resolution    = 0;
  BMP_HEADER.UsedColors      = 0;
  BMP_HEADER.ImportantColors = 0;
  BMP_WriteInfo(&BMP_HEADER, BitmapHeader);

  f_open(&file, "ImageT.bmp", FA_CREATE_ALWAYS | FA_WRITE);
  res = f_write(&file, BitmapHeader, 54, &i);

  while(res!=FR_OK) {
    LED_R = ~LED_R;
    Delay_100ms(2);
	}

  res = f_write(&file, ImageBuf, BMP_HEADER.DataSize, &i);
  TFT_DrawPicture(10, 140, FULL_IMAGE_ROW_SIZE, FULL_IMAGE_COLUMN_SIZE, ImageBuf);

  f_close(&file);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void System_Init( void )
{
	SystemInit();
	GPIO_Config();
	RS232_Config();
  SSD1963_Config();
  Delay_1ms(2);
  SSD1963_Init();
  Delay_1ms(2);

  TFT_Clear(WHITE);

  OV7725_Init();

  SDCard_Init(USART2);
}
/*=====================================================================================================*/
/*=====================================================================================================*/
int main( void )
{
  System_Init();

  // Wait
  while(KEY != 1){
    LED_G = ~LED_G;
    Delay_100ms(1);
  }

  f_mount(0, &fatfs);

  // Read Directory
  SDCard_ReadDirectory(USART2);

  // Wait
  while(KEY != 1){
    LED_G = ~LED_G;
    Delay_100ms(1);
  }

  Camera_Enable();

  Delay_100ms(1);
  Fatfs_WriteBMP();

  while(1) {
//    if(KEY==1) {
//      Camera_Enable();
//      Fatfs_WriteBMP();
//    }
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
