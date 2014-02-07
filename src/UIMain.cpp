#include "UIMain.hpp"
#include "ui_UIMain.h"

#include "BFInterpreter.hpp"

#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

namespace qt_bfint{

UIMain::UIMain():
   QMainWindow()
{
   ui.setupUi(this);
   ui.statusbar->showMessage("Ready");
   QString testSequence = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
   //QString testSequence = "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.";
   ui.tbInput->setPlainText(testSequence);

   connect(ui.buttonExecute, SIGNAL(clicked()),
           this,             SLOT(slotExecute()));
   connect(ui.cbQueueInputs, SIGNAL(stateChanged(int)),
           &m_bfInt        , SLOT(slotQueueInputs(int)));
   connect(&m_bfInt,         SIGNAL(signalPut(QChar)), 
           this,             SLOT(slotPut(QChar)));
            
   connect(ui.actionOpen,    SIGNAL(activated()), 
           this,             SLOT(slotOpenFileDialog()));
   connect(ui.actionSave,    SIGNAL(activated()), 
           this,             SLOT(slotSaveFileDialog()));
   connect(ui.actionAbout,   SIGNAL(activated()), 
           this,             SLOT(slotShowAboutDialog()));
}

UIMain::~UIMain(){}

void UIMain::slotExecute()
{
   ui.statusbar->showMessage("Executing...");
   ui.tbOutput->clear();
   m_bfInt = BFInterpreter(ui.tbInput->toPlainText());
   m_bfInt.slotQueueInputs(ui.cbQueueInputs->checkState());
   bool interrupted = m_bfInt.interpret();
   if (!interrupted) ui.statusbar->showMessage("Execution done. Ready");
   else              ui.statusbar->showMessage("Execution interrupted. Ready");
}

void UIMain::slotPut(QChar c)
{
   ui.tbOutput->insertPlainText(c);
}

void UIMain::slotOpenFileDialog()
{
   ui.statusbar->showMessage("Opening");
   QString fn = QFileDialog::getOpenFileName(this, tr("Open File"),"./bf-examples",
                                             tr("BF Files (*.bf);;All Files (*)"));
   QFile file(fn);
   if(file.open(QIODevice::ReadOnly)){
      QString content = file.readAll();
      ui.tbInput->setPlainText(content);
      file.close();
   }
   ui.statusbar->showMessage("Opened File \"" + fn + "\". Ready");

}
void UIMain::slotSaveFileDialog()
{
   ui.statusbar->showMessage("Saving");
   QString fn = QFileDialog::getSaveFileName(this, tr("Save File"),"./bf-examples",
                                             tr("BF Files (*.bf);;All Files (*)"));
   QFile file(fn);
   if (file.open(QIODevice::WriteOnly)){
      QString content = ui.tbInput->toPlainText();
      QTextStream stream(&file);
      stream << content;
      file.close();
   }
   ui.statusbar->showMessage("Saved File \"" + fn + "\". Ready");
}

void UIMain::slotShowAboutDialog()
{
   QString text = QString()
                + "<b>qt-bfint</b> Version " + PROJECTVERSION + " (" + __DATE__ + ")<br>"
                + "Qt4 based Brainfuck Interpreter GUI<br><br>Copyright 2014 Johannes Lange,<br>"
                + "for License see LICENSE file shipped with the code<br>or visit<br><br>"
                + "<a href='https://github.com/johannes-lange/qt-bfint'>https://github.com/johannes-lange/qt-bfint</a>";
   QMessageBox::about(this, QString("About qt-brainf Version ") + PROJECTVERSION, text);
}


} // end namespace qt_bfint
