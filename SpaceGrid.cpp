/**********************************************************************
**	SpaceRow.cpp
**	Author: Matt Britt
**	Date: 11/30/2017
**	Description:   SpaceRow.cpp is the implementation file for the SpaceRow class.
**				The SpaceRow class represents a row of spaces in the main
**				game area.
*********************************************************************/

#include "SpaceGrid.hpp"


/********************************************************************
**  SpaceGrid()
**	Description: Constructor, initializes SpaceGrid object  
*********************************************************************/
SpaceGrid::SpaceGrid()
{

}

/********************************************************************
**  ~SpaceGrid()
**	Description: Destructor, cleans up memory
*********************************************************************/
SpaceGrid::~SpaceGrid()
{
	// iterate backwards through grid and free memory
	for (int r = MAX_ROWS; r >= 0; r--)
	{
		for (int c = MAX_COLS; c >= 0; c--)
		{
			removeSpace(r, c);
		}
	}
}

/********************************************************************
**  Space* getSpace(int index)
**	Description: Getter, return Space* at given index
*********************************************************************/
Space* SpaceGrid::getSpace(int row, int col)
{
	// if valid index
	if (col >=0 && col < MAX_COLS && row >=0 && row < MAX_ROWS)
	{
		// iterate through row until col is found
		Space *ptr = firstSpace;

		if (!ptr)
		{
			return nullptr;
		}

		for (int i = 0; i < col; i++)
		{
		
				// check if there's a valid ptr to next space
				if (ptr->getSpace(RIGHT) == nullptr)
				{
					return nullptr;
				}

				ptr = ptr->getSpace(RIGHT);
			
		}

		// iterate through col until index is found
		for (int i = 0; i < row; i++)
		{
		
				// check if there's a valid ptr to next space
				if (ptr->getSpace(DOWN) == nullptr)
				{
					return nullptr;
				}

				ptr = ptr->getSpace(DOWN);
			
		}

		return ptr;
	}
	// else, invalid index
	else
	{
		return nullptr;
	}
}

/********************************************************************
**  Space* operator()(int row, int col)
**	Description: Getter, return Space* at given row and col (basically getSpace)
*********************************************************************/
Space* SpaceGrid::operator()(int row, int col)
{
	return getSpace(row, col);
}

/********************************************************************
**  int getRows()
**	Description: Getter, returns rows
*********************************************************************/
int SpaceGrid::getRows()
{
	return MAX_ROWS;
}

/********************************************************************
**  int getCols()
**	Description: Getter, returns cols
*********************************************************************/
int SpaceGrid::getCols()
{
	return MAX_COLS;
}

/********************************************************************
**  bool loadGrid(string fileName)
**	Description: Loads grid from filename
*********************************************************************/
bool SpaceGrid::loadGrid(string fileName)
{
	// open input file (fileName)
	ifstream inFile(fileName);

	// if file opens, parse it
	if (inFile)
	{
		string line;
		ParseLabels label = NONE;
		int lineNum = 0;

		// parse each line
		while (getline(inFile, line))
		{
			if (label == ERROR)
			{
				cout << "Error loading " << fileName << " Line: " << to_string(lineNum);
				
				// on error, close file and load default grid
				inFile.close();
				loadDefaultGrid();
			}

			// parse line
			label = parseGrid(line, label);
			lineNum++;
		}

		// close file
		inFile.close();
	}
	// else file didn't open
	else
	{
		loadDefaultGrid();
		return false;
	}
}

/********************************************************************
**  void loadDefaultGrid()
**	Description: Loads default grid (for loadGrid() failure
*********************************************************************/
void SpaceGrid::loadDefaultGrid()
{	
	vector<string> defaultLevel{
		"[LEVEL]",
			"Level 0=LEVEL_NAME",
			"An empty introductory level to the snake game experience=LEVEL_DESCRIPTION",
			"[CODES]",
			"-=WALL",
			"|=WALL",
			" =EMPTY",
			"s=SNAKE",
			"[COLORS]",
			" =RED",
			"[START]",
			"--------------------------------------------------------------------------------",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"|                                                                              |",
			"--------------------------------------------------------------------------------",
			"[END]"
	};
	


	ParseLabels label = NONE;


	for (auto line : defaultLevel) {

		if (label == END)
		{
			break;
		}
		label = parseGrid(line, label);
		
	}
}

