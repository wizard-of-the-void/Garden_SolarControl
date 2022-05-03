//                                0123456789ABCDEF 
#include "menue.h"

menue::menue(const char* const *someNames, const char* const *someShorts, const char* const *someMenue, const char* const *someLabels) {
    myNames = someNames;
    myShorts = someShorts;
    myMenue = someMenue;
    myLabels = someLabels;
}

void menue::changeState(bool aMenueState) {

}

void menue::processSignal(constants::inputSignal aSignal) {

}

void menue::update(void) {

}