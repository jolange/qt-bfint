#include "UIMain.hpp"
#include "ui_UIMain.h"

#include "BFInterpreter.hpp"

#include <iostream>
#include <QString>

UIMain::UIMain():
	QMainWindow()
{
	ui.setupUi(this);
	ui.statusbar->showMessage("Ready");
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
	ui.statusbar->showMessage("Executing...");
	ui.tbOutput->clear();
	m_bfInt = BFInterpreter(ui.tbInput->toPlainText());
	m_bfInt.interpret();
	ui.statusbar->showMessage("Executing done. Ready");
}

void UIMain::slotPut(QChar c)
{
	ui.tbOutput->insertPlainText(c);
}

