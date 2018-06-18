/**********************************************************************
**	Snake.cpp
**	Author: Matt Britt
**	Date: 12/2/2017
**	Description:   Snake.cpp is the implementation file for the Snake class.
**				The Snake class represents the snake in game
*********************************************************************/

#include "Snake.hpp"

/********************************************************************
**  Snake(int row, int col, SpaceGrid &grid)
**	Description:  Constructor, initializes Snake
*********************************************************************/
Snake::Snake(int row, int col, SpaceGridR &grid)
{
	// point gridPtr at grid
	gridPtr = &grid;

	// setup initial snake segment and push to body vector
	snakeSegment seg;
	seg.row = row;
	seg.col = col;

	body.push_front(seg);
}


/********************************************************************
**  void updateGrid()
**	Description:  updates grid with snake
*********************************************************************/
void Snake::updateGrid()
{
	ANSIColor bColor = WHITE;

	// check for lost event
	if (eventObj.eventIndex(LOST) > -1)
	{
		bColor = RED;
	}

	// we just need to update head and tail since only they change each move
	Space *ptr = new SnakeSpace(' ', RED, bColor);

	// if there's more then 1 body segment, update head + 1 and tail
	if (body.size() > 1)
	{
		Space *ptr = new SnakeSpace('x', BLUE, bColor);
		gridPtr->addSpace(body[1].row, body[1].col, ptr);
	
		ptr = new SnakeSpace(' ', WHITE, WHITE);
		gridPtr->addSpace(body.back().row, body.back().col, ptr);
	}

// add snake head to grid
	// add 'eyes' looking side ways or up-down
	if (headDir == LEFT || headDir == RIGHT)
	{
		ptr->setSymbol(':');
	}
	else
	{
		ptr->setSymbol('\"');
	}

	// if COLLIDE event, change colors'
	if (eventObj.eventIndex(COLLIDE) > -1)
	{
		ptr->setBackColor(RED);
		ptr->setColor(WHITE);
	}

	// add new head space to grid
	gridPtr->addSpace(body[0].row, body[0].col, ptr);

}

/********************************************************************
**  void moveSnake(Direction dir)
**	Description:  Moves snake in given direction
*********************************************************************/
void Snake::moveSnake(Direction dir)
{
	// clear any COLLISION  and MOVE events
	eventObj.clearEvent(COLLIDE);
	eventObj.clearEvent(MOVE);

	// get head and tail info
	snakeSegment head = body.front();
	snakeSegment tail = body.back();

	// extending is only set if EXTEND event is true
	bool extendingBool = false;

	// ignore dir if snake is heading into neck segment
	if (dir != lastDir)
	{
		headDir = dir;
	}
	
	// don't move if no direction
	if(headDir == NO_DIR)
	{
		updateGrid();
		return;
	}

	// check if we're EXTENDing the snake
	int extendIndex = eventObj.eventIndex(EXTEND);

	// if we're extending,
	if(extendIndex > -1)
	{
		// set extending
		extendingBool = true;

		// remove one EXTEND event
		eventObj.removeIndex(extendIndex);
	}


	// move snake head in given dir
	switch (headDir)//(dir)
	{
	case UP:
		head.row--;
		lastDir = DOWN;
		break;

	case DOWN:
		head.row++;
		lastDir = UP;
		break;

	case LEFT:
		head.col--;
		lastDir = RIGHT;
		break;

	case RIGHT:
		head.col++;
		lastDir = LEFT;
		break;
	}

	// if snake is shorter than 1 segment, clear lastDir
	if (body.size() <= 1)
	{
		lastDir = NO_DIR;
	}

	
	// if move is not valid (!Traversable or nullptr), emit COLLIDE event, updateGrid and return
	if (!validMove(head.row, head.col))
	{

		// if we're extending, we need to add EXTEND back to eventObj to extend on next move
		if (extendingBool)
		{
			eventObj.addEvent("", EXTEND);
		}

			headDir = NO_DIR;

			eventObj.addEvent("", COLLIDE);
			updateGrid();
			return;
	}
	// else move is valid
	else
	{
		// emit MOVE event
		eventObj.addEvent("", MOVE);

		// invoke event code in space we're moving into
		gridPtr->getSpace(head.row, head.col)->checkForEvent();
	}


	// add head to snake
	body.push_front(head);
	
	// if extending, updategrid and return (skip removing tail)
	if (extendingBool)
	{
		updateGrid();
		return;
	}

	// restore last tail space
	gridPtr->restoreSpace(tail.row, tail.col);
	
	// remove tail
	body.pop_back();

	// update grid with new snake
	updateGrid();
}

/********************************************************************
**  void moveForward()
**	Description:  Moves snake forward 
*********************************************************************/
void Snake::moveForward()
{
	// if MOVE event does not exist, move snake forward
	if (eventObj.eventIndex(MOVE) == -1)
	{
		moveSnake(headDir);
	}
	// we'll get it next time, clear MOVE event
	else
	{
		eventObj.clearEvent(MOVE);
	}
}

/********************************************************************
**  bool validMove(int row, int col)
**	Description:  Checks if space is valid or not
*********************************************************************/
bool Snake::validMove(int row, int col)
{
	Space *ptr = gridPtr->getSpace(row, col);

	// if ptr is not nullptr return getTraversable
	if (ptr)
	{
		return ptr->getTraversable();
	}
	// if ptr is nullptr, return false
	else
	{
		return false;
	}
}

