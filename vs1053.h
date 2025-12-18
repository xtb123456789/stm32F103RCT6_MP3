
#ifndef __VS1053_H
#define __VS1053_H

#include "stm32f1xx_hal.h"

// VS1053 寄存器地址
#define VS1053_REG_MODE         0x00
#define VS1053_REG_STATUS       0x01
#define VS1053_REG_BASS         0x02
#define VS1053_REG_CLOCKF       0x03
#define VS1053_REG_DECODE_TIME  0x04
#define VS1053_REG_AUDATA       0x05
#define VS1053_REG_WRAM         0x06
#define VS1053_REG_WRAMADDR     0x07
#define VS1053_REG_HDAT0        0x08
#define VS1053_REG_HDAT1        0x09
#define VS1053_REG_AIADDR       0x0A
#define VS1053_REG_VOL          0x0B



//CubeMX 配置宏
#define VS1053_CS_LOW()    HAL_GPIO_WritePin(SPI1_XCS_GPIO_Port, SPI1_XCS_Pin, GPIO_PIN_RESET)
#define VS1053_CS_HIGH()   HAL_GPIO_WritePin(SPI1_XCS_GPIO_Port, SPI1_XCS_Pin, GPIO_PIN_SET)
#define VS1053_DCS_LOW()   HAL_GPIO_WritePin(SPI1_XDCS_GPIO_Port, SPI1_XDCS_Pin, GPIO_PIN_RESET)
#define VS1053_DCS_HIGH()  HAL_GPIO_WritePin(SPI1_XDCS_GPIO_Port, SPI1_XDCS_Pin, GPIO_PIN_SET)
#define VS1053_RST_LOW()   HAL_GPIO_WritePin(SPI1_RESET_GPIO_Port, SPI1_RESET_Pin, GPIO_PIN_RESET)
#define VS1053_RST_HIGH()  HAL_GPIO_WritePin(SPI1_RESET_GPIO_Port, SPI1_RESET_Pin, GPIO_PIN_SET)
#define VS1053_DREQ_READ() HAL_GPIO_ReadPin(SPI1_DREQ_GPIO_Port, SPI1_DREQ_Pin)




// VS1053 命令
#define VS1053_WRITE_COMMAND    0x02
#define VS1053_READ_COMMAND     0x03

// VS1053 控制接口函数
void VS1053_Init(void);
void VS1053_Reset(void);
void VS1053_WriteRegister(uint8_t address, uint16_t value);
uint16_t VS1053_ReadRegister(uint8_t address);
void VS1053_SetVolume(uint8_t left, uint8_t right);
void VS1053_SendMusicData(uint8_t *data, uint16_t len);
#endif 
