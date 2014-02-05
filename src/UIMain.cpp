#include "UIMain.hpp"
#include "ui_UIMain.h"

#include "BFInterpreter.hpp"

#include <iostream>
#include <QString>

UIMain::UIMain():
	QMainWindow()
{
	ui.setupUi(this);
	//this->setText("HEYO");
	//connect(this, SIGNAL(clicked()), this, SLOT(testCall()));
	//QString testSequence = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	QString testSequence = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";
	ui.tbInput->setPlainText(testSequence);
	connect(ui.buttonExecute, SIGNAL(clicked()), this, SLOT(slotExecute()));
}

UIMain::~UIMain(){}

void UIMain::slotExecute()
{
	BFInterpreter bfInt(ui.tbInput->toPlainText());
}

