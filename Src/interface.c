#include "interface.h"
#include "globalstruct.h"

int switchingINTRO_flag = 0;
int switchingMENU_flag = 1;
int switchingSTART_flag = 1;
int switchingODCZYTY_flag = 1;
int switchingONAS_flag = 1;

int page = 0;

/*
 * Variables expressing the angle of rotation in degrees.
 */
extern int x;
extern int y;
extern int z;

void initMenu(TS_StateTypeDef* str, globalClass* globalClassHandler) {
	localstr = str;
	localClassHandler = globalClassHandler;
}

void screenRefresh(void) {
	BSP_LCD_SelectLayer(1);
	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font24);
}

void DrawButton(char* text, uint8_t line_number) {
	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_FillRect(20, line_number, BSP_LCD_GetXSize()-40, 44);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(0, line_number + 14, (uint8_t*)text,
			CENTER_MODE);
}

void Display(void) {
	if (page == 0) Display_Intro();
	if (page == 1) Display_Menu();
	if (page == 2) Display_Start();
	if (page == 3) Display_Odczyty();
	if (page == 4) Display_Onas();
}

void Service(void) {
	if (page == 1) menuService();
	if (page == 2) startService();
	if (page == 3) odczytyService();
	if (page == 4) onasService();
}

void Display_Intro(void) {
	if(switchingINTRO_flag == 0) {
		switchingINTRO_flag = 1;
		screenRefresh();
		int waitTime = 500;
		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 80, (uint8_t*)"LABIRINTH", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 110, (uint8_t*)"GAME", CENTER_MODE);
		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_FillRect(80, 150, 20, 20);
		BSP_LCD_FillRect(80, 180, 20, 20);
		BSP_LCD_FillRect(80, 210, 20, 20);

		BSP_LCD_FillRect(110, 150, 20, 20);
		BSP_LCD_FillRect(110, 180, 20, 20);
		BSP_LCD_FillRect(110, 210, 20, 20);

		BSP_LCD_FillRect(140, 150, 20, 20);
		BSP_LCD_FillRect(140, 180, 20, 20);
		BSP_LCD_FillRect(140, 210, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_DARKBLUE);
		//Loading module
		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(80, 150, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(80, 180, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(80, 210, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);

		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(110, 210, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(140, 210, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(140, 180, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);

		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(140, 150, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(110, 150, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
		HAL_Delay(waitTime);
		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillRect(110, 180, 20, 20);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
		HAL_Delay(waitTime);

		for(int i=80; i>=20; i--)
		{
			screenRefresh();
			BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
			BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
			BSP_LCD_DisplayStringAt(0, i, (uint8_t*)"LABIRINTH", CENTER_MODE);
			HAL_Delay(15);
		}
		page = 1;
	}
}

void Display_Menu(void) {
	if(switchingMENU_flag == 1) {
//		switchingMENU_flag = 0;
		screenRefresh();

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"LABIRINTH", CENTER_MODE);
		DrawButton("START",60);
		DrawButton("ODCZYTY",120);
		DrawButton("O NAS",180);
	}
}

/**
 * Ball position.
 */
static uint16_t xpos = 100;
static uint16_t ypos = 100;

/**
 * @brief Collision checking function.
 * @param x1 The x coordinate of the first point making up the line.
 * @param y1 The y coordinate of the first point making up the line.
 * @param x2 The x coordinate of the second point making up the line.
 * @param y2 The y coordinate of the second point making up the line.
 * @waring The function works only for vertical and horizontal lines.
 */
static void checkcollision(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	if (y1 == y2){
		if ((xpos >= (x1-10) && xpos <= (x2+10)) && (ypos > (y1-10) && ypos < (y2+10))) {
			if (ypos > y2) {
				ypos = y2 + 10;
			} else {
				ypos = y2 - 10;
			}
		}
	} else if (x1 == x2) {
		if ((xpos >= (x1-10) && xpos <= (x2+10)) && (ypos > (y1-10) && ypos < (y2+10))) {
			if (xpos > x2) {
				xpos = x2 + 10;
			} else {
				xpos = x2 - 10;
			}
		}
	}
}

/*
 * @brief Function for drawing the labyrinth and checking the collisions.
 */

static void labyrinthDraw() {
	BSP_LCD_DrawLine(50, 225, 200, 225);
	checkcollision(50, 225, 200, 225);

	BSP_LCD_DrawLine(200, 75, 200, 225);
	checkcollision(200, 75, 200, 225);

	BSP_LCD_DrawLine(50, 75, 200, 75);
	checkcollision(50, 75, 200, 75);

	BSP_LCD_DrawLine(50, 75, 50, 100);
	checkcollision(50, 75, 50, 100);

	BSP_LCD_DrawLine(50, 75, 50, 200);
	checkcollision(50, 75, 50, 200);

	BSP_LCD_DrawLine(50, 200, 150, 200);
	checkcollision(50, 200, 150, 200);

	BSP_LCD_DrawLine(125, 75, 125, 175);
	checkcollision(125, 75, 125, 175);

	BSP_LCD_DrawLine(75, 125, 125, 125);
	checkcollision(75, 125, 125, 125);
}

void Display_Start(void) {
	if(switchingSTART_flag == 1) {
//		switchingSTART_flag = 0;
		screenRefresh();

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"SCENA GRY", CENTER_MODE);
		DrawButton("Powrot",250);

		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillCircle(xpos, ypos, 10);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);

		labyrinthDraw();

		/*
		 * Multiplication by 0.5 for better driving.
		 */
		xpos += y * 0.5;
		ypos += x * 0.5;
	}
}

void Display_Odczyty(void) {
	if(switchingODCZYTY_flag == 1) {
//		switchingODCZYTY_flag = 0;
		screenRefresh();

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"ODCZYTY MPU", CENTER_MODE);
		DrawButton("Powrot",250);

		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);

		uint8_t xaxis[14] = "X ASIX: ";
		uint8_t yaxis[14] = "Y ASIX: ";
		uint8_t zaxis[14] = "Z ASIX: ";
		itoa(x, &xaxis[8], 10);
		itoa(y, &yaxis[8], 10);
		itoa(z, &zaxis[8], 10);
		BSP_LCD_DisplayStringAt(0, 60, xaxis, CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 100, yaxis, CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 140, zaxis, CENTER_MODE);

	}
}

