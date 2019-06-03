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
#include "globalstruct.h"
#include "main.h"



TS_StateTypeDef* localstr;
globalClass* localClassHandler;

void initMenu(TS_StateTypeDef* str, globalClass* globalClassHandler);
void screenRefresh(void);

void menuService(void);
void startService(void);
void odczytyService(void);
void onasService(void);

void Display_Menu(void);
void Display_Start(void);
void Display_Odczyty(void);

void Service(void);
void Display(void);
void DrawButton(char* text, uint8_t line_number);

#endif /* MENU_H_ */
