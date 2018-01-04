/*
* Important Note:	I this is one of the pages I was confused about. We are allowed to use the QT tutorial, right?
*					Most of the stuff here is based off the tutorial so I can't really say it is original content.
*					I hadn't figured out why my control and the window weren't talking to each other.
*/

#include "grid_window.h"

GridWindow::GridWindow(Info *info, int size, bool hasControl) {	
	setWindowTitle(tr("Game of Life"));
	// make scroll area
	scrollArea = new QScrollArea(this);
	
	// make scroll areas show up
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	scrollArea->setWidgetResizable(true);
	scrollArea->viewport()->setBackgroundRole(QPalette::Dark);
	scrollArea->viewport()->setAutoFillBackground(true);	
	setCentralWidget(scrollArea);
	
	if(hasControl) {
		// make control
		controlDialog = new ControlDialog(info->generation, size, this);

		// show control window
		controlDialog->show();
		controlDialog->activateWindow();
	}
}
