// Author: Seth George

#ifndef PARSING_H
#define PARSING_H

#include "life_structs.h"
#include "life_parsing.h"

using namespace std;


Info* parseInput(istream &inf);

/********************************* Parsing Initializers *********************************/
// checks validity of the initalizer 'Name' then returns parsed value for name if valid, exits if invalid
string parseName(istream &inf, bool hasName);

// checks validity of the initalizer 'Terrain' then creates a GridDimension of parsed values, exits if invalid
GridDimension parseTerrain(istream &inf, bool hasTerrain);

// checks validity of the initializer 'Window' then creates a GridDimension of parsed values, exits if invalid
GridDimension parseWindow(istream &inf, bool hasWindow);

/********************************* Parsing Helper methods *********************************/
// takes in a file pointer and returns a string of all the chars up to excluding the semicolon, removing comments and white space
string parseUntilSemicolon(istream &inf);

// Looks for the next non whitespace non commented character and compares to given character
void checkCharacter(istream &inf, char check);

// takes in a file pointer and parses until would be end of given string and compares to see if they are the same, exits if not
void checkString(istream &inf, string str);

// Takes in a file pointer then checks and advances to skip the comment until a '\n' char is found if needed
void skipComment(istream &inf);

// Takes in a file pointer and advances is if the next char is white space, exiting program on failure.
void skipWhiteSpace(istream &inf);

// Check for if char is white space
bool isWhiteSpace(char c);

// Takes in a string in the format low..high, and returns a struct containing the low and high value 
Range parseRange(string strRange);

// Takes in a string in the format (r, g, b) and returns a Triple class of those values
Triple parseTriple(string strTriple);

// Takes in a string in the format (x,y) and returns a Coord struct of those values
Coord parseCoord(string strCoord);


#endif