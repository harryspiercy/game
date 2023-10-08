#ifndef _TIMER_H_
#define _TIMER_H_

#include "common.h"

class LTimer{
public:
    //! Initialise variables
    /*!
    */
    LTimer();

    //! Start a new timer from 0
    /*!
    */
    void start();

    //! End the active timer
    /*!
    */
    void stop();

    //! Pause the timer
    /*!
    */
    void pause();

    //! Unpause a paused timer
    /*!
    */
    void unpause();

    //! Get the timers time
    /*!
    */
    Uint32 getTicks();

    //! Checked the start status of the timer
    /*!
    */
    inline bool isStarted() { return mStarted; }

    //! Check the paused status of the timer
    /*!
    */
    inline bool isPaused() { return mPaused && mStarted; }

private:
    //! Clock time when the timer is started
    /*!
    */
    Uint32 mStartTicks;

    //! The ticks stored when the timer was paused
    /*!
    */
    Uint32 mPausedTicks;

    //! Timer started status
    /*!
    */
    bool mStarted;

    //! Timer paused status
    /*!
    */
    bool mPaused;


};

#endif