/* #include "otm8009.h" */

#ifndef __OTM8009_H
#define __OTM8009_H

#include "stm32f4xx.h"
#include "fonts\fontlib.h"
#include "algorithms\string.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define LCD_RAM     *(__IO uint16_t *)((uint32_t)0x60020000)
#define LCD_REG     *(__IO uint16_t *)((uint32_t)0x60000000)

#ifdef H_VIEW
#define LCD_W       480
#define LCD_H       800
#else
#define LCD_W       800
#define LCD_H       480 
#endif

#define OTM8009_ID  ((uint32_t)(0x018B8009))


#define RGB_TO_GARY(C_R, C_G, C_B)  ((uint8_t)(0.299f * C_R + 0.587f * C_G + 0.114f * C_B))
#define ToRGB565(RGB888)            ((uint16_t)((RGB888&0xF80000>>8)|(RGB888&0x00FC00>>5)|(RGB888&0x0000F8>>3)))
#define ToRGB888(RGB565)            ((uint16_t)((RGB565&0xF800<<8)|(RGB565&0x07E0<<5)|(RGB565&0x001F<<3)))

#define RGB565_R(RGB565)            ((uint8_t)((RGB565 >> 11) & 0x1F))
#define RGB565_G(RGB565)            ((uint8_t)((RGB565 >>  4) & 0x3F))
#define RGB565_B(RGB565)            ((uint8_t)((RGB565      ) & 0x1F))

// Input: R G B, Output RGB565
#define RGB(C_R, C_G, C_B)          ((uint32_t)(((C_R<<8)&0xF800)|((C_G<<3)&0x07E0)|((C_B>>3)&0x001F)))

#define LINE(__FONT, __INDEX)       (__FONT.height * __INDEX)
#define CENTER(__FONT, __STR)       ((LCD_W - __FONT.width * lenOfStr(__STR)) >> 1)

#define RED         ((uint16_t)0xF800)  /* 紅色 */
#define GREEN       ((uint16_t)0x07E0)  /* 綠色 */
#define BLUE        ((uint16_t)0x001F)  /* 藍色 */
#define MAGENTA     ((uint16_t)0xF81F)  /* 紅紫色，洋紅色 */
#define GRED        ((uint16_t)0xFFE0)
#define GBLUE       ((uint16_t)0x07FF)
#define BRED        ((uint16_t)0XF81F)
#define BROWN       ((uint16_t)0xBC40)  /* 棕色 */
#define BRRED       ((uint16_t)0xFC07)  /* 棕紅色 */
#define CYAN        ((uint16_t)0x7FFF)  /* 藍綠色，青色 */
#define BLACK       ((uint16_t)0x0000)  /* 黑色 */
#define GRAY        ((uint16_t)0X8430)  /* 灰色 */
#define WHITE       ((uint16_t)0xFFFF)  /* 白色 */
#define YELLOW      ((uint16_t)0xFFE0)  /* 黃色 */
#define DARKBLUE    ((uint16_t)0x01CF)  /* 深藍色 */
#define LIGHTBLUE   ((uint16_t)0x7D7C)  /* 淺藍色 */
#define GRAYBLUE    ((uint16_t)0x5458)  /* 灰藍色 */
#define LIGHTGREEN  ((uint16_t)0X841F)  /* 淺綠色 */
#define LGRAY       ((uint16_t)0XC618)  /* 淺灰色 */
#define LGRAYBLUE   ((uint16_t)0XA651)  /* 淺灰藍色 */
#define LBBLUE      ((uint16_t)0X2B12)  /* 淺棕藍色 */
/*=====================================================================================================*/
/*=====================================================================================================*/
void   OTM8009_Config( void );
int8_t OTM8009_Init( void );

void   LCD_BLigConfig( void );

void   LCD_Clear( uint16_t color );
void   LCD_SetCursor( uint16_t posX, uint16_t posY );
void   LCD_SetWindow( uint16_t posX1, uint16_t posY1, uint16_t posX2, uint16_t posY2 );
void   LCD_SetBackLight( int16_t backLight );

void   LCD_DrawPixel( uint16_t posX, uint16_t posY, uint16_t color );
void   LCD_DrawLineX( uint16_t posX, uint16_t posY, uint16_t length, uint16_t color );
void   LCD_DrawLineY( uint16_t posX, uint16_t posY, uint16_t length, uint16_t color );
//void   LCD_DrawLine( uint16_t posX1, uint16_t posY1, uint16_t posX2, uint16_t posY2, uint16_t color );
void   LCD_DrawRect( uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t color );
void   LCD_DrawRectFill( uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, uint16_t color );
void   LCD_DrawCircle( uint16_t posX, uint16_t posY, uint16_t radius, uint16_t color );
void   LCD_DrawPic( uint16_t posX, uint16_t posY, uint16_t width, uint16_t height, const uint16_t *pic );

void   LCD_PutChar( uint16_t posX, uint16_t posY, sFONT *pFont, uint8_t word, uint16_t fontColor, uint16_t backColor );
void   LCD_PutStr( uint16_t posX, uint16_t posY, sFONT *pFont, char *pString, uint16_t fontColor, uint16_t backColor );
void   LCD_PutNum( uint16_t posX, uint16_t posY, sFONT *pFont, StringType type, uint8_t lens, int32_t number, uint16_t fontColor, uint16_t backColor );

void   LCD_TestColoBar( void );
void   LCD_TestFunction( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
#endif
