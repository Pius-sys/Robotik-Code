#ifndef EVENTS_1_H_INCLUDED
#define EVENTS_1_H_INCLUDED
#include "nnxt.h"


#define EVENT_1 0
#define EVENT_2 1
#define EVENT_3 2
#define EVENT_4 3

typedef uint8_t EventType;

void setEvent(EventType ev);

uint8_t eventIsSet(EventType ev);

void clearEvent(EventType ev);

#endif /* EVENTS_1_H_INCLUDED */

Nächste FILE 


#include "events_1.h"
#include "nnxt.h"

volatile uint16_t events = 0;

void setEvent(EventType ev){
    events |= (1 << ev);
}

uint8_t eventIsSet(EventType ev){
    if(events & (1 << ev)){
        return 1;
    }
    else{
        return 0;
    }
}


void clearEvent(EventType ev){
    events &= ~(1 << ev);
}


Nächste FILE 

#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include "events_1.h"
#include "nnxt.h"



typedef uint8_t TimerType;

void setTimer(TimerType timer, int time, EventType ev);

void startTimer(TimerType timer);

void cancelTimer(TimerType timer);

void task4();

#endif /* TIMER_H_INCLUDED */


Nächste FILE 

#include "events.h"
#include "timer.h"
#include "nnxt.h"

typedef struct Timer_struct {
  uint32_t time;
  uint32_t starttime;
  EventType ev;
  uint8_t running;
}Timer_struct;


Timer_struct timer_array[2];

void setTimer(TimerType timer, int time, EventType ev){
    timer_array[timer].time = time;
    timer_array[timer].ev = ev;
    timer_array[timer].running = 0;
}

void startTimer(TimerType timer){
    timer_array[timer].starttime = GetSysTime();
    timer_array[timer].running = 1;
}


void cancelTimer(TimerType timer){
    clearEvent(timer_array[timer].ev);
}

void task4(){
    while(1){
        if(timer_array[0].running == 1){
            if((GetSysTime() - timer_array[0].starttime) > timer_array[0].time){
                setEvent(timer_array[0].ev);
                timer_array[0].running = 0;
            }
        }
        if(timer_array[1].running == 1){
                if((GetSysTime() - timer_array[1].starttime) > timer_array[1].time){
                    setEvent(timer_array[1].ev);
                    timer_array[1].running = 0;
            }
        }
    }
}
