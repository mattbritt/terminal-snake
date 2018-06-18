

#ifndef TESTSPACE_HPP
#define TESTSPACE_HPP

#include "Space.hpp"

class TestSpace : public Space
{
private:

public:
	TestSpace(char symbol);
	TestSpace(char symbol, ANSIColor color);

	void checkForEvent() override;
};

#endif
