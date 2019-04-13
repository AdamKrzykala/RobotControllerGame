#include "interface.h"
#include "globalstruct.h"

int switchingMENU_flag = 1;
int switchingODCZYTY_flag = 1;
int page = 0;
char buffer[10];

void initMenu(TS_StateTypeDef* str) {
	localstr = str;
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

void Display(globalClass* globalClassHandler) {
	if (page == 0) Display_Menu(globalClassHandler);
	if (page == 1) Display_Odczyty(globalClassHandler);
}

void Service(globalClass* globalClassHandler) {
	if (page == 0) menuService();
	if (page == 1) odczytyService();
}

void Display_Menu(globalClass* globalClassHandler) {
	if(switchingMENU_flag == 1) {
		switchingMENU_flag = 0;
		BSP_LCD_SelectLayer(1);
		BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Font24);

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"SNAKE GAME", CENTER_MODE);
		DrawButton("Odczyty",50);
	}
}

void Display_Odczyty(globalClass* globalClassHandler) {
	if(switchingODCZYTY_flag == 1) {
		switchingODCZYTY_flag = 0;
		BSP_LCD_SelectLayer(1);
		BSP_LCD_SetFont(&LCD_DEFAULT_FONT);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_Clear(LCD_COLOR_WHITE);
		BSP_LCD_SetFont(&Font24);

		BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		BSP_LCD_DisplayStringAt(0, 20, (uint8_t*)"ODCZYTY MPU", CENTER_MODE);
		DrawButton("Powrot",250);

		BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
		BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
		//itoa (i,buffer,10);
		BSP_LCD_DisplayStringAt(0, 60, &globalClassHandler->gyroVarX, CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 100, &globalClassHandler->gyroVarY, CENTER_MODE);
		BSP_LCD_DisplayStringAt(0, 140, &globalClassHandler->gyroVarZ, CENTER_MODE);

	}
}


void menuService(void) {
	if (localstr->TouchDetected) {
		if (localstr->Y >= 50 && localstr->Y <= 94)
				{
			//DrawButton("Nacisnieto", 120);
			page = 1;
			switchingODCZYTY_flag = 1;
			HAL_Delay(50);
		}
	}
}

void odczytyService(void) {
	if (localstr->TouchDetected) {
		if (localstr->Y >= 250 && localstr->Y <= 294)
				{
			page = 0;
			switchingMENU_flag = 1;
			HAL_Delay(50);
		}
	}
}
