

#include "ANSI_Codes.hpp"


/********************************************************************
**  string ANSI_ColorToCodeForeGround(ANSIColor color)
**	Description: Changes foreground color 
**				Takes in color and returns code string for given color
*********************************************************************/
string ANSI_ColorToCodeForeGround(ANSIColor color)
{
	string retString = "\033[";  // escape sequence

	switch (color)
	{
	case BLACK:
		retString += to_string(30);
		break;
	case RED:
		retString += to_string(31);
		break;
	case GREEN:
		retString += to_string(32);
		break;
	case YELLOW:
		retString += to_string(33);
		break;
	case BLUE:
		retString += to_string(34);
		break;
	case MAGENTA:
		retString += to_string(35);
		break;
	case CYAN:
		retString += to_string(36);
		break;
	case WHITE:
		retString += to_string(37);
		break;
		// default
	case DEFAULT:
	default:
		retString += to_string(39);
	}

	retString += "m";				// final byte of control code
	return retString;
}

/********************************************************************
**  string ANSI_ColorToCodeBackGround(ANSIColor color)
**	Description: Changes background color
**				Takes in color and returns code string for given color
*********************************************************************/
string ANSI_ColorToCodeBackGround(ANSIColor color)
{
	string retString = "\033[";  // escape sequence

	switch (color)
	{
	case BLACK:
		retString += to_string(40);
		break;
	case RED:
		retString += to_string(41);
		break;
	case GREEN:
		retString += to_string(42);
		break;
	case YELLOW:
		retString += to_string(43);
		break;
	case BLUE:
		retString += to_string(44);
		break;
	case MAGENTA:
		retString += to_string(45);
		break;
	case CYAN:
		retString += to_string(46);
		break;
	case WHITE:
		retString += to_string(47);
		break;
		// default
	case DEFAULT:
	default:
		retString += to_string(49);
	}

	retString += "m";				// final byte of control code
	return retString;
}

/*********************************************************************
**	ANSIColor StringToColor(string str)
**	Description: Converts string str to ANSIColor 
*********************************************************************/
ANSIColor ANSI_StringToColor(string str)
{
	if (str == "RED")
	{
		return RED;
	}
	else if (str == "BLUE")
	{
		return BLUE;
	}
	else if (str == "BLACK")
	{
		return BLACK;
	}
	else if (str == "GREEN")
	{
		return GREEN;
	}
	else if (str == "YELLOW")
	{
		return YELLOW;
	}
	else if (str == "MAGENTA")
	{
		return MAGENTA;
	}
	else if (str == "CYAN")
	{
		return CYAN;
	}
	else if (str == "WHITE")
	{
		return WHITE;
	}
	// default
	else
	{
		return DEFAULT;
	}
}

/*********************************************************************
**	string ANSI_GridPositionToCode(int row, int col)
**	Description: returns control code string for given row and col on grid
*********************************************************************/
string ANSI_GridPositionToCode(int row, int col)
{
	return ANSI_AbsolutePositionToCode(row + GRID_TOP, col + 1);
}

/*********************************************************************
**	string ANSI_AbsolutePositionToCode(int row, int col)
**	Description: returns code string for given row and col on screen (absolute)
*********************************************************************/
string ANSI_AbsolutePositionToCode(int row, int col)
{
	return "\033[" + to_string(row) + ";" + to_string(col) + "H";
}


