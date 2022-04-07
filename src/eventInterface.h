#ifndef _EVENTINTERFACE_H_
#define _EVENTINTERFACE_H_

#include <RTClib.h>
#include "constants.h"
#include "outputCommand.h"

class eventProcessor {
    private:
        
        const char* myAlias;
        bool myState;
        char myIoMatrix, myDaysOfTheWeek;
        DateTime myStartTime, myEndTime;
        TimeSpan myDuration;
    public:
        const char* getAlias(void);
        const bool getState(void);
        void setState(const bool aState);
        const char getIoMatrix(void);
        void setIoMatrix(const char aMatrix);
        DateTime getStartTime(void);
        void setStartTime(DateTime aStartTime);
        DateTime getEndTime(void);
        void setEndTime(DateTime aEndTime);
        TimeSpan getDuration(void);
        void setDuration(TimeSpan aDuration);

        outputCommand processEvent(void);
};

#endif