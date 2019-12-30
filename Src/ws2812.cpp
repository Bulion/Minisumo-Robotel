#include "ws2812.hpp"

ws2812::ws2812(GPIO_TypeDef *GPIOx, uint16_t gpioPin, uint16_t numberOfLEDs) :
    GPIOx(GPIOx),
    gpioPin(gpioPin),
    htim(nullptr),
    timChannel(0),
    lastUsedBuffer(0)
{
    if(numberOfLEDs > MAX_NUM_OF_LEDS)
    {
        this->numberOfLEDs = MAX_NUM_OF_LEDS;
    }
    else
    {
        this->numberOfLEDs = numberOfLEDs;
    }
    interfaceType = GPIO_Based;
}

ws2812::ws2812(TIM_HandleTypeDef *htim, uint32_t channel, uint16_t numberOfLEDs) :
    GPIOx(nullptr),
    gpioPin(0),
    htim(htim),
    timChannel(channel),
    lastUsedBuffer(0)
{
    if(numberOfLEDs > MAX_NUM_OF_LEDS)
    {
        this->numberOfLEDs = MAX_NUM_OF_LEDS;
    }
    else
    {
        this->numberOfLEDs = numberOfLEDs;
    }
    const uint32_t ledDataBusFreq = 800000;
    const uint32_t sysClockFreq = HAL_RCC_GetSysClockFreq();
    const uint32_t timerClockDivider = (sysClockFreq / ledDataBusFreq) - 1;
    __HAL_TIM_SET_AUTORELOAD(htim, timerClockDivider);
    __HAL_TIM_SET_PRESCALER(htim, 0);
    if(__HAL_TIM_IS_TIM_COUNTING_DOWN(htim))
    {
        highStateValue = timerClockDivider/3;
        lowStateValue = timerClockDivider*0.6667;
        stripDataBuffer[0][numberOfLEDs*BITS_PER_LED] = timerClockDivider;
        stripDataBuffer[1][numberOfLEDs*BITS_PER_LED] = timerClockDivider;
    }
    else
    {
        highStateValue = (timerClockDivider*0.6667)+1;
        lowStateValue = (timerClockDivider/3)+1;
        stripDataBuffer[0][numberOfLEDs*BITS_PER_LED] = 0;
        stripDataBuffer[1][numberOfLEDs*BITS_PER_LED] = 0;
    }
    
    interfaceType = TIM_Based;
    clear();
}

void ws2812::clear()
{
    for(int i = 0; i < numberOfLEDs; ++i)
    {
        ledsColorArray[i].green = 0;
        ledsColorArray[i].red = 0;
        ledsColorArray[i].blue = 0;
        calculateStripData(i, ledsColorArray[i]);
    }
    sendDataToStrip();
}

void ws2812::setMaximumBrightnes(uint8_t maxBrightnes)
{
    this->maxBrightnes = maxBrightnes;
}

void ws2812::setLedColor(uint8_t ledNumber, uint8_t red, uint8_t green, uint8_t blue)
{
    ledsColorArray[ledNumber].green = green;
    ledsColorArray[ledNumber].red = red;
    ledsColorArray[ledNumber].blue = blue;
    calculateStripData(ledNumber, ledsColorArray[ledNumber]);
    sendDataToStrip();
}

void ws2812::calculateStripData(uint16_t ledNumber, ws2812LedColor ledData)
{
    uint16_t arrayStartAddres = ledNumber * BITS_PER_LED;
    
    uint32_t bitShiftedMask = (1 << BITS_PER_LED);
    for(int i = 0; i < BITS_PER_LED; ++i)
    {
        if(ledData.raw & bitShiftedMask)
        {
            stripDataBuffer[0][arrayStartAddres + i] = highStateValue;
        }
        else
        {
            stripDataBuffer[0][arrayStartAddres + i] = lowStateValue;
        }
        bitShiftedMask >>= 1;
    }
}

void ws2812::sendDataToStrip()
{
    if(interfaceType == TIM_Based)
    {
        HAL_TIM_PWM_Start_DMA(htim, timChannel, (uint32_t *)stripDataBuffer[0], (numberOfLEDs*BITS_PER_LED)+1);
    }
}