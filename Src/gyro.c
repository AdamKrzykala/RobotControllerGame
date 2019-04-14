#include "gyro.h"

void writegyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data) {
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit_DMA(&SPI, &address, 1);
	HAL_SPI_Transmit_DMA(&SPI, &data, 1);
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);
}

uint8_t readgyro(SPI_HandleTypeDef SPI, uint8_t address, uint8_t data) {
	address = address | 0x80;
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit_DMA(&SPI, &address, 1);
	HAL_SPI_Receive_DMA(&SPI, &data, 1);
	HAL_GPIO_WritePin(SPI5_CS_GPIO_Port, SPI5_CS_Pin, GPIO_PIN_SET);

	return data;
}
