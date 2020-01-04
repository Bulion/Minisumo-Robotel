#include "encoder.h"

#define M_PI 3.14159265358979323846  /* pi */

Encoder::Encoder(TIM_HandleTypeDef *htim, uint16_t ticksPerRev, 
                 uint16_t wheelDiameterInMM, uint16_t dt, 
                 float gearRatio, uint32_t timerMaxValue): 
      htim(htim)
    , dt(dt)
    , timerOverrunValue(timerMaxValue / 2)
    , timerMaxValue(timerMaxValue)
    , ticksPerRev(ticksPerRev * gearRatio)
    , lastCounterValue(htim->Instance->CNT)
    , mmPerRev(M_PI * wheelDiameterInMM)
    , currRPM(0)
    , currSpeedInMMPS(0)
{
    HAL_TIM_Encoder_Start(htim, TIM_CHANNEL_ALL);
}

int32_t Encoder::getTicksDelta(const uint32_t currCntVal)
{
    int32_t delta = currCntVal - lastCounterValue;
    
    lastCounterValue = currCntVal;

    if(delta > timerOverrunValue)
    {
        delta -= timerMaxValue;
    }
    if(delta < -timerOverrunValue)
    {
        delta += timerMaxValue;
    }

    return delta;
}

inline int32_t Encoder::calcRPM(const int32_t countedTicks)
{
    const uint16_t msInMinute = 60000;
    return (int32_t)(countedTicks * msInMinute) / (int32_t)(ticksPerRev * dt);
}

inline int32_t Encoder::calcSpeedInMMPS()
{
    const uint8_t secInMinute = 60;
    return (currRPM * mmPerRev) / secInMinute;
}

void Encoder::update()
{
    const int32_t countedTicks = getTicksDelta(htim->Instance->CNT);
    currRPM = calcRPM(countedTicks);
    currSpeedInMMPS = calcSpeedInMMPS();
}
