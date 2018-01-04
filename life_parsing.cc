// Author: Seth George

#include "parsing.h"
#include "life_parsing.h"
#include "life_structs.h"

using namespace std;

/*
*	Important note: This file implements functions in life_parsing.h and some for life_structs.h
*/

/********************************* LifeInfo Class Implementation *********************************/
// print out the test based version of the output
void LifeInfo::printTextual() {
	cout << "Life = {" << endl;
	
	cout << "\tName = \"" << name << "\"" << endl;
	
	cout << "\tTerrain = {" << endl;
	cout << "\t\tXrange = " << terrain.x.low << ".."<< terrain.x.high << ";" << endl;
	cout << "\t\tYrange = " << terrain.y.low << ".."<< terrain.y.high << ";" << endl;
	cout << "\t};" << endl;
	
	cout << "\tWindow = {" << endl;
	cout << "\t\tXrange = " << window.x.low << ".."<< window.x.high << ";" << endl;
	cout << "\t\tYrange = " << window.y.low << ".."<< window.y.high << ";" << endl;
	cout << "\t};" << endl;
	
	cout << "\tChars = {" << endl;
	cout << "\t\tAlive = " << int(chars.alive) << " #ASCII for " << chars.alive << endl;
	cout << "\t\tDead = " << int(chars.dead) << " #ASCII for " << chars.dead << endl;
	cout << "\t};" << endl;
	
	cout << "\tColors = {" << endl;
	cout << "\t\tAlive = (" << colors.alive.red << "," << colors.alive.green << "," << colors.alive.blue << ");" << endl;
	cout << "\t\tDead = (" << colors.dead.red << "," << colors.dead.green << "," << colors.dead.blue << ");" << endl;
	cout << "\t};" << endl;
	
	cout << "\tInitial = {" << endl;
	cout << "\t\t Alive = " << flush;
	
	bool isFirst = true;
	for(int i = terrain.y.high; i >= terrain.y.low; i--) { 
		for(int j = terrain.x.low; j <= terrain.x.high; j++) { // print out everything in a line
			if(grid.getCell(j, i) == chars.alive) {
				if(isFirst) {
					isFirst = false; // no comma
				} else {
					cout << ","<< flush;
				}
				cout << "(" << j << "," << i << ")" << flush;
			}
		}
	}
	cout << ";" << endl;
	
	cout << "\t};" << endl;
	cout << "};" << endl;
}


/********************************* Parsing Initializers *********************************/
// Takes in a file pointer and returns the passive data collection, LifeStaus, of all the parsed data.
LifeInfo* parseLifeInput(istream &inf) {
	if(!inf.good()) {
		cerr << "Error: given file pointer to parseLifeInput is null" << endl;
		exit(EXIT_FAILURE);
	}

	LifeInfo *lifeInfo = new LifeInfo(); // info class to be populated
	
	bool hasName = false;
	bool hasTerrain = false;
	bool hasWindow = false;
	bool hasChars = false;
	bool hasColors = false;
	bool hasInitial = false;
	
	checkString(inf, "Life");
	checkCharacter(inf, '=');
	checkCharacter(inf, '{');
	
	char c; // char used to parse through input file
	// While not all the initializers have been found
	while(!(hasName && hasTerrain && hasChars && hasColors && hasInitial)) {
		c = inf.get();
		if(inf.eof()) { // if end of file was reached
			cerr << "Error: found end of file while parsing initializers, which is before was expected" << endl;
			exit(EXIT_FAILURE);
		}
		
		switch(c) {
			case('N'): // begin check for Name
				inf.unget();
				lifeInfo->name = parseName(inf, hasName);
				hasName = true;
				break;
				
			case('T'): // begin check for Terrain
				inf.unget();
				lifeInfo->terrain = parseTerrain(inf, hasTerrain);
				hasTerrain = true;
				break;
				
			case('W'): // begin check for Window
				inf.unget();
				lifeInfo->window = parseWindow(inf, hasWindow);
				hasWindow = true;
				break;

			case('C'): // begin check for Chars and Colors
				c = inf.get();
				if(inf.eof()) { // if end of file was reached unexpectedly
					cerr << "Error: found end of file before was expected" << endl;
					exit(EXIT_FAILURE);
				}
				
				inf.unget();
				if(c == 'h') {
					lifeInfo->chars = parseChars(inf, hasChars);
					hasChars = true;
					
				} else if(c == 'o') {
					lifeInfo->colors = parseColors(inf, hasColors);
					hasColors = true;
					
				} else {
					cerr << "Error: format error due to unexpected character " << c << " found during parsing for initializers." << endl;
					exit(EXIT_FAILURE);
				}
				break;
				
			case('I'): // begin check for Initial
				inf.unget();
				lifeInfo->initial = parseInitial(inf, hasInitial);
				hasInitial = true;
				break;
				
			default:
				if(!isWhiteSpace(c)) {
					cerr << "Error: format error due to unexpected character " << c << " found during parsing for initializers." << endl;
					exit(EXIT_FAILURE);
				}
				
				skipComment(inf);
				break;
		}
		
		if(!hasWindow) { // window will be the same as terrain, even if terrain changes
			lifeInfo->window.x = lifeInfo->terrain.x;
			lifeInfo->window.y = lifeInfo->terrain.y;
		}
	}
	
	return lifeInfo;
}

