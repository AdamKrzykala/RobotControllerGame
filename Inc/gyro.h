#include "main.h"

uint8_t readgyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data);
void writegyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data);
void read_gyro(int *gyrox, int *gyroy, int *gyroz);
void gyro_init();

extern char datax[2];
extern char datay[2];
extern char dataz[2];
extern float xgyro;
extern float ygyro;
extern float zgyro;
extern float delta[3];
extern float current[3];
extern float time_delay;
