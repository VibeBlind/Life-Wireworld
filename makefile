all: life life_gui

clean:
	rm -f *.o *.gch *.pro life life_gui QMakefile

tarball: seth_george_proj2_final.tar.gz

seth_george_proj2_final.tar.gz: makefile life.cc life_gui.cc life_grid.cc parsing.cc parsing.h life_parsing.cc life_parsing.h life_structs.h README.txt grid_window.cc grid_window.h control.cc control.h
	tar -czf seth_george_proj2_final.tar.gz makefile life.cc life_gui.cc life_grid.cc parsing.cc parsing.h life_parsing.cc life_parsing.h life_structs.h README.txt grid_window.cc grid_window.h control.cc control.h

life: life.o life_grid.o life_parsing.o parsing.o
	g++ -o life life.o life_grid.o life_parsing.o parsing.o
life_gui: life_gui.cc life_grid.cc life_parsing.h parsing.cc parsing.h life_structs.h grid_window.cc grid_window.h control.cc control.h gui_grid.cc gui_grid.h
	qmake-qt4 -project -o life_gui.pro
	sed  -i 's/life.cc//g'  life_gui.pro
	qmake-qt4 -o QMakefile life_gui.pro
	make -f QMakefile

life.o: life.cc life_parsing.h life_structs.h
	g++ -Wall -c life.cc
life_grid.o: life_grid.cc life_structs.h
	g++ -Wall -c life_grid.cc
life_parsing.o: life_parsing.cc life_parsing.h life_structs.h
	g++ -Wall -c life_parsing.cc
parsing.o: parsing.cc parsing.h life_structs.h
	g++ -Wall -c parsing.cc