// Author: Seth George

#include "life_structs.h"

using namespace std;

//Constructer
Grid::Grid(GridDimension terrain, GridDimension window, Chars givenChars, vector<Coord> initial) {
	ter = terrain;
	win = window;
	init = initial;
	chars = givenChars;
	
	tWidth = ter.x.high - ter.x.low + 1; // zero inclusive
	tHeight = ter.y.high - ter.y.low + 1;
	
	grid.resize(tWidth); // generate a grid based on the given GridDimension
	for(int i = 0; i < tWidth; i++) {
		grid[i].resize(tHeight);
	}
	
	for(int i = 0; i < tWidth; i++) { // set everything to dead
		for(int j = 0; j < tHeight; j++) {
			grid[i][j] = chars.dead;
		}
	}
	
	for(unsigned i = 0; i < init.size(); i++) { // set the ones from the initial list to alive
		grid[init[i].x - ter.x.low][init[i].y - ter.y.low] = chars.alive;
	}
}

// Gets the character in the terrain 2D vector given the x and y coordinates, used when printing out in a 
char Grid::getCell(int x, int y) {
	if((x >= ter.x.low) && (x <= ter.x.high) && (y >= ter.y.low) && (y <= ter.y.high)) { // if within ranges
		return grid[x - ter.x.low][y - ter.y.low]; // return the character in the 2D vector
	} 
	return chars.dead; // else return dead
}

// finds the number of adjacent living cells 
int Grid::findAdjacent(int x, int y) {
	int adjacent = 0;
	
	int left = x - 1;
	int right = x + 1;
	int bottom = y - 1;
	int top = y + 1;
	
	bool leftFlag = false; // default is out of bounds
	bool rightFlag = false;
	bool bottomFlag = false;
	bool topFlag = false;
	
	if(left >= 0) { // if left is not out of bounds
		leftFlag = true;
	}
	if(right < tWidth) { // if right is not out of bounds
		rightFlag = true;
	}
	if(bottom >= 0) { // if bottom is not out of bounds
		bottomFlag = true;
	}
	if(top < tHeight) { // if top is not out of bounds
		topFlag = true;
	}
	
	if(leftFlag) { //if is one to the left is within left bonds
		if(grid[left][y] == chars.alive) { // check if is alive
			adjacent++;
		}
	
		if(topFlag) { // top left
			if(grid[left][top] == chars.alive) {
				adjacent++;
			}
		}
		if(bottomFlag){ // bottom left
			if(grid[left][bottom] == chars.alive) {
				adjacent++;
			}
		}
	}
	
	if(rightFlag) { // right
		if(grid[right][y] == chars.alive) {
			adjacent++;
		}
		
		if(topFlag) { // top right
			if(grid[right][top] == chars.alive) {
				adjacent++;
			}
		}
		if(bottomFlag){ // bottom right
			if(grid[right][bottom] == chars.alive) {
				adjacent++;
			}
		}
	}
	
	if(topFlag) { // top
		if(grid[x][top] == chars.alive) {
			adjacent++;
		}
	}
	
	if(bottomFlag) { // bottom
		if(grid[x][bottom] == chars.alive) {
			adjacent++;
		}
	}
	
	return adjacent; // should have at max 8
}

// Updates a life file to the next generation
void Grid::update() { 
	vector< vector<char> > tempGrid;
	
	tempGrid.resize(tWidth);
	for(int i = 0; i < tWidth; i++) { // check if each character is dead
		tempGrid[i].resize(tHeight);
		for(int j = 0; j < tHeight; j++) {
			int adjacent = findAdjacent(i, j);
			if(grid[i][j] == chars.alive) {
				if((adjacent == 2) || (adjacent == 3)) {
					tempGrid[i][j] = chars.alive; // stasis
				} else {
					tempGrid[i][j] = chars.dead; // loneliness and over population
				}
			} else { // if dead
				if(adjacent == 3) {
					tempGrid[i][j] = chars.alive; // stasis
				} else {
					tempGrid[i][j] = chars.dead; // reproduction
				}
			}
		}
	}
	
	for(int i = 0; i < tWidth; i++) { // move everything over to the stored grid
		for(int j = 0; j < tHeight; j++) {
			grid[i][j] = tempGrid[i][j];
		}
	}
	
	tempGrid.clear(); //free space
}

// resets the grid back the it's initial state
void Grid::reset() {
	for(int i = 0; i < tWidth; i++) { // set everything to dead
		for(int j = 0; j < tHeight; j++) {
			grid[i][j] = chars.dead;
		}
	}
	
	for(unsigned i = 0; i < init.size(); i++) { // set the ones from the initial list to alive
		grid[init[i].x - ter.x.low][init[i].y - ter.y.low] = chars.alive;
	}
}

void Grid::printGrid() {
	for(int i = win.y.high; i >= win.y.low; i--) { 
		for(int j = win.x.low; j <= win.x.high; j++) { // print out everything in a line
			cout << getCell(j, i) << flush;
		}
		cout << endl; // end that line and start the next line
	}
}
