/*
 * menu.h
 *
 *  Created on: Mar 27, 2019
 *      Author: Artur
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include "stm32f429i_discovery_ts.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery.h"



TS_StateTypeDef* p_struktura;
volatile int* led;
enum SCENY {
	MENU, STEROWANIE, NASTAWY, TESTY, AUTORZY
};

enum SCENY scena;

void initMenu(TS_StateTypeDef* arg_struktura);
int getLed();
void DisplayCurrentScene(void);
void HandleCurrentScene(void);
void PrepareScene(void);
void DrawBackButton(void);
void DrawTitleBar(uint8_t* title);

void Display_Menu(void);
void Display_Splash(void);
void Display_Touch(int x, int y, uint8_t* mpu_text);

void Display_Steruj(void);
void Display_Nastawy(void);
void Display_Testy(void);
void Display_Autorzy(void);

void Handle_Menu();
void Handle_Steruj();
void Handle_Nastawy();
void Handle_Testy();
void Handle_Autorzy();
#endif /* MENU_H_ */
