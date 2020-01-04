#include "kernel.h"

Kernel* Kernel::instance = 0;

Kernel* Kernel::getInstance()
{
    if (instance == 0)
    {
        instance = new Kernel();
    }

    return instance;
}

Kernel::Kernel()
{

}

Kernel::~Kernel()
{

}

void Kernel::registerObserverToTimerInterrupt(TIM_HandleTypeDef *htim, TimerObserver *observer)
{
    if(timersObservers.find(htim) == timersObservers.end())
    {
        timersObservers[htim] = std::vector<TimerObserver*>{observer};
    }
    else
    {
        timersObservers[htim].push_back(observer);
    }
}

void Kernel::timerInterruptNotification(TIM_HandleTypeDef *htim)
{
    const uint16_t msInSec = 1000;
    const uint32_t timerFreq = HAL_RCC_GetHCLKFreq() / (htim->Instance->PSC + 1);
    for(TimerObserver *obs : timersObservers[htim])
    {
        obs->update(msInSec / (timerFreq / (htim->Instance->ARR + 1)));
    }
}