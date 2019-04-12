/*
 * menu.c
 *
 *  Created on: Mar 27, 2019
 *      Author: Artur
 */
#include "menu.h"
int refreshMenuFlag = 1; //pierwszy raz musi odswiezyc (narysowac)
int refreshSterowanieFlag = 1;
int refreshNastawyFlag = 1;
int refreshTestyFlag = 1;
int refreshAutorzyFlag = 1;
void initMenu(TS_StateTypeDef* arg_struktura) {
	p_struktura = arg_struktura;
	scena = MENU;
}

void DisplayCurrentScene(void) {
	switch (scena) {
	case MENU:
		//Display_Menu();
		if (refreshMenuFlag) {
			Display_Menu();
			refreshMenuFlag = 0;
		}
		break;
	case STEROWANIE:
		if (refreshSterowanieFlag) {
			Display_Steruj();
			refreshSterowanieFlag = 0;
		}
		break;
	case NASTAWY:
		if (refreshNastawyFlag) {
			Display_Nastawy();
			refreshNastawyFlag = 0;
		}
		break;
	case TESTY:
		if (refreshTestyFlag) {
			Display_Testy();
			refreshTestyFlag = 0;
		}
		break;
	case AUTORZY:
		if (refreshAutorzyFlag) {
			Display_Autorzy();
			refreshAutorzyFlag = 0;
		}
		break;
	}
	BSP_LCD_SetBackColor(LCD_COLOR_RED);
	//BSP_LCD_FillRect(60, 40, 50,50);
	//BSP_TS_GetState(p_struktura);
	//if (p_struktura->TouchDetected) {
	//	BSP_LCD_FillRect(p_struktura->X, 20, p_struktura->Y, 20);
	//}
	//HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_SET);
	//	*led = 0;
	//} else
	//	*led = 1;
	//HAL_GPIO_WritePin(LD3_GPIO_Port, LD3_Pin, GPIO_PIN_RESET);

}
void PrepareScene(void) {
	/* Set LCD Foreground Layer  */
	BSP_LCD_SelectLayer(1);

	BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

	/* Clear the LCD */
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE);
	BSP_LCD_Clear(LCD_COLOR_WHITE);

	BSP_LCD_SetFont(&Font12);
}
void DrawBackButton(void) {
	//button wstecz
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(0, BSP_LCD_GetYSize() - 30, BSP_LCD_GetXSize(), 30);
	BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() - 20, (uint8_t*) "WSTECZ",
			CENTER_MODE);
}
void DrawTitleBar(uint8_t* title)
{
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_FillRect(0, 0, BSP_LCD_GetXSize(), 30);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
	BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(0, 10, title, CENTER_MODE);
	BSP_LCD_SetBackColor(LCD_COLOR_WHITE );
	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
}

void HandleCurrentScene(void) {
	switch (scena) {
	case MENU:
		Handle_Menu();
		break;
	case STEROWANIE:
		Handle_Steruj();
		break;
	case NASTAWY:
		Handle_Nastawy();
		break;
	case TESTY:
		Handle_Testy();
		break;
	case AUTORZY:
		Handle_Autorzy();
		break;
	}
}

void Display_Splash(void) {

}

void Display_Menu(void) {

	/* Set LCD Foreground Layer  */
	PrepareScene();
	BSP_LCD_SetTextColor(LCD_COLOR_RED);
	BSP_LCD_FillRect(0, BSP_LCD_GetYSize() / 2, BSP_LCD_GetXSize(), 2); //kreski oddzielajace pozycje w mewnu
	BSP_LCD_FillRect(BSP_LCD_GetXSize() / 2, 0, 2, BSP_LCD_GetYSize());
	DrawTitleBar("MENU");

	BSP_LCD_DisplayStringAt(10, 20 + BSP_LCD_GetXSize() / 4,
			(uint8_t*) "Steruj robotem", LEFT_MODE);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 + 20,
			20 + BSP_LCD_GetXSize() / 4, (uint8_t*) "Nastawy PID", LEFT_MODE);

	BSP_LCD_SetTextColor(LCD_COLOR_BLACK);
	BSP_LCD_DisplayStringAt(20, BSP_LCD_GetYSize() / 2 + BSP_LCD_GetXSize() / 4,
			(uint8_t*) "Testy komp.", LEFT_MODE);

	BSP_LCD_DisplayStringAt(BSP_LCD_GetXSize() / 2 + 20,
			BSP_LCD_GetYSize() / 2 + BSP_LCD_GetXSize() / 4,
			(uint8_t*) "Autorzy", LEFT_MODE);
	BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
}

void Display_Nastawy(void) {
	uint8_t desc[50];

	/* Set LCD Foreground Layer  */
	PrepareScene();
	/* Set the LCD Text Color */
	DrawTitleBar("NASTAWY");

	BSP_LCD_DisplayStringAt(0, 60, (uint8_t*) "P", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 60, (uint8_t*) "0.00", RIGHT_MODE);
	BSP_LCD_FillRect(30, 60, 150, 10); //suwak

	BSP_LCD_DisplayStringAt(0, 80, (uint8_t*) "I", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 80, (uint8_t*) "0.00", RIGHT_MODE);
	BSP_LCD_FillRect(30, 80, 150, 10);

	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*) "D", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*) "0.00", RIGHT_MODE);
	BSP_LCD_FillRect(30, 100, 150, 10);

