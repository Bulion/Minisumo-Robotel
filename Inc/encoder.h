#ifndef __ENCODER_H
#define __ENCODER_H
#include "tim.h"
#include "observer.h"
#include <stdint.h>

class Encoder : public TimerObserver {
public:
    Encoder(TIM_HandleTypeDef *htim, uint16_t ticksPerRev, 
            uint16_t wheelDiameterInMM, float gearRatio = 1.0f, 
            uint32_t timerMaxValue = UINT16_MAX);
    ~Encoder() {};

    void update(float dt);
    uint32_t getTickValue();
    int32_t getSpeedInMMPS();
    int32_t getRPM();
private:
    int32_t getTicksDelta(const uint32_t currCntVal);
    int32_t calcRPM(const int32_t countedTicks, float dt);
    int32_t calcSpeedInMMPS();

    TIM_HandleTypeDef *htim;
    int32_t timerOverrunValue;
    uint32_t timerMaxValue;
    uint16_t ticksPerRev;
    uint32_t lastCounterValue;
    uint16_t mmPerRev;
    int32_t currRPM;
    int32_t currSpeedInMMPS;
};

#endif