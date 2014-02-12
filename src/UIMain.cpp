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
   QFont fontMono("Monospace");
   fontMono.setStyleHint(QFont::TypeWriter); // for windows
   ui.tbInput ->setFont(fontMono);
   ui.tbOutput->setFont(fontMono);
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

   InterruptReason interrupt = m_bfInt.interpret();
   switch (interrupt){
      case exitedNormally     : ui.statusbar->showMessage("Execution done. Ready");                         break;
      case openBracketMissing : ui.statusbar->showMessage("Error: Open bracket is missing. Ready");         break;
      case closeBracketMissing: ui.statusbar->showMessage("Error: Close bracket is missing. Ready");        break;
      case cellOverflow       : ui.statusbar->showMessage("Error: Cell overflow. Ready");                   break;
      case cellUnderflow      : ui.statusbar->showMessage("Error: Cell underflow. Ready");                  break;
      case ptrOverflow        : ui.statusbar->showMessage("Error: Pointer overflow. Ready");                break;
      case ptrUnderflow       : ui.statusbar->showMessage("Error: Pointer underflow. Ready");               break;
      case inputInterrupt     : ui.statusbar->showMessage("Error: Input interrupt. Ready");                 break;
      case maxLoopsExceed     : ui.statusbar->showMessage("Error: Maximum number of Loops exceeded. Ready");break;
      case genericError       : ui.statusbar->showMessage("Error: Something went wrong. Ready");            break;
      default                 : ui.statusbar->showMessage("Error: Something went wrong. Ready");            break;
   }
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
   if (fn.isEmpty())
      ui.statusbar->showMessage("Opening cancelled. Ready");
   else
      slotOpenFile(fn);
}

void UIMain::slotSaveFileDialog()
{
   ui.statusbar->showMessage("Saving");
   QString fn = QFileDialog::getSaveFileName(this, tr("Save File"),"./bf-examples",
                                             tr("BF Files (*.bf);;All Files (*)"));
   if (fn.isEmpty()){
      ui.statusbar->showMessage("Saving cancelled. Ready");
   }else{
      QFile file(fn);
      if (file.open(QIODevice::WriteOnly)){
         QString content = ui.tbInput->toPlainText();
         QTextStream stream(&file);
         stream << content;
         file.close();
      }
      ui.statusbar->showMessage("Saved File \"" + fn + "\". Ready");
   }
}

void UIMain::slotLoadExample(QAction* actionExample)
{
   slotOpenFile(":/bf-examples/"+actionExample->text());
}

void UIMain::slotShowAboutDialog()
{
   QString text = "<b>qt-bfint</b> by Johannes Lange"; // backup text
   #define STRING1(x) #x
   #define STRING(x) STRING1(x)
   QString version( STRING(PROJECTVERSION) );
   #undef  STRING
   #undef  STRING1
   QFile aboutFile(":/resources/aboutText.html");
   if(aboutFile.open(QIODevice::ReadOnly)){
      text = aboutFile.readAll();
      text = text.arg(version).arg( __DATE__ );
      aboutFile.close();
   }
   QMessageBox::about(this, QString("About qt-brainf"), text);
}


} // end namespace qt_bfint
