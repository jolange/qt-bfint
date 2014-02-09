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
   QMainWindow(),
   m_menuExamples("Load Example...")
{
   ui.setupUi(this);
   buildExamplesMenu();

   ui.statusbar->showMessage("Ready");
   slotOpenFile(":/bf-examples/hello.bf");

   connect(ui.buttonExecute, SIGNAL(clicked()),
           this,             SLOT(slotExecute()));
   connect(ui.cbQueueInputs, SIGNAL(stateChanged(int)),
           &m_bfInt,         SLOT(slotQueueInputs(int)));
   connect(ui.sbMaxLoopIter, SIGNAL(valueChanged(int)),
           &m_bfInt,         SLOT(slotMaxLoopIterations(int)));
   connect(ui.cbEIH,         SIGNAL(currentIndexChanged(int)),
           &m_bfInt,         SLOT(slotEmptyInputHandle(int)));

   connect(&m_bfInt,         SIGNAL(signalPut(QChar)), 
           this,             SLOT(slotPut(QChar)));

   connect(ui.tbInput,       SIGNAL(undoAvailable(bool)),
           ui.actionUndo,    SLOT(setEnabled(bool)));
   connect(ui.tbInput,       SIGNAL(redoAvailable(bool)),
           ui.actionRedo,    SLOT(setEnabled(bool)));
   connect(ui.actionUndo,    SIGNAL(activated()),
           ui.tbInput,       SLOT(undo()));
   connect(ui.actionRedo,    SIGNAL(activated()),
           ui.tbInput,       SLOT(redo()));

   connect(ui.actionOpen,    SIGNAL(activated()), 
           this,             SLOT(slotOpenFileDialog()));
   connect(ui.actionSave,    SIGNAL(activated()), 
           this,             SLOT(slotSaveFileDialog()));
   connect(ui.actionAbout,   SIGNAL(activated()), 
           this,             SLOT(slotShowAboutDialog()));
}

UIMain::~UIMain(){}

void UIMain::buildExamplesMenu()
{
   // can't access separator from ui-file, so add one manually here...
   QAction* separator = ui.menuFile->insertSeparator(ui.actionQuit);
   ui.menuFile->insertMenu(separator,&m_menuExamples);
   // get all examples from resource dir
   QDir dir(":/bf-examples");
   QStringList slExamples = dir.entryList(QStringList("*.bf"));
   foreach (QString sExample, slExamples){
      m_menuExamples.addAction(sExample);
   }
   connect(&m_menuExamples, SIGNAL(triggered(QAction*)), 
           this,            SLOT(slotLoadExample(QAction*)));
}

void UIMain::slotExecute()
{
   ui.statusbar->showMessage("Executing...");
   ui.tbOutput->clear();
   m_bfInt = BFInterpreter(ui.tbInput->toPlainText());
   m_bfInt.slotQueueInputs(ui.cbQueueInputs->checkState());
   m_bfInt.slotMaxLoopIterations(ui.sbMaxLoopIter->value());
   m_bfInt.slotEmptyInputHandle(ui.cbEIH->currentIndex());
   bool interrupted = m_bfInt.interpret();
   if (!interrupted) ui.statusbar->showMessage("Execution done. Ready");
   else              ui.statusbar->showMessage("Execution interrupted. Ready");
}

void UIMain::slotPut(QChar c)
{
   ui.tbOutput->insertPlainText(c);
}

void UIMain::slotOpenFile(QString filename)
{
   QFile file(filename);
   if(file.open(QIODevice::ReadOnly)){
      QString content = file.readAll();
      ui.tbInput->setPlainText(content);
      file.close();
   }
   ui.statusbar->showMessage("Opened File \"" + filename + "\". Ready");
}

void UIMain::slotOpenFileDialog()
{
   ui.statusbar->showMessage("Opening");
   QString fn = QFileDialog::getOpenFileName(this, tr("Open File"),"./bf-examples",
                                             tr("BF Files (*.bf);;All Files (*)"));
   slotOpenFile(fn);
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

void UIMain::slotLoadExample(QAction* actionExample)
{
   slotOpenFile(":/bf-examples/"+actionExample->text());
}

void UIMain::slotShowAboutDialog()
{
   QString text = "<b>qt-bfint</b> by Johannes Lange"; // backup text
   QFile aboutFile(":/resources/aboutText.html");
   if(aboutFile.open(QIODevice::ReadOnly)){
      text = aboutFile.readAll();
      text = text.arg( PROJECTVERSION ).arg( __DATE__ );
      aboutFile.close();
   }
   QMessageBox::about(this, QString("About qt-brainf Version ") + PROJECTVERSION, text);
}


} // end namespace qt_bfint
