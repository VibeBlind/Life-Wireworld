#ifndef LIFE_STRUCTS_H
#define LIFE_STRUCTS_H

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;


/******************** Range ********************/
struct Range {
	int low;
	int high;
};

/******************** Triple ********************/
struct Triple {
	int red;
	int green;
	int blue;
};

/***************** GridDimension *****************/
struct GridDimension {
	Range x;
	Range y;
};

/******************** Coords ********************/
struct Coord {
	int x;
	int y;
};

/******************** Colors ********************/
struct Colors {
	Triple alive;  // color for "Alive" cells
	Triple dead; // color for "Dead" cells
};

/******************** WireColors ********************/
struct WireColors {
	Triple empty;
	Triple head;
	Triple tail;
	Triple wire;
};

/******************** Chars ********************/
struct Chars {
	char alive; // character for "Alive" cells
	char dead; // character for "Dead" cells
};

/******************** WireChars ********************/
struct WireChars {
	char empty;
	char head;
	char tail;
	char wire;
};

/******************** Grid ********************/
class Grid { // should be LifeGrid but everything works and it's already passed due
	protected:
		Chars chars;
		vector<Coord> init;
		vector< vector<char> > grid;
		GridDimension ter;
		GridDimension win;
		int tWidth;
		int tHeight;
		int wWidth;
		int wHeight;
		
	public:
		Grid(GridDimension terrain, GridDimension window, Chars givenChars, vector<Coord> initial);
		Grid() {}
		~Grid() {}
		
		int findAdjacent(int x, int y);
		char getCell(int x, int y);
		void update();
		void reset();
		void printGrid();
};

/******************** Info ********************/
class Info { //abstract class
	public:
		string name;
		GridDimension terrain;
		GridDimension window;
		int generation;
		void setTerrainX(Range x) { terrain.x = x; }
		void setTerrainY(Range y) { terrain.y = y; } 
		void setWindowX(Range x) { window.x = x; }
		void setWindowY(Range y) { window.y = y; }
		
		Info() {}
		virtual ~Info() {}
		
		virtual Triple getColor(int x, int y) = 0;
		virtual void generateGrid() = 0;
		virtual void advanceGen(int gen) = 0;
		virtual void resetGen() = 0;
		virtual void printVisual() = 0;
		virtual void printTextual() = 0;
};

/******************** LifeInfo ********************/
class LifeInfo : public Info {
	public:
		Chars chars;
		Colors colors;
		vector<Coord> initial;
		Grid grid;
		
		virtual Triple getColor(int x, int y) {
			if(grid.getCell(x,y) == chars.alive) {
				return colors.alive;
			} else {
				return colors.dead;
			}
		}
		
		virtual void generateGrid() {
			grid = Grid(terrain, window, chars, initial);
			generation = 0;
		}
		
		virtual void advanceGen(int gen) {
			for(int i = 0; i < gen; i++) {
				grid.update();
				generation++;
			}
		}
		
		virtual void resetGen() {
			grid.reset();
			generation = 0;
		}
		
		virtual void printVisual() {
			grid.printGrid();
		}
		
		// print out the test based version of the output
		virtual void printTextual();
};

/******************** WireGrid ********************
class WireGrid {
	protected:
		WireChars wireChars;
		WireColors wireColors;
		vector<Coord> initialHead;
		vector<Coord> initialTail;
		vector<Coord> initialWire;
		vector< vector<char> > grid;
		GridDimension ter;
		GridDimension win;
		int tWidth;
		int tHeight;
		int wWidth;
		int wHeight;
		
	public:
		// This is why I had structs for life
		WireGrid(GridDimension terrain, GridDimension window, WireChars wireChars, WireColors wireColors, vector<Coord> initialHead, vector<Coord> initialTail, vector<Coord> initialWire);
		WireGrid() {}
		~WireGrid() {}
		
		int findAdjacent(int x, int y);
		char getCell(int x, int y);
		void update();
		void reset();
		void printGrid();
};*/

/******************** WireInfo ********************
class WireInfo : public Info {
	public:
		WireChars wireChars;
		WireColors wireColors;
		vector<Coord> initialHead;
		vector<Coord> initialTail;
		vector<Coord> initialWire;
		WireGrid wireGrid;
		
		virtual Triple getColor(int x, int y) {
			if(wireGrid.getCell(x,y) == wireChars.head) {
				return wireColors.head;
			} else if(wireGrid.getCell(x,y) == wireColors.tail) {
				return wireColors.tail;
			} else if(wireGrid.getCell(x,y) == wireColors.wire) {
				return wireColors.wire;
			} else {
				return wireColors.empty;
			}
		}
		
		virtual void generateGrid() {
			wireGrid = WireGrid(terrain, window, wireChars, wireColors, initialHead, initialTail, initialWire);
			generation = 0;
		}
		
		virtual void advanceGen(int gen) {
			for(int i = 0; i < gen; i++) {
				wireGrid.update();
				generation++;
			}
		}
		
		virtual void printVisual() {
			wireGrid.printGrid();
		}
		
		// print out the test based version of the output
		virtual void printTextual();
};*/

#endif