//checks validity of the initializer 'Chars' then creates a struct, Chars, of parsed values, exits if invalid
Chars parseChars(istream &inf, bool hasChars) {
	checkString(inf, "hars");
	
	if(hasChars) {
		cerr << "Error: duplicate initializer for Chars found" << endl;
		exit(EXIT_FAILURE);
	}
	
	Chars chars;
	
	checkCharacter(inf, '=');
	checkCharacter(inf, '{');
	
	// Parse ascii value for alive char
	checkString(inf, "Alive");
	checkCharacter(inf, '=');
	string strAlive = parseUntilSemicolon(inf);
	int aliveValue;
	istringstream(strAlive) >> aliveValue;
	char alive = aliveValue;
	chars.alive = alive;
	
	// Parse ascii value for dead char
	checkString(inf, "Dead");
	checkCharacter(inf, '=');
	string strDead = parseUntilSemicolon(inf);
	int deadValue;
	istringstream(strDead) >> deadValue;
	char dead = deadValue;
	chars.dead = dead;
	
	checkCharacter(inf, '}');
	checkCharacter(inf, ';');
	
	return chars;
}

//checks validity of the initializer 'Colors' then creates a struct, Colors, of parsed values, exits if invalid
Colors parseColors(istream &inf, bool hasColors) {
	checkString(inf, "olors");
	
	if(hasColors) {
		cerr << "Error: duplicate initializer for Colors found" << endl;
		exit(EXIT_FAILURE);
	}
	
	checkCharacter(inf, '=');
	checkCharacter(inf, '{');
	
	Colors colors;
	
	checkString(inf, "Alive");
	checkCharacter(inf, '=');
	
	string strAlive = parseUntilSemicolon(inf);
	colors.alive = parseTriple(strAlive);
	
	checkString(inf, "Dead");
	checkCharacter(inf, '=');
	
	string strDead = parseUntilSemicolon(inf);
	colors.dead = parseTriple(strDead);
	
	checkCharacter(inf, '}');
	checkCharacter(inf, ';');
	
	return colors;
}

