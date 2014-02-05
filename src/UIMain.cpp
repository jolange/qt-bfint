#include "UIMain.hpp"
#include "ui_UIMain.h"

#include "BFInterpreter.hpp"

#include <iostream>
#include <QMessageBox>
#include <QString>

UIMain::UIMain():
	QMainWindow()
{
	ui.setupUi(this);
	ui.statusbar->showMessage("Ready");
	QString testSequence = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
	//QString testSequence = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";
	ui.tbInput->setPlainText(testSequence);
	
	connect (ui.buttonExecute, SIGNAL(clicked()),
	         this,             SLOT(slotExecute()));
	connect (&m_bfInt,         SIGNAL(signalPut(QChar)), 
	         this,             SLOT(slotPut(QChar)));
	         
	connect (ui.actionAbout,   SIGNAL(activated()), 
	         this,             SLOT(slotShowAboutDialog()));
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

void UIMain::slotShowAboutDialog()
{
	QString text = QString()
	             + "Qt4 based Brainfuck Interpreter GUI<br><br>Copyright 2014 Johannes Lange,<br>"
	             + "for License see LICENSE file shipped with the code<br>or visit<br><br>"
	             + "<a href='https://github.com/johannes-lange/qt-bfint'>https://github.com/johannes-lange/qt-bfint</a>";
	QMessageBox::about(this, "About qt-brainf", text);
	//QMessageBox::aboutQt(this);
}
