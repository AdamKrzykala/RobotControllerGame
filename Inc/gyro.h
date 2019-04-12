#include "main.h"

//uint8_t config_address = 0x20;
//uint8_t config_data = 0x27;
//uint8_t Address_ACCX = 0x29;
//uint8_t Address_ACCY = 0x2B;
//uint8_t Address_ACCZ = 0x2D;
//
//uint8_t x = 0;
//uint8_t y = 0;
//uint8_t z = 0;

uint8_t readgyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data);
void writegyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data);
