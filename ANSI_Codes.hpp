


#ifndef ANSI_CODES_HPP
#define ANSI_CODES_HPP

#include <string>

using std::string;
using std::to_string;

enum ANSIColor { BLACK, RED, GREEN, YELLOW, BLUE, MAGENTA, CYAN, WHITE, DEFAULT };  // available color codes

// constants

const int GRID_TOP = 2;									// top of grid (play area)

const string CURSOR_HOME = "\033[23;1H";				// home cursor

const string CLEAR_LINE = "\033[2K";					// clears entire line that cursor is on
const string CLEAR_SCREEN = "\033[2J";					// clears entire screen
const string CLEAR_COLOR = "\033[0m";					// clears color setting

const string SET_BOLD = "\033[1m";						// sets text to bold

const string SCORE_POSITION = "\033[1;1H";				
const string LIVES_POSITION = "\033[1;35H";
const string TIME_POSITION = "\033[1;65H";


string ANSI_ColorToCodeForeGround(ANSIColor color);		// changes foreground color - takes ANSIColor color and returns code string 
string ANSI_ColorToCodeBackGround(ANSIColor color);		// changes background color - takes ANSIColor color and returns code string

ANSIColor ANSI_StringToColor(string str);				// converts string to ANSIColor

string ANSI_GridPositionToCode(int row, int col);		// returns code for given row and col on grid
string ANSI_AbsolutePositionToCode(int row, int col);	// returns code for given row and col on screen (absolute)
#endif
