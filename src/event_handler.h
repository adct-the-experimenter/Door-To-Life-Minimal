#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "globalvariables.h"
#include <cstdint>
#include <queue>

extern SDL_Event sdl_event;

enum class Event : std::int8_t {
 
        NONE = 0,
        
    //Keys
        //arrows
        UP_ARROW, LEFT_ARROW, DOWN_ARROW, RIGHT_ARROW,
        UP_ARROW_REPEAT, LEFT_ARROW_REPEAT, DOWN_ARROW_REPEAT, RIGHT_ARROW_REPEAT,
        UP_ARROW_RELEASE,LEFT_ARROW_RELEASE,DOWN_ARROW_RELEASE,RIGHT_ARROW_RELEASE,
        // space
        SPACE, SPACE_REPEAT, SPACE_RELEASE,
        //Enter
        ENTER,
        //escape
        ESCAPE,
        
        //Various keys
        G,V,B,N,R,
    //Quit
        QUIT_WINDOW
};

//queue of events, first in first out order
extern std::queue <Event> event_instances_queue;

//function to push event into queue
void pushEventInstance(Event thisEvent);

//function to pop event from queue. pops event in front
void popEventInstanceFromFront();

//function to tell whether event queue is empty or not
bool isEventQueueEmpty();

//function to get event in front of queue
Event& getEventInstanceFront();

//function to clear events on queue
void clearEventsQueue();

//function to run loop for event and set event 
void run_event_handler();
//function to set events in queue
void readAndSetEventQueue(SDL_Event* sdl_event_ptr);

#endif