/*
*	Important Note:	I had stuff in here, but none of it worked until I looked off Monica's stuff.
*					If there is anything else I've forgotten, but causes problems, I do not claim ownership.
*
*/

#ifndef GUIGRID_H
#define GUIGRID_H

#include <QColor>
#include <QRect>
#include <QSize>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QWidget>

#include "life_parsing.h"

class GuiGrid : public QWidget {
	Q_OBJECT
	
	private:
		Info *info;
		int size;
		int delay;
		int timer;
		QImage image;
		QRect rect(int i, int j) const;
		void updateImage(); 

	public:
		GuiGrid(Info *i, int s, QWidget *parent = 0);
		QSize resize() const;
		void paintEvent(QPaintEvent *event);
		void timerEvent(QTimerEvent *event);
		
	signals:
		void genUpdate(int g);
		
	public slots:
		void play();
		void pause();
		void stepPress();
		void restartPress();
		void delayChange(int d);
		void gridSizeChange(int s);
};

#endif