/********************************************************************
**  bool addSpace(int row, int col, Space* newPtr)
**	Description: Adds new space at row, col; returns true on success, false on fail
*********************************************************************/
bool SpaceGrid::addSpace(int row, int col, Space *newPtr)
{
	// check if row and col are valid
	if (row < 0 || row >= MAX_ROWS || col < 0 || col >= MAX_COLS)
	{
		return false;
	}

	// check if space is already filled
	Space *ptr = getSpace(row, col);

	// if space is filled, remove current space from mem before adding new one
	if (ptr != nullptr)
	{
		// update direction pointers
		newPtr->setSpace(UP, ptr->getSpace(UP));
		newPtr->setSpace(DOWN, ptr->getSpace(DOWN));
		newPtr->setSpace(LEFT, ptr->getSpace(LEFT));
		newPtr->setSpace(RIGHT, ptr->getSpace(RIGHT));
		
		// remove space from mem
		removeSpace(row, col);
	}
	
	// set Space
	ptr = newPtr;

	// update direction links
	updateDirections(row, col, ptr);

	return true;
}

/********************************************************************
**  void updateDirections(int row, int col, Space *ptr)
**	Description: Updates direction links for spaces
*********************************************************************/
void SpaceGrid::updateDirections(int row, int col, Space *newPtr)
{
	Space *ptr;

	// update firstSpace if needed
	if (row == 0 && col == 0)
	{
		firstSpace = newPtr;
	}

	// update space to left
	if (col > 0)
	{
		ptr = getSpace(row, col - 1);
		newPtr->setSpace(LEFT, ptr);
		
		if (ptr)
		{
			ptr->setSpace(RIGHT, newPtr);
		}
	}

	// update space to right
	if (col < MAX_COLS - 1)
	{
		ptr = getSpace(row, col + 1);
		newPtr->setSpace(RIGHT, ptr);
		
		if (ptr)		// keep from accessing nullptr
		{
			ptr->setSpace(LEFT, newPtr);
		}
	}

	// update space above
	if (row > 0)
	{
		ptr = getSpace(row - 1, col);
		newPtr->setSpace(UP, ptr);

		if (ptr)
		{
			ptr->setSpace(DOWN, newPtr);
		}
	}
	
	// update space below
	if (row < MAX_ROWS - 1)
	{
		ptr = getSpace(row + 1, col);
		newPtr->setSpace(DOWN, ptr);
		
		if (ptr)
		{
			ptr->setSpace(UP, newPtr);
		}
	}
}


/********************************************************************
**  void removeSpace(int row, int col)
**	Description: Removes space from memory
** WARNING: Does not update any pointers
*********************************************************************/
void SpaceGrid::removeSpace(int row, int col)
{
	delete getSpace(row, col);
}


/********************************************************************
**  vector<string>& getUpdate()
**	Description: Returns a vector of strings to update screen
*********************************************************************/
void SpaceGrid::getUpdate(vector<string> &updateVector)
{
	Space *ptr;

	// checks for foreColor and backColor
	ANSIColor foreColor = DEFAULT;
	ANSIColor backColor = DEFAULT;

	bool firstColor = true;


	// iterate through grid rows and cols and add updated strings to updateVector
	// if the space has updated since last read
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			ptr = getSpace(row, col);


			// if space at ptr needs update
			if (ptr && ptr->hasUpdated())
			{

				// push ANSI control code strings to position
				updateVector.push_back(ANSI_GridPositionToCode(row, col));

				// if it's the first color, read the colors
				if (firstColor)
				{
					firstColor = false;
					updateVector.push_back(ptr->read());
				}
				// if it's not the first color, read but ignore colors already set
				else
				{
					updateVector.push_back(ptr->read(foreColor, backColor));
				}

				// save colors to compare to next updating space
				foreColor = ptr->getColor();
				backColor = ptr->getBackColor();
			}
		}
	}
}


