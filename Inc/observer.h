#ifndef __OBSERVER_H
#define __OBSERVER_H

class TimerObserver {
public:
    virtual void update(const float dt) = 0;
};

#endif