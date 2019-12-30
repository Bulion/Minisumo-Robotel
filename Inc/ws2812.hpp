#ifndef __WS2812_H
#define __WS2812_H

#include <stdint.h>
#include "tim.h"
#include "gpio.h"

#define BITS_PER_COLOR 8
#define BITS_PER_LED (BITS_PER_COLOR*3)
#define MAX_NUM_OF_LEDS 1
#define LED_ARRAY_LENGTH (MAX_NUM_OF_LEDS*BITS_PER_LED)

typedef union
{
    struct {
        uint8_t blue;
        uint8_t red;
        uint8_t green;
    };
    uint32_t raw;
} ws2812LedColor;


class ws2812 {
public:
    ws2812(GPIO_TypeDef *GPIOx, uint16_t gpioPin, uint16_t numberOfLEDs);
    ws2812(TIM_HandleTypeDef *htim, uint32_t Channel, uint16_t numberOfLEDs);
    ~ws2812() {};

    void setMaximumBrightnes(uint8_t maxBrightnes);
    void setLedColor(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue);
    void setLedsColor(uint8_t startLedNum, uint8_t stopLedNum, uint8_t red, uint8_t green, uint8_t blue);
    void clear();

    ws2812LedColor ledsColorArray[MAX_NUM_OF_LEDS];

private:
    enum stripDataInterface {
        GPIO_Based,
        TIM_Based,
        SPI_Based
    };

    void calculateStripData(uint16_t ledNumber, ws2812LedColor ledData);
    void sendDataToStrip();

    GPIO_TypeDef       *GPIOx;
    uint16_t           gpioPin;

    TIM_HandleTypeDef  *htim;
    uint32_t           timChannel;

    uint16_t           highStateValue;
    uint16_t           lowStateValue;

    uint16_t           numberOfLEDs;
    uint8_t            maxBrightnes;

    uint8_t            stripDataBuffer[2][LED_ARRAY_LENGTH];
    uint8_t            currentlyUnusedBuffer;
    uint8_t            lastUsedBuffer;
    stripDataInterface interfaceType;
};

#endif