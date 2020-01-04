#ifndef __KERNEL_H
#define __KERNEL_H

#include <functional>
#include <utility>
#include <vector>
#include "tim.h"

class Kernel {
public:
    static Kernel* getInstance();

    void registerCallbackToTimerInterrupt(TIM_HandleTypeDef *htim, 
                                          std::function<void()> fcn);


private:
    Kernel();
    ~Kernel();

    static Kernel* instance;

    std::vector< std::pair< TIM_HandleTypeDef*, 
                            std::function<void()> > > timCallbacksVect;
};

#endif