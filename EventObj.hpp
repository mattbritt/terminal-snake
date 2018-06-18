/**********************************************************************
**	Event.hpp
**	Author: Matt Britt
**	Date: 12/3/2017
**	Description:   Event.hpp is the header file for the Event class.
**				The Event class implements a simple event passing system that
**				allows events to be shared amongst the classes of the program.
*********************************************************************/

#ifndef EVENTOBJ_HPP
#define EVENTOBJ_HPP

#include <string>
#include <vector>
#include <time.h>

using std::string;
using std::vector;

enum EventCode {												// available event codes to check for
	ERROR_EVENT,
	MOVE,
	SECOND,
	COLLIDE,
	POINT,
	EXTEND,
	WON,
	LOST
};


struct EventStruct {											// struct to hold event properties
	string message;
	int number;
	EventCode code;

	EventStruct(string mes, EventCode cod ,int num=-1) {
		message = mes;
		number = num;
		code = cod;
	}
};

class EventObj
{
private: 
	
	static vector<EventStruct> eventsVector;					// vector that holds all events
	static clock_t startTime;									// timer to compare against 

public:
	EventObj();													// constructor
	void addEvent(EventStruct eStruct);							// push new event to vector
	void addEvent(string mes, EventCode cod);					// push string and code and create event

	const vector<EventStruct>&  getEvents();					// returns events vector
	void clearEvents();											// clears events

	clock_t updateTime();										// updates time and returns the current elapsed time
	void resetTimer();											// resets timer

	void removeIndex(int index);								// removes event at index
	void clearEvent(EventCode eCode);							// removes all events matching eCode

	int eventIndex(EventCode eCode);							// returns index of 1st eCode found (-1 == not found)

};

#endif 


