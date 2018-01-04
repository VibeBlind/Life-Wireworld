Author: Seth George

The README is a brief explanation to the following programs:
life.cc
life_gui.cc			life_structs.h
life_parsing.cc		life_parsing.h
parsing.cc			parsing.h
life_grid.cc
grid_window.cc		grid.window.h
control.cc			control.h
gui_grid.cc			gui_grid.h

I tired my best to remove any instances of guiGrid within my code and still have it compile.

life.cc:
	This program reads a single input file, either from a pathname passed as an argument, 
	or from standard input if no file names are given as arguments. The input file specifies 
	the Dimension of the terrain and the initial configuration for generation 0. The program 
	determines and displays the state of each cell at generation n. 
	The program accepts the following command line switches.\n 
		-h 		 Display a help screen that describes the program. 
		-v 		 Output should be visual: an ASCII display of the terrain with appropriate characters for the 
				 dead and alive cells. The dead character is ~ and the alive character is @. 
		-f 		 Outputs a file format in a readable code-like format. 
		-g n 	 Specify the desired generation number. If omitted, the default should be n = 0 
		-tx l..h Set the x range of the terrain; overrides values specified in the input file. 
		-ty l..h Set the y range of the terrain; overrides values specified in the input file. 
		-wx l..h Set the x range of the output window; otherwise this defaults to the x range of the terrain. 
		-wy l..h Set the y range of the output window; otherwise this defaults to the y range of the terrain. 
	Note that ranges l..h specify that the value v is between l and h, inclusive (i.e., l <= v <= h).

life_gui.cc:
	Currently only displays a help screen of how it should work.
	The program reads a single input file either from a pathname passed as an argument,
	or from standard input if no file names are given as arguments. The program determines and
	displays the state of each cell at generation n, as a grid and using the colors specified for
	each state. The window title should be the Name specified in the input file.
	The program should accept the following command{line switches.
		-g  n 	 Specify the desired generation number. If omitted, the default should be n = 0.
		-h 		 Display a help screen that describes the program, and terminate before starting the GUI.
		-s  n 	 Specify the size, in pixels, of each square in the grid (default should be 10).
				 Grid lines should be omitted when the size is less than 4.
		-tx l..h Set the x range of the terrain; overrides values specified in the input file.
		-ty l..h Set the y range of the terrain; overrides values specified in the input file.
		-wx l..h Set the (initial) x range of the output window (default is terrain x range).
		-wy l..h Set the (initial) y range of the output window (default is terrain y range).
	
life_parsing.cc, life_parsing.h, life_structs.h
	This file houses all the helper functions used for parsing the input file, printing help screen to stdout,
	many of misc functions that are used in the main functions of life and life_gui. It also implements some of the
	class functions	of classes held in life_structs.h. This wasn't meant to happen, and the classes were meant to have individual
	files for each class, but due to time constraints and getting things to work, I just didn't want to fix/break it.
	life_util.h also holds all the various structs of Range, Coords, Colors,... etc, which are used to pass collections of data.
	Originally these were classes, but due to time constraints and many other things, they were made into structs for easy access.
	
parsing.cc and parsing.h
	This file is the base class (abstractish class) for the methods used for parsing the input files. Life is the only working
	file format at this point, but it's children would be life_parsing (working), wire_parsing, and eleParsing. Each of these
	files would hold the functions that implement the functions to correctly parse the corresponding file formats.
	It can be related to the Info class used to hold common information that has be parsed.
	
life_grid.cc
	This file contains the class related to life's grid logic. Functions about advancing generation and updating the grid
	can be found here. This class, Grid, was intended to be the base class for life_grid, wire_grid, and eleGrid, but
	ended up only supporting life logic in order to get things into a presentable state.
	Unfortunately, this means some of my other classes (WireGrid), had to be commented out, but
	has been left in the code so they can demonstrate it was worked on.

control.c and control.h
	This file is the QT dialog for the control box used to control the game grid. It has a slider and spin box for both
	grid size and delay between generations. It also displays the current generation and 
	has a button to play/pause, restart, step 1 generation, and quit the program.
	
gui_grid.cc and gui_grid.h //Author Monica Kozbial
	This file is a widget called GuiGrid. This makes a gui to represent the afore mentioned grid class. A lot of the functions
	are mainly making boxes and painting them, checking for events and other gui like things. Originally, I tried to do within the grid_window
	class, but it didn't work well. Which is why I used this class instead my my old stuff.
	
grid_window.cc
	This file deals with creating a main window to connect the game logic with the dialog, control, and the widget, guigrid,.