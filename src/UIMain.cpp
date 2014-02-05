#include "UIMain.hpp"
#include "ui_UIMain.h"

#include "BFInterpreter.hpp"

#include <iostream>
#include <QString>

UIMain::UIMain():
	QMainWindow()
{
	ui.setupUi(this);
	//QString testSequence = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	QString testSequence = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";
	ui.tbInput->setPlainText(testSequence);
	
	connect (ui.buttonExecute, SIGNAL(clicked()),
	         this,             SLOT(slotExecute()));
	connect (&m_bfInt,         SIGNAL(signalPut(QChar)), 
	         this,             SLOT(slotPut(QChar)));
}

UIMain::~UIMain(){}

void UIMain::slotExecute()
{
	ui.tbOutput->clear();
	m_bfInt = BFInterpreter(ui.tbInput->toPlainText());
	m_bfInt.interpret();
}

void UIMain::slotPut(QChar c)
{
	ui.tbOutput->insertPlainText(c);
}

