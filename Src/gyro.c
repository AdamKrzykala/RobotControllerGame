#include "gyro.h"

void writegyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data) {
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI, &address, 1, 50);
	HAL_SPI_Transmit(&SPI, &data, 1, 50);
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);
}

uint8_t readgyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data) {
	address = address | 0x80;
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&SPI, &address, 1, 50);
	HAL_SPI_Receive(&SPI, &data, 1, 50);
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);

	return data;
}
