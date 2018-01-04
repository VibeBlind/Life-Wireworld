// Author: Seth George based of QT Tutorial

#ifndef CONTROL_H
#define CONTROL_H

#include <sstream>
#include <string>

#include <QLabel>
#include <QSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QDialog>

#include "life_structs.h"

class ControlDialog : public QDialog {
	Q_OBJECT

	signals:
		// Events
		void gridSizeChange(int change);
		void delayChange(int change);
		void quitPress();
		void restartPress();
		void playPress();
		void pausePress();
		void stepPress();;
		
	private slots:
		void play();
		void pause();
		void updateGen(int gen);
		
	public:
		ControlDialog(int generation, int gridSize, QWidget *parent);
		
	private:
		int size;
	
		// Grid Size
		QLabel *gridSizeLabel;
		QSpinBox *gridSizeSpinBox;
		QSlider *gridSizeSlider;
		QHBoxLayout *gridSizeLayout;
		// Delay
		QLabel *delayLabel;
		QSpinBox *delaySpinBox;
		QSlider *delaySlider;
		QHBoxLayout *delayLayout;
		// Generation
		QLabel *genLabel;
		QLabel *genVarLabel;
		QHBoxLayout *genLayout;
		// Buttons
		QPushButton *quitButton;
		QPushButton *restartButton;
		QPushButton *playButton;
		QPushButton *stepButton;
		QHBoxLayout *buttonLayout;
};

#endif