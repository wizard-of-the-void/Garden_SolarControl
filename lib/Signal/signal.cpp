#include "signal.h"

triggerSignal::triggerSignal(uint8_t aSource, uint8_t aDelay, DateTime aCreation) {
    myCreation = aCreation;
    myDelay = aDelay;
    mySource = aSource;
}

const uint8_t triggerSignal::get_source() {
    return mySource;
}

const DateTime triggerSignal::get_creation() {
    return myCreation;
}

const uint8_t triggerSignal::get_Delay() {
    return myDelay;
}

const DateTime triggerSignal::get_expiration() {
    return myCreation + TimeSpan(60 * myDelay);
}


signalInterface::signalInterface(signalRouter *aRouter) {
    theRouter = aRouter;
}

void signalInterface::checkInputs() {
    uint8_t lastPin = myMcp.getLastInterruptPin();
    theRouter->issueSignal(triggerSignal(lastPin, myDelays[lastPin], ));
}