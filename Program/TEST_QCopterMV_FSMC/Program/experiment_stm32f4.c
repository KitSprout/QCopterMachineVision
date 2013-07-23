/*=====================================================================================================*/
/*=====================================================================================================*/
#include "stm32f4_system.h"
#include "module_ssd1963.h"
#include "algorithm_mathUnit.h"
#include "arm_math.h"
/*=====================================================================================================*/
/*=====================================================================================================*/
#define KEY   PBI(2)
#define LED_R PCO(15)
#define LED_G PCO(14)
#define LED_B PCO(13)
/*=====================================================================================================*/
/*=====================================================================================================*/
void GPIO_Config( void );
void TFT_3D_DEMO( void );
/*=====================================================================================================*/
/*=====================================================================================================*/
void Windows_DrawMenu( void )
{
	TFT_Clear(BLACK);

	TFT_DrawLineX(0, 248, 479, WHITE);
	TFT_DrawLineX(0, 247, 479, WHITE);
}
int main( void )
{
	SystemInit();
	GPIO_Config();
	SSD1963_Config();

	Delay_10ms(10);

	SSD1963_Init();

	Delay_10ms(10);

  while(1) {
    TFT_3D_DEMO();
    while(KEY) {
			LED_R = 0;
      LED_G = 1;
      LED_B = 1;
      Delay_100ms(1);
      LED_R = 1;
      LED_G = 0;
      LED_B = 1;
      Delay_100ms(1);
      LED_R = 1;
      LED_G = 1;
      LED_B = 0;
      Delay_100ms(1);
    }
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
void Engine3D_RotateX( s16 Angle, s16 *Coordinate )
{
	s16 Temp[2] = {0};
	float TempSin = 0.0f;
	float TempCos = 0.0f;

	TempSin = sinf(toRad(Angle));
	TempCos = cosf(toRad(Angle));

	Temp[0] = (s16)((float)Coordinate[1]*TempCos - (float)Coordinate[2]*TempSin+0.5f);
	Temp[1] = (s16)((float)Coordinate[2]*TempCos + (float)Coordinate[1]*TempSin+0.5f);

	Coordinate[1] = Temp[0];
	Coordinate[2] = Temp[1];
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void Engine3D_RotateY( s16 Angle, s16 *Coordinate )
{
	s16 Temp[2] = {0};
	float TempSin = 0.0f;
	float TempCos = 0.0f;

	TempSin = sinf(toRad(Angle));
	TempCos = cosf(toRad(Angle));

	Temp[0] = (s16)((float)Coordinate[0]*TempCos + (float)Coordinate[2]*TempSin + 0.5f);
	Temp[1] = (s16)((float)Coordinate[2]*TempCos - (float)Coordinate[0]*TempSin + 0.5f);

	Coordinate[0] = Temp[0];
	Coordinate[2] = Temp[1];
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void Engine3D_RotateZ( s16 Angle, s16 *Coordinate )
{
	s16 Temp[2] = {0};
	float TempSin = 0.0f;
	float TempCos = 0.0f;

	TempSin = sinf(toRad(Angle));
	TempCos = cosf(toRad(Angle));

	Temp[0] = (s16)((float)Coordinate[0]*TempCos - (float)Coordinate[1]*TempSin + 0.5f);
	Temp[1] = (s16)((float)Coordinate[1]*TempCos + (float)Coordinate[0]*TempSin + 0.5f);

	Coordinate[0] = Temp[0];
	Coordinate[1] = Temp[1];
}
/*=====================================================================================================*/
/*=====================================================================================================*/
void TFT_3D_DEMO( void )
{
	/* 3D ด๚ธี */
	#define Sp3D_X	240
	#define Sp3D_Y	136
	#define Sp3D_R	60

	u8 i = 0;
	static s16 Sita = 0;
	static s16 Cube[8][3] = {0};

	TFT_DrawLine(Sp3D_X+Cube[0][0], Sp3D_Y+Cube[0][1], Sp3D_X+Cube[1][0], Sp3D_Y+Cube[1][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[0][0], Sp3D_Y+Cube[0][1], Sp3D_X+Cube[2][0], Sp3D_Y+Cube[2][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[0][0], Sp3D_Y+Cube[0][1], Sp3D_X+Cube[3][0], Sp3D_Y+Cube[3][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[7][0], Sp3D_Y+Cube[7][1], Sp3D_X+Cube[4][0], Sp3D_Y+Cube[4][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[7][0], Sp3D_Y+Cube[7][1], Sp3D_X+Cube[5][0], Sp3D_Y+Cube[5][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[7][0], Sp3D_Y+Cube[7][1], Sp3D_X+Cube[6][0], Sp3D_Y+Cube[6][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[1][0], Sp3D_Y+Cube[1][1], Sp3D_X+Cube[5][0], Sp3D_Y+Cube[5][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[1][0], Sp3D_Y+Cube[1][1], Sp3D_X+Cube[6][0], Sp3D_Y+Cube[6][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[2][0], Sp3D_Y+Cube[2][1], Sp3D_X+Cube[4][0], Sp3D_Y+Cube[4][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[2][0], Sp3D_Y+Cube[2][1], Sp3D_X+Cube[6][0], Sp3D_Y+Cube[6][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[3][0], Sp3D_Y+Cube[3][1], Sp3D_X+Cube[5][0], Sp3D_Y+Cube[5][1], BLACK);
	TFT_DrawLine(Sp3D_X+Cube[3][0], Sp3D_Y+Cube[3][1], Sp3D_X+Cube[4][0], Sp3D_Y+Cube[4][1], BLACK);
	Cube[0][0] = -Sp3D_R;
	Cube[0][1] = -Sp3D_R;
	Cube[0][2] = -Sp3D_R;
	Cube[1][0] = Sp3D_R;
	Cube[1][1] = -Sp3D_R;
	Cube[1][2] = -Sp3D_R;
	Cube[2][0] = -Sp3D_R;
	Cube[2][1] = Sp3D_R;
	Cube[2][2] = -Sp3D_R;
	Cube[3][0] = -Sp3D_R;
	Cube[3][1] = -Sp3D_R;
	Cube[3][2] = Sp3D_R;
	Cube[4][0] = -Sp3D_R;
	Cube[4][1] = Sp3D_R;
	Cube[4][2] = Sp3D_R;
	Cube[5][0] = Sp3D_R;
	Cube[5][1] = -Sp3D_R;
	Cube[5][2] = Sp3D_R;
	Cube[6][0] = Sp3D_R;
	Cube[6][1] = Sp3D_R;
	Cube[6][2] = -Sp3D_R;
	Cube[7][0] = Sp3D_R;
	Cube[7][1] = Sp3D_R;
	Cube[7][2] = Sp3D_R;
	for(i=0; i<8; i++) {
		Engine3D_RotateY(Sita/2.0f, Cube[i]);
		Engine3D_RotateX(Sita, Cube[i]);
	}
	TFT_DrawLine(Sp3D_X+Cube[0][0], Sp3D_Y+Cube[0][1], Sp3D_X+Cube[1][0], Sp3D_Y+Cube[1][1], WHITE);
	TFT_DrawLine(Sp3D_X+Cube[0][0], Sp3D_Y+Cube[0][1], Sp3D_X+Cube[2][0], Sp3D_Y+Cube[2][1], WHITE);
	TFT_DrawLine(Sp3D_X+Cube[0][0], Sp3D_Y+Cube[0][1], Sp3D_X+Cube[3][0], Sp3D_Y+Cube[3][1], WHITE);
	TFT_DrawLine(Sp3D_X+Cube[7][0], Sp3D_Y+Cube[7][1], Sp3D_X+Cube[4][0], Sp3D_Y+Cube[4][1], YELLOW);
	TFT_DrawLine(Sp3D_X+Cube[7][0], Sp3D_Y+Cube[7][1], Sp3D_X+Cube[5][0], Sp3D_Y+Cube[5][1], YELLOW);
	TFT_DrawLine(Sp3D_X+Cube[7][0], Sp3D_Y+Cube[7][1], Sp3D_X+Cube[6][0], Sp3D_Y+Cube[6][1], YELLOW);
	TFT_DrawLine(Sp3D_X+Cube[1][0], Sp3D_Y+Cube[1][1], Sp3D_X+Cube[5][0], Sp3D_Y+Cube[5][1], RED);
	TFT_DrawLine(Sp3D_X+Cube[1][0], Sp3D_Y+Cube[1][1], Sp3D_X+Cube[6][0], Sp3D_Y+Cube[6][1], RED);
	TFT_DrawLine(Sp3D_X+Cube[2][0], Sp3D_Y+Cube[2][1], Sp3D_X+Cube[4][0], Sp3D_Y+Cube[4][1], BLUE);
	TFT_DrawLine(Sp3D_X+Cube[2][0], Sp3D_Y+Cube[2][1], Sp3D_X+Cube[6][0], Sp3D_Y+Cube[6][1], BLUE);
	TFT_DrawLine(Sp3D_X+Cube[3][0], Sp3D_Y+Cube[3][1], Sp3D_X+Cube[5][0], Sp3D_Y+Cube[5][1], GREEN);
	TFT_DrawLine(Sp3D_X+Cube[3][0], Sp3D_Y+Cube[3][1], Sp3D_X+Cube[4][0], Sp3D_Y+Cube[4][1], GREEN);

	Sita++;
	if(Sita == 360)
		Sita = 0;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
