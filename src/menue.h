#ifndef _MENUE_H_
#define _MENUE_H_
#include "constants.h"

class menue {
    private:
    const char **myNames, **myShorts, **myMenue, **myLabels;

    public:
    menue(const char* const *someNames, const char* const *someShorts, const char* const *someMenue, const char* const *someLabels);

    void changeState(bool aMenueState);
    void processSignal(constants::inputSignal aSignal);
    void update(void);
};

#endif