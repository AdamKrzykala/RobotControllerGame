#include "interface.h"
#include "globalstruct.h"

int switchingINTRO_flag = 0;
int switchingMENU_flag = 1;
int switchingSTART_flag = 1;
int switchingODCZYTY_flag = 1;
int switchingONAS_flag = 1;

int page = 0;

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
		switchingMENU_flag = 0;
		screenRefresh();

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"LABIRINTH", CENTER_MODE);
		DrawButton("START",60);
		DrawButton("ODCZYTY",120);
		DrawButton("O NAS",180);
	}
}

void Display_Start(void) {
	if(switchingSTART_flag == 1) {
		switchingSTART_flag = 0;
		screenRefresh();

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"SCENA GRY", CENTER_MODE);
		DrawButton("Powrot",250);

		static uint16_t xpos = 100;
		static uint16_t ypos = 100;
		xpos += x;
		ypos += y;

		BSP_LCD_SetTextColor(LCD_COLOR_RED);
		BSP_LCD_FillCircle(ypos, xpos, 10);
		BSP_LCD_SetBackColor(LCD_COLOR_RED);
	}
}

void Display_Odczyty(void) {
	if(switchingODCZYTY_flag == 1) {
		switchingODCZYTY_flag = 0;
		screenRefresh();

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"ODCZYTY MPU", CENTER_MODE);
		DrawButton("Powrot",250);

		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 60, (uint8_t*)"X AXIS: 0.0000", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 100, (uint8_t*)"Y AXIS: 0.0000", CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 140, (uint8_t*)"Z AXIS: 0.0000", CENTER_MODE);

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
