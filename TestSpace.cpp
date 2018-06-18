

#include "TestSpace.hpp"

TestSpace::TestSpace(char symbol)
{
	setSymbol(symbol);
}

TestSpace::TestSpace(char symbol, ANSIColor color)
{
	setSymbol(symbol);
	setColor(color);
}

void TestSpace::checkForEvent()
{

}
