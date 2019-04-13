/*
 * menu.h
 *
 *  Created on: Mar 30, 2019
 *      Author: Adam
 */

#ifndef MENU_H_
#define MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include "stm32f429i_discovery_ts.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery.h"
#include "globalstruct.h"



TS_StateTypeDef* localstr;
void initMenu(TS_StateTypeDef* str);
void odczytyService(void);
void menuService(void);
void Display_Odczyty(globalClass* globalClassHandler);
void Display_Menu(globalClass* globalClassHandler);
void Service(globalClass* globalClassHandler);
void Display(globalClass* globalClassHandler);
void DrawButton(char* text, uint8_t line_number);
void initMenu(TS_StateTypeDef* str);
#endif /* MENU_H_ */
