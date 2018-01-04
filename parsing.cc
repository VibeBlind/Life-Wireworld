// Author: Seth Georgecle

#include "life_structs.h"
#include "life_parsing.h"
#include "parsing.h"

using namespace std;


Info* parseInput(istream &inf){
	skipComment(inf);
	
	char c = inf.get(); // char used to see with file type we're parsing
	if(inf.eof()) { // if end of file was reached
		cerr << "Error: found end of file while parsing initializers, which is before was expected" << endl;
		exit(EXIT_FAILURE);
	}
	inf.unget();
	switch(c) {
		case('L'): // Life
			return parseLifeInput(inf);
			break;
		case('W'): // WireWorld
			//return parseWireInput(inf);
			break;
			
		case('E'): // Elementary
			//return parseEleInput(inf);
			break;
			
		default:
			cerr << "Error: format error due to invalid unexpected character " << c << " found determining file type." << endl;
			cerr << "\tThis means there is either a formatting error or an invalid file type. Please correct the issue and try again." << endl;
			exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

/********************************* Parsing Initializers *********************************/
// checks validity of the initializer 'Name' then returns parsed value for name if valid, exits if invalid
string parseName(istream &inf, bool hasName) {
	checkString(inf, "Name");
	
	if(hasName) {
		cerr << "Error: duplicate initializer for Name found" << endl;
		exit(EXIT_FAILURE);
	}
	
	checkCharacter(inf, '=');
	checkCharacter(inf, '"');
	
	string str = "";
	char c = 0;
	while(c != '"') {
		c = inf.get();
		if(inf.eof()) { // if end of file was reached unexpectedly
			cerr << "Error: found end of file before was expected" << endl;
			exit(EXIT_FAILURE);
		}
		
		if(c == '"') {
			break;
		}
		
		str += c;
	}
	
	checkCharacter(inf, ';');
	
	return str;
}

//checks validity of the initializer 'Terrain' then creates a GridDimension of parsed values, exits if invalid
GridDimension parseTerrain(istream &inf, bool hasTerrain) {
	checkString(inf, "Terrain");
	
	if(hasTerrain) {
		cerr << "Error: duplicate initializer for Terrain found" << endl;
		exit(EXIT_FAILURE);
	}
	
	checkCharacter(inf, '=');
	checkCharacter(inf, '{');
	
	GridDimension terrain; // this is just a struct of 2 ranges
	
	checkString(inf, "Xrange");
	checkCharacter(inf, '=');
	string Xrange = parseUntilSemicolon(inf); // should return a formatted comment/whitespace free range to parse
	terrain.x = parseRange(Xrange); // parses the data and put it into terrain
	
	checkString(inf, "Yrange");
	checkCharacter(inf, '=');
	string Yrange = parseUntilSemicolon(inf);
	terrain.y = parseRange(Yrange);
	
	checkCharacter(inf, '}');
	checkCharacter(inf, ';');
	
	return terrain;
}

//checks validity of the initializer 'Window' then creates a GridDimension of parsed values, exits if invalid
GridDimension parseWindow(istream &inf, bool hasWindow) {
	checkString(inf, "window");
	
	if(hasWindow) {
		cerr << "Error: duplicate initializer for Window found" << endl;
		exit(EXIT_FAILURE);
	}
	
	checkCharacter(inf, '=');
	checkCharacter(inf, '{');
	
	GridDimension window; // this is just a struct of 2 ranges, which are a struct of 2 ints (ewww)
	
	checkString(inf, "Xrange");
	checkCharacter(inf, '=');
	string Xrange = parseUntilSemicolon(inf); // should return a comment/whitespace free range to parse
	window.x = parseRange(Xrange); // parses the data and put it into window
	
	checkString(inf, "Yrange");
	checkCharacter(inf, '=');
	string Yrange = parseUntilSemicolon(inf);
	window.y = parseRange(Yrange);
	
	checkCharacter(inf, '}');
	checkCharacter(inf, ';');
	
	return window;
}


/********************************* Parsing Helper methods *********************************/
// takes in a file pointer and returns a string of all the chars up to excluding the semicolon, removing comments and white space
string parseUntilSemicolon(istream &inf) {
	skipComment(inf);
	
	string str = "";
	char c = 0;
	while(c != ';') {
		c = inf.get();
		if(inf.eof()) { // if end of file was reached unexpectedly
			cerr << "Error: found end of file before was expected" << endl;
			exit(EXIT_FAILURE);
		}
		
		if(c == ';') {
			break;
		}
		
		skipComment(inf);
		
		str += c;
	}
	
	return str;
}

// Looks for the next non whitespace non commented character and compares to given character
void checkCharacter(istream &inf, char check) {
	skipComment(inf);
	
	char c = inf.get();
	if(inf.eof()) { // if end of file was reached unexpectedly
		cerr << "Error: found end of file before was expected" << endl;
		exit(EXIT_FAILURE);
	}
	
	if(c != check){
		cerr << "Error: found unexpected character " << c << " when parsing Life values" << endl;
		exit(EXIT_FAILURE);
	}
}

// takes in a file pointer and parses until would be end of given string and compares to see if they are the same, exits if not
void checkString(istream &inf, string str) {
	skipComment(inf);
	
	string check = "";
	char c;	
	for(unsigned int i = 0; i < str.length(); i++) {
		c = inf.get();
		if(inf.eof()) { // if end of file was reached unexpectedly
			cerr << "Error: found end of file before was expected" << endl;
			exit(EXIT_FAILURE);
		}
		
		check += c;
	}
	
	if(check.compare(str)) {
		cerr << "Error: expected: " << str << " but was: " << check << endl;
		exit(EXIT_FAILURE);
	}
}

// Takes in a file pointer then checks and advances to skip the comment until a '\n' char is found if needed
void skipComment(istream &inf) {
	if(!inf.good()) {
		cerr << "Error: given file pointer to skipComment is null" << endl;
		exit(EXIT_FAILURE);
	}
	skipWhiteSpace(inf);
	char c = inf.get();
	while(c == '#') { // gets all subsequent comments, won't do anything if there are no comments
		if(inf.eof()) { // if end of file was reached unexpectedly
			cerr << "Error: found end of file before was expected" << endl;
			exit(EXIT_FAILURE);
		}
		while((c = inf.get())) {
			if(c == '\n') {
				break;
			}		
		}
		skipWhiteSpace(inf);
		if(inf.eof()) { // if end of file was reached unexpectedly
			cerr << "Error: found end of file before was expected" << endl;
			exit(EXIT_FAILURE);
		}

		c = inf.get();
	}
	
	inf.unget();
	return;
}

// Takes in a file pointer and advances is if the next char is white space, exiting program on failure.
void skipWhiteSpace(istream &inf) {
	if(!inf.good()) {
		cerr << "Error: given file pointer to skipWhiteSpace is null" << endl;
		exit(EXIT_FAILURE);
	}
	
	char c = inf.get();
	while(isWhiteSpace(c)) {
		if(inf.eof()) {
			cerr << "Error: found end of file before was expected" << endl;
			exit(EXIT_FAILURE);
		}
		c = inf.get();
	}
	
	inf.unget(); // go back to the first not white space character
	return;
}

// Check for if char is white space
bool isWhiteSpace(char c) {
	return (c == ' ')||(c == '\t')||(c == '\n')||(c == '\r');
}

// Takes in a string in the format low..high, and returns a struct containing the low and high value (overhead... I know.. sorry)
Range parseRange(string strRange) {
	int numDots = 0;	
	for(unsigned int i = 0; i < strRange.length(); i++) { // check that they are numbers or periods
		if(!((strRange[i] >= '0' && strRange[i] <= '9') || strRange[i] == '-' || strRange[i] == '.' || isWhiteSpace(strRange[i]))) {
			cerr << "Error: argument for range contains invalid character: " << strRange[i] << endl;
			cerr << "\tPlease only use characters 0-9 and .. to delimit the two values"  << endl;
			exit(EXIT_FAILURE);
		}
		
		if(strRange[i] == '.') { // Check for the .. delimiter
			numDots++;
		}
	}
	
	if(numDots != 2) {
		cerr << "Error: There are " << numDots << "periods, when there should be 2 in the range. " << strRange << endl;
		exit(EXIT_FAILURE);
	}

	int dots = strRange.find("..");
	if(dots == string::npos) {
		cerr << "Error: delimiter .. not found in range " << strRange << endl;
		exit(EXIT_FAILURE);
	}
	
	Range range;
	string strLow = strRange.substr(0, dots); // low equals the value before .. in [low..high]
	istringstream(strLow) >> range.low;
	
	string strHigh = strRange.substr(dots +2, strRange.length()); // high equals the value after .. in [low..high]
	istringstream(strHigh) >> range.high;
	
	if(range.low > range.high) {
		cerr << "Error: specified low value " << range.low << " is greater than high value " << range.high << endl;
		exit(EXIT_FAILURE);
	}
	
	return range;
}

// Takes in a string in the format (r, g, b) and returns a Triple struct of those values
Triple parseTriple(string strTriple) {
	int numCommas = 0;
	for(unsigned int i = 0; i < strTriple.length(); i++) { // check that there are no invalid characters
		if(!((strTriple[i] >= '0' && strTriple[i] <= '9') || strTriple[i] == ',' ||strTriple[i] == '(' || strTriple[i] == ')' ||isWhiteSpace(strTriple[i]))) {
			cerr << "Error: argument for triple contains invalid character, " << strTriple[i] << endl;
			cerr << "\tPlease only use characters numerical characters, commas, and parentheses"  << endl;
			exit(EXIT_FAILURE);
		}
		
		if(strTriple[i] == ',') { // there should only be 2 commas in a triple
			numCommas++;
		}
	}
	
	if(numCommas != 2) {
		cerr << "Error: There are " << numCommas << "commas, when there should only be 2 in the triple. " << strTriple << endl;
	}
	
	int leftPar = strTriple.find_first_of("(");
	if(leftPar == strTriple.length()) { // Check for left parenthesis
		cerr << "Error: Beginning '(' not found in triple " << strTriple << endl;
		exit(EXIT_FAILURE);
	}
	
	int firstComma = strTriple.find_first_of(",");
	Triple triple;
	// turn first value into an integer for value of red
	string strRed = strTriple.substr(leftPar+1, firstComma);
	istringstream(strRed) >> triple.red;
	if(triple.red > 256 || triple.red < 0) {
		cerr << "Error: first value of triple " << triple.red << " is invalid." << endl;
		cerr << "\tPlease make sure desired red value is between 0 and 256" << endl;
		exit(EXIT_FAILURE);
	}
	
	int secondComma = strTriple.find_last_of(",");
	// turn second value into an integer for value of green
	string strGreen = strTriple.substr(firstComma+1, secondComma);
	istringstream(strGreen) >> triple.green;
	if(triple.green > 256 || triple.green < 0) {
		cerr << "Error: Second value of triple " << triple.green << " is invalid." << endl;
		cerr << "\tPlease make sure desired green value is between 0 and 256" << endl;
		exit(EXIT_FAILURE);
	}
	
	int rightPar = strTriple.find(")"); //right parenthesis should be the last element of the string, but I don't trust myself any more
	// turn last value into an integer for value of blue
	string strBlue = strTriple.substr(secondComma+1, rightPar);
	istringstream(strBlue) >> triple.blue;
	if(triple.blue > 256 || triple.blue < 0) {
		cerr << "Error: third value of triple " << triple.blue << " is invalid." << endl;
		cerr << "\tPlease make sure desired blue value is between 0 and 256" << endl;
		exit(EXIT_FAILURE);
	}
	
	return triple;
}

// Takes in a string in the format (x, y) and returns a Coord struct of those values
Coord parseCoord(string strCoord) {
	int numCommas = 0;
	for(unsigned int i = 0; i < strCoord.length(); i++) { // check that no invalid characters
		if(!((strCoord[i] >= '0' && strCoord[i] <= '9') || strCoord[i] == '-' || strCoord[i] == ',' ||strCoord[i] == '(' || strCoord[i] == ')' ||isWhiteSpace(strCoord[i]))) {
			cerr << "Error: argument for Coord contains invalid character, " << strCoord[i] << endl;
			cerr << "\tPlease only use characters numerical characters, commas, and parentheses"  << endl;
			exit(EXIT_FAILURE);
		}
		
		if(strCoord[i] == ',') { // there should only be 1 commas in a Coord
			numCommas++;
		}
	}
	
	if(numCommas != 1) {
		cerr << "Error: There are " << numCommas << " commas, when there should only be 1 in the Coord " << strCoord << endl;
		exit(EXIT_FAILURE);
	}
	
	int leftPar = strCoord.find("(");
	if(leftPar == strCoord.length()) {
		cerr << "Error: Beginning '(' not found in Coord " << strCoord << endl;
		exit(EXIT_FAILURE);
	}
	
	int firstComma = strCoord.find(",");
	Coord coord;
	string strX = strCoord.substr(leftPar+1, firstComma);
	istringstream(strX) >> coord.x; // turn parsed x value into an integer
	
	int rightPar = strCoord.find(")");
	string strY = strCoord.substr(firstComma+1, rightPar);
	istringstream(strY) >> coord.y; // turn parsed y value into an integer
	
	return coord;
}