#include "stm32f1xx_hal.h"
#include "gpio.h"
#include "vs1053.h"
#include "spi.h"

//// 用户需根据 CubeMX 配置修改这些宏
//#define VS1053_CS_LOW()    HAL_GPIO_WritePin(SPI1_XCS_GPIO_Port, SPI1_XCS_Pin, GPIO_PIN_RESET)
//#define VS1053_CS_HIGH()   HAL_GPIO_WritePin(SPI1_XCS_GPIO_Port, SPI1_XCS_Pin, GPIO_PIN_SET)
//#define VS1053_DCS_LOW()   HAL_GPIO_WritePin(SPI1_XDCS_GPIO_Port, SPI1_XDCS_Pin, GPIO_PIN_RESET)
//#define VS1053_DCS_HIGH()  HAL_GPIO_WritePin(SPI1_XDCS_GPIO_Port, SPI1_XDCS_Pin, GPIO_PIN_SET)
//#define VS1053_RST_LOW()   HAL_GPIO_WritePin(SPI1_RESET_GPIO_Port, SPI1_RESET_Pin, GPIO_PIN_RESET)
//#define VS1053_RST_HIGH()  HAL_GPIO_WritePin(SPI1_RESET_GPIO_Port, SPI1_RESET_Pin, GPIO_PIN_SET)
//#define VS1053_DREQ_READ() HAL_GPIO_ReadPin(SPI1_DREQ_GPIO_Port, SPI1_DREQ_Pin)

extern SPI_HandleTypeDef hspi1;

uint8_t VS1053_SPI_RW(uint8_t data)
{
    uint8_t rx = 0;
    HAL_SPI_TransmitReceive(&hspi1, &data, &rx, 1, HAL_MAX_DELAY);
    return rx;
}

void VS1053_Reset(void)
{
    VS1053_DCS_HIGH();
    VS1053_CS_HIGH();
    VS1053_RST_LOW();
    HAL_Delay(2);
    VS1053_RST_HIGH();
    HAL_Delay(100);
    while (VS1053_DREQ_READ() == GPIO_PIN_RESET);
}

void VS1053_WriteRegister(uint8_t address, uint16_t value)
{
    while (VS1053_DREQ_READ() == GPIO_PIN_RESET);
    VS1053_CS_LOW();
    VS1053_SPI_RW(VS1053_WRITE_COMMAND);
    VS1053_SPI_RW(address);
    VS1053_SPI_RW((value >> 8) & 0xFF);
    VS1053_SPI_RW(value & 0xFF);
    VS1053_CS_HIGH();
}

uint16_t VS1053_ReadRegister(uint8_t address)
{
    uint16_t value = 0;
    while (VS1053_DREQ_READ() == GPIO_PIN_RESET);
    VS1053_CS_LOW();
    VS1053_SPI_RW(VS1053_READ_COMMAND);
    VS1053_SPI_RW(address);
    value = VS1053_SPI_RW(0xFF) << 8;
    value |= VS1053_SPI_RW(0xFF);
    VS1053_CS_HIGH();
    return value;
}

void VS1053_SetVolume(uint8_t left, uint8_t right)
{
    uint16_t vol = ((left & 0xFF) << 8) | (right & 0xFF);
    VS1053_WriteRegister(VS1053_REG_VOL, vol);
}

void VS1053_SendMusicData(uint8_t *data, uint16_t len)
{
    while (VS1053_DREQ_READ() == GPIO_PIN_RESET);
    VS1053_DCS_LOW();
    for (uint16_t i = 0; i < len; i++)
    {
        VS1053_SPI_RW(data[i]);
    }
    VS1053_DCS_HIGH();
}

void VS1053_Init(void)
{
    VS1053_Reset();
    VS1053_WriteRegister(VS1053_REG_MODE, 0x0800); // 软件复位
    HAL_Delay(2);
    VS1053_WriteRegister(VS1053_REG_CLOCKF, 0x6000); // 3.0x 时钟
	  HAL_Delay(2);
    VS1053_WriteRegister(VS1053_REG_VOL,0x2020);
	  HAL_Delay(2);
}