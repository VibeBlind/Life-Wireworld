// Author: Seth George

#ifndef LIFE_PARSING_H
#define LIFE_PARSING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>

#include "parsing.h"
#include "life_structs.h"

using namespace std;


/********************************* Parsing Initializers *********************************/
// Takes in a file pointer and returns the passive data collection, LifeStaus, of all the parsed data.
LifeInfo* parseLifeInput(istream &inf);

// checks validity of the initializer 'Chars' then creates a struct of parsed values, exits if invalid
Chars parseChars(istream &inf, bool hasChars);

// checks validity of the initializer 'Colors' then creates a struct of parsed values, exits if invalid
Colors parseColors(istream &inf, bool hasColors);

// checks validity of the initializer 'Initial' then calls setInital if valid format, exits program if invalid format
vector<Coord> parseInitial(istream &inf, bool hasInitial);


/********************************* Print Functions *********************************/
// Prints the help screen for life for the -h flag
void printHelpLife();

// Prints the help screen for life_gui for the -h flag
void printHelpGui();


#endif