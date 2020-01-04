#ifndef __KERNEL_H
#define __KERNEL_H

#include <unordered_map>
#include <vector>
#include "tim.h"
#include "observer.h"

class Kernel {
public:
    static Kernel* getInstance();

    void registerObserverToTimerInterrupt(TIM_HandleTypeDef *htim, 
                                          TimerObserver *observer);
    void timerInterruptNotification(TIM_HandleTypeDef *htim);

private:
    Kernel();
    ~Kernel();

    static Kernel* instance;

    std::unordered_map< TIM_HandleTypeDef*, std::vector< TimerObserver* > > timersObservers;
};

#endif