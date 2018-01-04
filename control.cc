// Author: Seth George based of QT Tutorial

#include "control.h"

ControlDialog::ControlDialog(int generation, int gridSize, QWidget *parent) : QDialog(parent) {
	int size = gridSize;
	
	// Control for Grid Size
	gridSizeLabel = new QLabel("Grid Size:");
	gridSizeSpinBox = new QSpinBox;
	gridSizeSlider = new QSlider(Qt::Horizontal);
	gridSizeSpinBox->setRange(1, 64);
	gridSizeSlider->setRange(1, 64);
	// Connections for Grid Size
	connect(gridSizeSpinBox, SIGNAL(valueChanged(int)), gridSizeSlider, SLOT(setValue(int)));
	connect(gridSizeSlider, SIGNAL(valueChanged(int)), gridSizeSpinBox, SLOT(setValue(int)));
	connect(gridSizeSlider, SIGNAL(valueChanged(int)), this, SIGNAL(gridSizeChange(int)));
	gridSizeSpinBox->setValue(10);
	// Layout for Grid Size
	QHBoxLayout *gridSizeLayout = new QHBoxLayout;
	gridSizeLayout->addWidget(gridSizeLabel);
	gridSizeLayout->addWidget(gridSizeSpinBox);
	gridSizeLayout->addWidget(gridSizeSlider);
	
	// Layout for the Delay
	delayLabel = new QLabel("Delay:");
	delaySpinBox = new QSpinBox;
	delaySlider = new QSlider(Qt::Horizontal);
	delaySpinBox->setRange(1, 100);
	delaySlider->setRange(1, 100);
	//Connections for Delay
	connect(delaySpinBox, SIGNAL(valueChanged(int)), delaySlider, SLOT(setValue(int)));
	connect(delaySlider, SIGNAL(valueChanged(int)), delaySpinBox, SLOT(setValue(int)));
	connect(delaySlider, SIGNAL(valueChanged(int)), this, SIGNAL(delayChange(int)));
	delaySpinBox->setValue(1);
	// Layout for Grid Size
	QHBoxLayout *delayLayout = new QHBoxLayout;
	delayLayout->addWidget(delayLabel);
	delayLayout->addWidget(delaySpinBox);
	delayLayout->addWidget(delaySlider);
	
	// Control for Generation
	genLabel = new QLabel(tr("Generation: "));
	genVarLabel = new QLabel("Variable for Generation");
	updateGen(generation);
	// Layout for Generation
	QHBoxLayout *genLayout = new QHBoxLayout;
	genLayout->addWidget(genLabel);
	genLayout->addWidget(genVarLabel);
	
	// Control for buttons at the bottom
	quitButton = new QPushButton(tr("Quit"));
	restartButton = new QPushButton(tr("Restart"));
	playButton = new QPushButton(tr("Play"));
	stepButton = new QPushButton(tr("Step"));
	// Connections for buttons
	connect(quitButton, SIGNAL(clicked()), this, SIGNAL(quitPress()));
	connect(restartButton, SIGNAL(clicked()), this, SIGNAL(restartPress()));
	connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
	connect(stepButton, SIGNAL(clicked()), this, SIGNAL(stepPress()));
	// Layout for the buttons
	QHBoxLayout *buttonLayout = new QHBoxLayout;
	buttonLayout->addWidget(quitButton);
	buttonLayout->addWidget(restartButton);
	buttonLayout->addWidget(playButton);
	buttonLayout->addWidget(stepButton);
	
	// Main layout, made of the other layouts
	QVBoxLayout *layout = new QVBoxLayout;
	layout->addLayout(gridSizeLayout);
	layout->addLayout(delayLayout);
	layout->addLayout(genLayout);
	layout->addLayout(buttonLayout);
	setLayout(layout);
	
	setWindowTitle(tr("Control"));
}

// Play through a loop to advance the game logic
void ControlDialog::play() {
	playButton->setText("Pause");
	emit playPress();
	disconnect(playButton, SIGNAL(clicked()), this, SLOT(play()));
	connect(playButton, SIGNAL(clicked()), this, SLOT(pause()));
}

// Pause the loop
void ControlDialog::pause() {
	playButton->setText("Play");
	emit pausePress();
	disconnect(playButton, SIGNAL(clicked()), this, SLOT(pause()));
	connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
}

// Change the generation
void ControlDialog::updateGen(int gen) {
	stringstream ss;
	ss << gen;
	string str = ss.str();
	char const* cStr = (char*) str.c_str();
	genVarLabel->setText(cStr);
}