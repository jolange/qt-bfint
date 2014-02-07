#include "BFInterpreter.hpp"

#include <iostream>
#include <QInputDialog>


namespace qt_bfint{

BFInterpreter::BFInterpreter(QString bfSequence):
   QObject(),
   m_bfSequence(bfSequence),
   m_bInterrupted(false),
   m_bQueueInputs(true)
{
   // init cells
   m_vCells    = QVector<int>(m_iNumberOfCells,0);
   m_iPosition = 0;
}

BFInterpreter& BFInterpreter::operator=(const BFInterpreter& that)
{
   // init cells
   m_vCells       = that.m_vCells;
   m_iPosition    = that.m_iPosition;
   m_bfSequence   = that.m_bfSequence;
   m_bInterrupted = that.m_bInterrupted;
   m_bQueueInputs = that.m_bQueueInputs;
   m_sInputQueue  = that.m_sInputQueue;
   return *this;
}

bool BFInterpreter::interpret()
{
   m_sInputQueue = "";
   interpret(m_bfSequence);
   return m_bInterrupted;
}

void BFInterpreter::interpret(QString bfSequence)
{
   QString::const_iterator it = bfSequence.constBegin();
   for(; it != bfSequence.constEnd() && !m_bInterrupted; it++){
      switch (it->toAscii()){
         case '+': incrementValue();   break;
         case '-': decrementValue();   break;
         case '>': incrementPointer(); break;
         case '<': decrementPointer(); break;
         case '.': put();              break;
         case ',': get();              break;
         case '[': loop(bfSequence,it);break;
         case ']': m_bInterrupted=true;break; // TODO error!
         default : break;
      }
   }
}

void BFInterpreter::loop(QString bfSequence, QString::const_iterator &itLoopStart)
{
   QString loopSequence;
   QString::const_iterator &it = itLoopStart;
   it++;
   QChar c;
   for(; it != bfSequence.constEnd(); it++){
      c = it->toAscii();
      if(c == ']') break;
      loopSequence += c;
   }

   int iLoopCount = 0;
   while (cellCondition() && !m_bInterrupted){
      interpret(loopSequence);
      iLoopCount++;
      if (iLoopCount > 2000)
         m_bInterrupted = true;
   }
}

void BFInterpreter::put()
{
   emit signalPut(QChar(m_vCells[m_iPosition]));
}

void BFInterpreter::get()
{
   if (m_bQueueInputs && !m_sInputQueue.isEmpty()){
      m_vCells[m_iPosition] = m_sInputQueue[0].toAscii();
      m_sInputQueue.remove(0,1);
   }else{
      bool ok;
      QString text = QInputDialog::getText(0, "Input requested!", "Input:",
                                           QLineEdit::Normal, "", &ok);
      if (ok && !text.isEmpty()){
         if (m_bQueueInputs){
            m_sInputQueue += text;
            m_vCells[m_iPosition] = m_sInputQueue[0].toAscii();
            m_sInputQueue.remove(0,1);
         }else{
            m_vCells[m_iPosition] = text[0].toAscii();
         }
      }else{
         m_bInterrupted = true;
      }
   }
}

void BFInterpreter::incrementPointer() { m_iPosition++; }
void BFInterpreter::decrementPointer() { m_iPosition--; }
void BFInterpreter::incrementValue()   { m_vCells[m_iPosition]++; }
void BFInterpreter::decrementValue()   { m_vCells[m_iPosition]--; }
bool BFInterpreter::cellCondition()    { return m_vCells[m_iPosition] > 0; }

// // // //
// SLOTS //
// // // //

void BFInterpreter::slotQueueInputs(int cs)
{
   m_bQueueInputs = (cs == Qt::Checked);
}

} // end namespace qt_bfint
