#ifndef __MOTOR_H
#define __MOTOR_H

#include "observer.h"

class Motor : TimerObserver {
public:
    Motor();
    ~Motor() {};

    void setSpeedInMMPS(int16_t speedInMMPS);
    void setAcceleration(uint32_t accelerationInMMPS2);
    void update(const float dt);
private:


}

#endif