void Display_Onas(void) {
	if(switchingONAS_flag == 1) {
		switchingONAS_flag = 0;
		screenRefresh();

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"Autorzy", CENTER_MODE);
		DrawButton("Powrot",250);

		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 60, (uint8_t*)"Adam Krzykala", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 80, (uint8_t*)"Szymon Rajca", CENTER_MODE);

	}
}


void menuService(void) {
	if (localstr->TouchDetected) {
		if (localstr->Y >= 60 && localstr->Y <= 104)
				{

			page = 2;
			switchingSTART_flag = 1;
			HAL_Delay(50);
		}
		if (localstr->Y >= 120 && localstr->Y <= 164)
						{

			page = 3;
			switchingODCZYTY_flag = 1;
			HAL_Delay(50);
				}
		if (localstr->Y >= 180 && localstr->Y <= 224)
						{

			page = 4;
			switchingONAS_flag = 1;
			HAL_Delay(50);
				}
	}
}

void startService(void) {
	if (localstr->TouchDetected) {
		if (localstr->Y >= 250 && localstr->Y <= 294)
				{
			page = 1;
			switchingMENU_flag = 1;
			HAL_Delay(50);
		}
	}
}

void odczytyService(void) {
	if (localstr->TouchDetected) {
		if (localstr->Y >= 250 && localstr->Y <= 294)
				{
			page = 1;
			switchingMENU_flag = 1;
			HAL_Delay(50);
		}
	}
}

void onasService(void) {
	if (localstr->TouchDetected) {
		if (localstr->Y >= 250 && localstr->Y <= 294)
				{
			page = 1;
			switchingMENU_flag = 1;
			HAL_Delay(50);
		}
	}
}