DrawBackButton();

}
void Display_Testy(void) {
	uint8_t desc[50];

	/* Set LCD Foreground Layer  */
	PrepareScene();
	/* Set the LCD Text Color */
	DrawTitleBar("TESTY");

	BSP_LCD_DisplayStringAt(0, 60, (uint8_t*) "MPU_A", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 60, (uint8_t*) "0.00 0.00 0.00", RIGHT_MODE);

	BSP_LCD_DisplayStringAt(0, 80, (uint8_t*) "MPU_G", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 80, (uint8_t*) "0.00 0.00 0.00", RIGHT_MODE);

	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*) "ESP", LEFT_MODE);
	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*) "no connection", RIGHT_MODE);

	DrawBackButton();
}
void Display_Autorzy(void) {
	uint8_t desc[50];

	/* Set LCD Foreground Layer  */
	PrepareScene();
DrawTitleBar("AUTORZY");

	BSP_LCD_DisplayStringAt(0, 60, (uint8_t*) "Sterowniki robotow projekt",
			CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 80, (uint8_t*) "2019", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 100, (uint8_t*) "Michal Nowak 235xxx",
			CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 120, (uint8_t*) "Artur Kowalczyk 235775",
			CENTER_MODE);

	DrawBackButton();

}

void Display_Touch(int x, int y, uint8_t* mpu_text) {

	PrepareScene();

	BSP_LCD_SetTextColor(LCD_COLOR_DARKBLUE);
	//BSP_LCD_DisplayStringAt(0, 10, (uint8_t*)"STM32F429I BSP", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 10, (uint8_t*) "Projekt SR", CENTER_MODE);
	BSP_LCD_SetFont(&Font16);
	BSP_LCD_DisplayStringAt(0, 35, (uint8_t*) "Test dotyku", CENTER_MODE);
	BSP_LCD_DisplayStringAt(0, 60, mpu_text, CENTER_MODE);
	//BSP_LCD_DisplayStringAt(0, 60, mpu, CENTER_MODE); TODO: fixit

	BSP_LCD_FillRect(x, y, 10, 10);

	//sprintf((char *)desc,"%s example", BSP_examples[DemoIndex].DemoName);
	//BSP_LCD_DisplayStringAt(0, BSP_LCD_GetYSize() / 2 + 45, (uint8_t *) desc,
	//		CENTER_MODE);
}

void Display_Steruj(void) {
	uint8_t desc[50];

	/* Set LCD Foreground Layer  */
	PrepareScene();
	/* Set the LCD Text Color */
	DrawTitleBar("STERUJ");
	DrawBackButton();

}

void Handle_Menu() {
	//BSP_TS_GetState(p_struktura);
	if (p_struktura->TouchDetected) {
		if (p_struktura->X <= BSP_LCD_GetXSize() / 2) //lewa polowa ekranu
				{
			if (p_struktura->Y <= BSP_LCD_GetYSize() / 2) //gorna polowa ekranu
					{
				scena = STEROWANIE;
				refreshSterowanieFlag = 1;
			} else  //dolna
			{
				scena = TESTY;
				refreshTestyFlag = 1;
			}
		} else //prawa polowa ekranu
		{
			if (p_struktura->Y <= BSP_LCD_GetYSize() / 2) //gorna polowa ekranu
					{
				scena = NASTAWY;
				refreshNastawyFlag = 1;
			} else  //dolna
			{
				scena = AUTORZY;
				refreshAutorzyFlag = 1;
			}
		}
	}

}
void Handle_Steruj() {
	if (p_struktura->TouchDetected) {
		if (p_struktura->Y >= BSP_LCD_GetYSize() - 30) {
			scena = MENU;
			refreshMenuFlag = 1;
			HAL_Delay(500);
		}
	}

}
void Handle_Nastawy() {
	if (p_struktura->TouchDetected) {
		if (p_struktura->Y >= BSP_LCD_GetYSize() - 30) {
			scena = MENU;
			refreshMenuFlag = 1;
			HAL_Delay(500);
		}
	}
}
void Handle_Testy() {
	if (p_struktura->TouchDetected) {
		if (p_struktura->Y >= BSP_LCD_GetYSize() - 30) {
			scena = MENU;
			refreshMenuFlag = 1;
			HAL_Delay(500);
		}
	}
}
void Handle_Autorzy() {
	if (p_struktura->TouchDetected) {
		if (p_struktura->Y >= BSP_LCD_GetYSize() - 30) {
			scena = MENU;
			refreshMenuFlag = 1;
			HAL_Delay(500);
		}
	}
}
int getLed() {
	return *led;
}
