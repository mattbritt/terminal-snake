/**********************************************************************
**	EventObj.cpp
**	Author: Matt Britt
**	Date: 12/3/2017
**	Description:   EventObj.cpp is the implmentation file for the EventObj class.
**				The EventObj class implements a simple event passing system that
**				allows events to be shared amongst the classes of the program.
*********************************************************************/

#include "EventObj.hpp"

// static vars
vector<EventStruct> EventObj::eventsVector;
clock_t EventObj::startTime;

/********************************************************************
**  EventObj()
**	Description:  Default constructor
*********************************************************************/
EventObj::EventObj()
{

}

/********************************************************************
**  void addEvent(EventStruct eStruct)
**	Description:  Adds new event
*********************************************************************/
void EventObj::addEvent(EventStruct eStruct)
{
	eventsVector.push_back(eStruct);
}

/********************************************************************
**  void addEvent(string mes, EventCode cod)
**	Description:  Adds new event by creating EventStruct from mes and cod
*********************************************************************/
void EventObj::addEvent(string mes, EventCode cod)
{
	addEvent(EventStruct(mes, cod));
}

/********************************************************************
**  const vector<EventStruct>& getEvents()
**	Description:  returns events vector
*********************************************************************/
const vector<EventStruct>& EventObj::getEvents()
{
	return eventsVector;
}

/********************************************************************
**  void clearEvents()
**	Description:  Clears events
*********************************************************************/
void EventObj::clearEvents()
{
	eventsVector.clear();
}

/********************************************************************
**  void resetTimer()
**	Description:  Resets timer
*********************************************************************/
void EventObj::resetTimer()
{
	startTime = clock();  // set timer to current time
	clearEvent(SECOND);
}

/********************************************************************
**  double updateTime()
**	Description:  updates time and returns current elapsed time
*********************************************************************/
clock_t EventObj::updateTime()
{
	clock_t newTime = clock();

	// clear any existing SECOND events
	if (eventIndex(SECOND) > -1)
	{
		clearEvent(SECOND);
	}
	
	// if we have 1 second, reset timer and add SECOND event
	if (newTime - startTime >= CLOCKS_PER_SEC)
	{
		resetTimer();
		addEvent("",SECOND);
	}

	return newTime;
}


/********************************************************************
**  int eventIndex(EventCode eCode)
**	Description:  returns 1st index found matching eCode (-1 == not found)
*********************************************************************/
int EventObj::eventIndex(EventCode eCode)
{
	for (int i = 0; i < eventsVector.size(); i++)
	{
		if (eventsVector[i].code == eCode)
		{
			return i;
		}
	}

	// index not found
	return -1;
}

/********************************************************************
**  void removeIndex(int index)
**	Description:  Removes events at index
*********************************************************************/
void EventObj::removeIndex(int index)
{
	eventsVector.erase(eventsVector.begin() + index);
}


/********************************************************************
**  void clearEvent(EventCode eCode)
**	Description:  Removes all events matching eCode
*********************************************************************/
void EventObj::clearEvent(EventCode eCode)
{
	for (int i = 0; i < eventsVector.size(); i++)
	{
		// check if index matched eCode
		if (eventsVector[i].code == eCode)
		{
			// erase index && decrement i
			removeIndex(i);
			i--;
		}
	}
}


