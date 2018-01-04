// Author: Seth George

#include <QApplication>

#include "life_parsing.h"
#include "parsing.h"
#include "grid_window.h"

using namespace std;


int main(int argc, char** argv) {
	int generation = 0;
	int size = 10;
	
	Range terX; // terrain ranges
	Range terY;
	Range winX; // window ranges
	Range winY;
	
	bool terXflag = false; // if value was given to overwrite file value
	bool terYflag = false;
	bool winXflag = false;
	bool winYflag = false;
	
	bool hasControl= false;
	
	Info *info; // abstract class that holds all the relevant information
	ifstream inf;
	bool fileSpecified = false;
	
	for(int i = 1; i < argc; i++) {// Parse each argument on the command line.
		if(string(argv[i]) == "-h") { // display help screen
			printHelpGui();
			return 0;
			
		} else if(string(argv[i]) == "-g") { // Specify the desired generation number
			i++;
			if(i == argc) {
				cerr << "Error: no value given after switch -g" << endl;
				exit(EXIT_FAILURE);
			}
			
			for(unsigned j = 0; j < string(argv[i]).length(); j++){
				if(argv[i][j] < '0' || argv[i][j] > '9'){ // if not a number or zero
					cerr << "Error: given value for -g " << argv[i] << "is invalid, please only insert numerical values after -g tag" << endl;
					exit(EXIT_FAILURE);
				}
			}
			
			generation = atoi(argv[i]); // generation equals the given value
		
		} else if(string(argv[i]) == "-c") {
			hasControl= true;
		
		} else if(string(argv[i]) == "-s") {
			i++;
			if(i == argc) {
				cerr << "Error: no value given after switch -s" << endl;
				exit(EXIT_FAILURE);
			}
			
			for(unsigned j = 0; j < string(argv[i]).length(); j++) {
				if((argv[i][j] < '0' || argv[i][j] > '9') || argv[i][j] == '-'){ // if not a number or zero
					cerr << "Error: given value for -s " << argv[i] << "is invalid, please only insert numerical values after -s tag" << endl;
					exit(EXIT_FAILURE);
				}
			}
			
			size = atoi(argv[i]); // generation equals the given value
		
		} else if(string(argv[i]) == "-tx") { // Set the x range of the terrain			
			i++;
			if(i >= argc)  {
				cerr << "Error: No range l..h specified for switch -tx" << endl;
				exit(EXIT_FAILURE);
			}
			
			terX = parseRange(string(argv[i]));
			terXflag = true;
			
		} else if(string(argv[i]) == "-ty") { // Set the y range of the terrain
			i++;
			if(i >= argc)  {
				cerr << "Error: No range l..h specified for switch -ty" << endl;
				exit(EXIT_FAILURE);
			}
			
			terY = parseRange(string(argv[i]));
			terYflag = true;
			
		} else if(string(argv[i]) == "-wx") { // Set the x range of the output window
			i++;
			if(i >= argc)  {
				cerr << "Error: No range l..h specified for switch -wx" << endl;
				exit(EXIT_FAILURE);
			}
			
			winX = parseRange(string(argv[i]));
			winXflag = true;
			
		} else if(string(argv[i]) == "-wy") { // Set the y range of the output window
			i++;
			if(i >= argc)  {
				cerr << "Error: No range l..h specified for switch -wy" << endl;
				exit(EXIT_FAILURE);
			}
			
			winY = parseRange(string(argv[i]));
			winYflag = true;
		} else {
			if(fileSpecified) { //multiple files specified
				//make some error
			}
			inf.open(argv[i]); // else use given file
			if(!inf.good()) { // exit if file not found, there will be redundant checks in the helper functions
				cerr << "Error: given file could not be found. Please make sure you gave a good file path." << endl;
				exit(EXIT_FAILURE);
			}
		
			info = parseInput(inf); // parse the input file
			
			fileSpecified = true;
		}
	}

	if(!fileSpecified){ // if no files were specified
		info = parseInput(cin); // use standard in
	}

	if(terXflag) { //Overwrite parsed x range of terrain
		info->setTerrainX(terX);
	}
	if(terYflag) { //Overwrite parsed y range of terrain
		info->setTerrainY(terY);
	}
	if(winXflag) { //Overwrite parsed x range of window
		info->setWindowX(winX);
	}
	if(winYflag) { //Overwrite parsed y range of window
		info->setWindowY(winY);
	}
	
	info->generateGrid();
	info->advanceGen(generation);
	
	char* lifeGui = "./life_gui"; // QT stuff to make program
	char** argV = &lifeGui;
	int argC = 1;
	
	QApplication app(argC, argV); // Make the window
	GridWindow gridWindow(info, size, hasControl);
	gridWindow.show();
	
	return app.exec(); // run the app
}

