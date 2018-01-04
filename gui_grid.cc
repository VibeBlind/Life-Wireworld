// Author: Monica Kozbial and QT tutorial on how to make custom widgets

/*
*	Important Note:	I'm leaving the stuff in so everything still compiles. Not sure if that's a good or bad idea...
*					I know it's harder for you grade when it doesn't work, but still...
*/


#include "gui_grid.h"

GuiGrid::GuiGrid(Info *givenInfo, int gridSize, QWidget *parent) : QWidget(parent){
	info = givenInfo;
	size = gridSize;
	timer = 0;

	setAttribute(Qt::WA_StaticContents);
	setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
	
	int height = info->window.y.high - info->window.y.low + 1;
	int width = info->window.x.high - info->window.x.low + 1;
	image = QImage(width, height, QImage::Format_ARGB32);
	image.fill(qRgba(0, 0, 0, 0));
}

void GuiGrid::play() {
	pause();
	timer = startTimer(delay);
}

void GuiGrid::pause() {
	if(timer != 0) {
		killTimer(timer);
		timer = 0;
	}
}

void GuiGrid::stepPress() {
	info->advanceGen(1);
	update();
	emit genUpdate(info->generation);
}

void GuiGrid::restartPress() {
	info->resetGen();
	update();
	emit genUpdate(info->generation);
}

void GuiGrid::delayChange(int d) {
	delay = d;
	if(timer != 0) {
		play();
	}
}

void GuiGrid::gridSizeChange(int gridSize) {
	if(gridSize < 1) {
		gridSize = 1;
	}
	if(gridSize != size)  {
		size = gridSize;
		update();
		updateGeometry();
	}
}

QSize GuiGrid::resize() const {
	QSize resize = size * image.size();
	if (size >= 4) {
		resize += QSize(1, 1);
	}
	return resize;
}

void GuiGrid::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	if (size >= 4) {
		painter.setPen(QColor(0,0,0));
		for (int i = 0; i <= image.width(); ++i) {
			painter.drawLine(size * i, 0, size * i, size * image.height());
		}
		
		for (int j = 0; j <= image.height(); ++j) {
			painter.drawLine(0, size * j, size * image.width(), size * j);
		}
	}
	
	updateImage();
	
	for (int i = 0; i < image.width(); ++i) {
		for (int j = 0; j < image.height(); ++j) {
			QRect r = rect(i, j);
			if (!event->region().intersect(r).isEmpty()) {
				QColor color = QColor::fromRgba(image.pixel(i, j));
				painter.fillRect(r, color);
			}
		}
	}

}

QRect GuiGrid::rect(int i, int j) const {
	if (size >= 4) {
		return QRect(size * i + 1, size * j + 1, size - 1, size - 1);
	} else {
		return QRect(size * i, size * j, size, size);
	}
}

void GuiGrid::updateImage() {
	int x = 0; 
	int y = 0;
	for(int i = info->window.y.high; i >= info->window.y.low; i--) {
		for(int j = info->window.x.low; j <= info->window.x.high; j++) {
			Triple cellColor = info->getColor(j, i);
			QColor color = QColor(cellColor.red, cellColor.green, cellColor.blue);
			image.setPixel(x, y, color.rgba());
			x++;
		}
		y++;
		x = 0;
	}
}

void GuiGrid::timerEvent(QTimerEvent *event) {
	if (event->timerId() == timer) {
		stepPress();
	} else {
		QWidget::timerEvent(event);
	}
}