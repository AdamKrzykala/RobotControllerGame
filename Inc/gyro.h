#include "main.h"

uint8_t readgyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data);
void writegyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data);
void read_gyro(int *gyrox, int *gyroy, int *gyroz);
void gyro_init();