/********************************************************************
**  ParseLabels parseGrid(string line, parseLabel label)
**	Description: Parses one line into the grid based on label.
**				Returns label if encountered to setup next parse.
*********************************************************************/
ParseLabels SpaceGrid::parseGrid(string line, ParseLabels label)
{
	// TODO: implement background colors
	// TODO: implement dual symbol system for multiple colors / types of same character/symbol

	// check for label at current line
	if (line[0] == '[')
	{
		if (line == "[LEVEL]")
		{
			return LEVEL;
		}
		else if (line == "[CODES]")
		{
			return CODES;
		}
		else if (line == "[COLORS]")
		{
			return COLORS;
		}
		else if (line == "[BACK_COLORS]")
		{
			return BACK_COLORS;
		}
		else if (line == "[START]")
		{
			return START;
		}
		else if (line == "[END]")
		{
			return END;
		}
		// unknown label
		return ERROR;
	}

	// if not label, parse everything but the layout
	if (label != START)
	{
		int equalsIndex = line.find_last_of("=");
		string leftSide = line.substr(0, equalsIndex);
		string rightSide = line.substr(equalsIndex + 1);

		// check for LEVEL properties
		if (label == LEVEL)
		{
			if (rightSide == "LEVEL_NAME")
			{
				levelInfo.levelName = leftSide;
				return label;
			}
			else if (rightSide == "LEVEL_DESCRIPTION")
			{
				levelInfo.levelDescription = leftSide;
				return label;
			}
			else if (rightSide == "TIME")
			{
				try
				{
					int time = stoi(leftSide);
					levelInfo.time = time;
					return label;
				}
				// failed to convert integer
				catch (...)
				{
					return ERROR;
				}
			}
			else if (rightSide == "LIVES")
			{
				try
				{
					int lives = stoi(leftSide);
					levelInfo.lives = lives;
					return label;
				}
				// failed to convert integer
				catch (...)
				{
					return ERROR;
				}
			}
			else if (rightSide == "NEXT_LEVEL")
			{
				levelInfo.nextLevel = leftSide;
				return label;
			}
			else
			{
				return ERROR;
			}
		}

		// check for CODES properties
		else if (label == CODES)
		{
			ELEMENT tempElement;
			tempElement.character = leftSide[0];

			// WALL code
			if (rightSide == "WALL")
			{
				tempElement.type = WALL;
				elemVec.push_back(tempElement);
				return label;
			}

			// EMPTY code
			else if (rightSide == "EMPTY")
			{
				tempElement.type = EMPTY;
				elemVec.push_back(tempElement);
				return label;
			}

			// SNAKE code
			else if (rightSide == "SNAKE")
			{
				tempElement.type = SNAKE;

				elemVec.push_back(tempElement);
				return label;
			}
			// unknown element type
			return ERROR;
		}

		// check for colors properties
		else if (label == COLORS)
		{
			ANSIColor color = ANSI_StringToColor(rightSide);

			// find element and set color
			for (auto &element : elemVec)
			{
				if (element.character == leftSide[0])
				{
					element.color = color;
					return label;
				}
			}
		}

		// check for background colors
		else if (label == BACK_COLORS)
		{
			ANSIColor bcolor = ANSI_StringToColor(rightSide);

			// find element and set color
			for (auto &element : elemVec)
			{
				if (element.character == leftSide[0])
				{
					element.backColor = bcolor;
					return label;
				}
			}

		}

		// element not found by character
		return ERROR;
	}
	

	// else label == START and we need to parse a line of the level layout
	else
	{
		if (line.length() > MAX_COLS)
		{
			return ERROR;
		}

		char incomingChar;
		// iterate through line populating the row in the grid
		for (int i = 0; i < line.length(); i++)
		{
			// get next char in line
			incomingChar = line[i];

			for (auto element : elemVec)
			{
				if (element.character == incomingChar)
				{
					// create appropriate space type
					Space *ptr = nullptr;

					switch (element.type)
					{
					case SNAKE:
						levelInfo.snakeRow = nextRow;
						levelInfo.snakeCol = i;
					case EMPTY:
						ptr = new EmptySpace(element.character, element.color, element.backColor);
						//ptr = new TestSpace(element.character, element.color);
						break;
					
					case WALL:
						ptr = new WallSpace(element.character, element.color, element.backColor);
						//ptr = new TestSpace(element.character, element.color);
						break;
					}
	
					// add space to grid
					this->addSpace(nextRow, i, ptr);
				}
				// TODO: ignore if character not found -- risky
			}

		}
		nextRow++;
		return label;
	}
}

/********************************************************************
**  LevelInfo getLevelInfo()
**	Description: Getter, returns levelInfo
*********************************************************************/
LevelInfo SpaceGrid::getLevelInfo()
{
	return levelInfo;
}

