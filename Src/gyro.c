#include "spi.h"
#include "gyro.h"
#include "FreeRTOS.h"
#include "task.h"

void writegyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data) {
    taskENTER_CRITICAL();
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI, &address, 1, 50);
	HAL_SPI_Transmit(&SPI, &data, 1, 50);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
    taskEXIT_CRITICAL();
}

uint8_t readgyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data) {
	address = address | 0x80;
    taskENTER_CRITICAL();
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI, &address, 1, 50);
	HAL_SPI_Receive(&SPI, &data, 1, 50);
	HAL_GPIO_WritePin(NCS_MEMS_SPI_GPIO_Port, NCS_MEMS_SPI_Pin, GPIO_PIN_SET);
    taskEXIT_CRITICAL();

	return data;
}

void gyro_init() {
	writegyro(hspi5, 0x20, 0x0F);
	writegyro(hspi5, 0x23, 0x30);
	HAL_Delay(100);
}

void read_gyro(int *gyrox, int *gyroy, int *gyroz) {
	static char datax[2] = { 0 };
	static char datay[2] = { 0 };
	static char dataz[2] = { 0 };
	static float xgyro = 0;
	static float ygyro = 0;
	static float zgyro = 0;
	static float delta[3] = { 0 };
	static float current[3] = { 0 };
	static float time_delay = 10;

	datax[0] = readgyro(hspi5, 0x28, datax[0]);
	datax[1] = readgyro(hspi5, 0x29, datax[1]);

	datay[0] = readgyro(hspi5, 0x2A, datay[0]);
	datay[1] = readgyro(hspi5, 0x2B, datay[1]);

	dataz[0] = readgyro(hspi5, 0x2C, dataz[0]);
	dataz[1] = readgyro(hspi5, 0x2D, dataz[1]);

	xgyro = datax[1] * 256 + datax[0];
	if (xgyro > 32767) {
		xgyro -= 65536;
	}
	ygyro = datay[1] * 256 + datay[0];
	if (ygyro > 32767) {
		ygyro -= 65536;
	}
	zgyro = dataz[1] * 256 + dataz[0];
	if (zgyro > 32767) {
		zgyro -= 65536;
	}
	xgyro -= 29;
	ygyro -= 8;
	zgyro += 12;
	xgyro *= 0.07;
	ygyro *= 0.07;
	zgyro *= 0.07;

	delta[0] = xgyro * (time_delay);
	current[0] += delta[0];

	delta[1] = ygyro * (time_delay);
	current[1] += delta[1];

	delta[2] = zgyro * (time_delay);
	current[2] += delta[2];

	*gyrox = ((int) current[0])/182/8;
	*gyroy = ((int) current[1])/182/8;
	*gyroz = ((int) current[2])/182/8;
}
