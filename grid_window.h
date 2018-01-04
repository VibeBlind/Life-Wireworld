// Author: Seth George

#ifndef GRID_WINDOW_H_
#define GRID_WINDOW_H_

#include <QMainWindow>
#include <QScrollArea>

#include "gui_grid.h"
#include "control.h"

class GridWindow : public QMainWindow {
	Q_OBJECT
	
	public:
		GridWindow(Info *info, int size, bool hasControl);
		
	private:
		ControlDialog *controlDialog;
		QScrollArea *scrollArea;
};

#endif