// checks validity of the initializer 'Initial' then calls setInital if valid format, exits program if invalid format
vector<Coord> parseInitial(istream &inf, bool hasInitial) {
	checkString(inf, "Initial");
	
	if(hasInitial) {
		cerr << "Error: duplicate initializer for Initial found" << endl;
		exit(EXIT_FAILURE);
	}
	
	checkCharacter(inf, '=');
	checkCharacter(inf, '{');
	checkString(inf, "Alive");
	checkCharacter(inf, '=');
	
	string strCoords = parseUntilSemicolon(inf);
	
	vector<Coord> coords; // list of Coords
	if(strCoords.length() == 0) { // make sure there is at least something to try to put in coords
		return coords;
	}
	
	int leftPar; // will be index of left parentheses of each range in the strCoord string
	int rightPar = -2; // index of the right parentheses
	do { // (x,y),(x,y), ... (x,y)
		leftPar = rightPar + 2; // first should be zero
		if(strCoords[leftPar] != '(') {
			cerr << "Error: Beginning '(' of Coord not found, instead found" << strCoords[leftPar] << endl;
			exit(EXIT_FAILURE);
		}
		
		rightPar = strCoords.find(")", leftPar); // look for the ending parenthesis
		
		string strCoord = strCoords.substr(leftPar, (rightPar+1) - leftPar);
		Coord coord = parseCoord(strCoord);
		coords.push_back(coord);
		
		if(strCoords[rightPar+1] != ',') {
			if(rightPar != strCoords.length()-1) {
				cerr << "Error: Delimiting comma not found between Coords not found, instead found" << strCoords[rightPar+1] << endl;
			}
		}
		
	} while(rightPar != strCoords.length()-1);
	
	checkCharacter(inf, '}');
	checkCharacter(inf, ';');
	
	return coords;
}


/********************************* Printing Functions *********************************/
// Prints the help screen for the -h flag
void printHelpGui() {
	cout << "\nThe program reads a single input file either from a pathname passed as an argument," << endl;
	cout << "or from standard input if no file names are given as arguments. The program determines and" << endl;
	cout << "displays the state of each cell at generation n, as a grid and using the colors specified for" << endl;
	cout << "each state. The window title should be the Name specified in the input file." << endl;
	cout << "The program should accept the following command{line switches.\n" << endl;
	cout << "\t-g n Specify the desired generation number. If omitted, the default should be n = 0." << endl;
	cout << "\t-h Display a help screen that describes the program, and terminate before starting the GUI." << endl;
	cout << "\t-s n Specify the size, in pixels, of each square in the grid (default should be 10)." << endl;
	cout << "\t -c Display a dialog box that controls the simulation" << endl;
	cout << "\t\tGrid lines should be omitted when the size is less than 4." << endl;
	cout << "\t-tx l..h Set the x range of the terrain; overrides values specified in the input file." << endl;
	cout << "\t-ty l..h Set the y range of the terrain; overrides values specified in the input file." << endl;
	cout << "\t-wx l..h Set the (initial) x range of the output window (default is terrain x range)." << endl;
	cout << "\t-wy l..h Set the (initial) y range of the output window (default is terrain y range)." << endl;
}

// Prints the help screen for the -h flag
void printHelpLife() {
	cout << "\nThis program reads a single input file, either from a pathname passed as an argument," << endl;
	cout << "or from standard input if no file names are given as arguments. The input file specifies" << endl;
	cout << "the dimension of the terrain and the initial configuration for generation 0. The program" << endl;
	cout << "determines and displays the state of each cell at generation n." << endl;
	cout << "The program accepts the following command line switches.\n" << endl;
	cout << "\t-h Display a help screen that describes the program." << endl;
	cout << "\t-v Output should be visual: an ASCII display of the terrain with appropriate characters for the" << endl;
	cout << "\t\tdead and alive cells. The dead character is ~ and the alive character is @." << endl;
	cout << "\t-f Outputs a file format in a readable code-like format." << endl;
	cout << "\t-g n Specify the desired generation number. If omitted, the default should be n = 0" << endl;
	cout << "\t-tx l..h Set the x range of the terrain; overrides values specified in the input file." << endl;
	cout << "\t-ty l..h Set the y range of the terrain; overrides values specified in the input file." << endl;
	cout << "\t-wx l..h Set the x range of the output window; otherwise this defaults to the x range of the terrain." << endl;
	cout << "\t-wy l..h Set the y range of the output window; otherwise this defaults to the y range of the terrain." << endl;
	cout << "Note that ranges l..h specify that the value v is between l and h, inclusive (i.e., l <= v <= h).\n" << endl;
}