#include "BFInterpreter.hpp"

#include <iostream>
#include <QInputDialog>


namespace qt_bfint{

BFInterpreter::BFInterpreter(QString bfSequence, int iTapeSize):
   QObject(),
   m_iNumberOfCells(iTapeSize),
   m_bfSequence(bfSequence),
   m_interruptReason(exitedNormally),
   m_bQueueInputs(true),
   m_iMaxLoopIterations(2000),
   m_emtpyInputHandle(breakProgram)
{
   // init cells
   m_vCells    = QVector<int>(m_iNumberOfCells,0);
   m_iPosition = 0;
}

BFInterpreter& BFInterpreter::operator=(const BFInterpreter& that)
{
   // init cells
   m_vCells         = that.m_vCells;
   m_iPosition      = that.m_iPosition;
   m_iNumberOfCells = that.m_iNumberOfCells;
   m_bfSequence     = that.m_bfSequence;
   m_bQueueInputs   = that.m_bQueueInputs;
   m_sInputQueue    = that.m_sInputQueue;
   m_interruptReason    = that.m_interruptReason;
   m_iMaxLoopIterations = that.m_iMaxLoopIterations;
   m_emtpyInputHandle   = that.m_emtpyInputHandle;
   return *this;
}

InterruptReason BFInterpreter::interpret()
{
   m_sInputQueue = "";
   interpret(m_bfSequence);
   return m_interruptReason;
}

void BFInterpreter::interpret(QString bfSequence)
{
   QString::const_iterator it = bfSequence.constBegin();
   for(; it != bfSequence.constEnd() && !m_interruptReason; it++){
      switch (it->toAscii()){
         case '+': incrementValue();                    break;
         case '-': decrementValue();                    break;
         case '>': incrementPointer();                  break;
         case '<': decrementPointer();                  break;
         case '.': put();                               break;
         case ',': get();                               break;
         case '[': loop(bfSequence,it);                 break;
         case ']': m_interruptReason=openBracketMissing;break;
         default : break;
      }
   }
}

void BFInterpreter::loop(QString bfSequence, QString::const_iterator &itLoopStart)
{
   QString loopSequence;
   QString::const_iterator &it = itLoopStart;
   it++;
   int iOpenBrackets = 0;
   QChar c;
   for(; it != bfSequence.constEnd(); it++){
      c = it->toAscii();
      if(c == '['){
         iOpenBrackets++;
      }else if(c == ']'){
         if (iOpenBrackets == 0){
            break;
         }else{
            iOpenBrackets--;
         }
      }
      loopSequence += c;
   }
   if (c != ']') // loop ended without finding close bracket
      m_interruptReason = closeBracketMissing;
   
   int iLoopCount = 0;
   while (cellCondition() && !m_interruptReason){
      interpret(loopSequence);
      iLoopCount++;
      if (iLoopCount >= m_iMaxLoopIterations)
         m_interruptReason = maxLoopsExceed;
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
      if (ok){
         if (!text.isEmpty()){
            if (m_bQueueInputs){
               m_sInputQueue += text;
               m_vCells[m_iPosition] = m_sInputQueue[0].toAscii();
               m_sInputQueue.remove(0,1);
            }else{
               m_vCells[m_iPosition] = text[0].toAscii();
            }
         }else{
            if (m_emtpyInputHandle == breakProgram){
               m_interruptReason = inputInterrupt;
            }else if (m_emtpyInputHandle == zeroCell){
               m_vCells[m_iPosition] = 0;
            } // else: (m_emtpyInputHandle == keep Cell)
               // do nothing.
         }
      }else{
         m_interruptReason = inputInterrupt;
      }
   }
}

void BFInterpreter::incrementPointer(){
   m_iPosition++;
   if (m_iPosition >= m_iNumberOfCells)
      m_interruptReason = ptrOverflow;
}
void BFInterpreter::decrementPointer()
{
   m_iPosition--;
   if (m_iPosition < 0)
      m_interruptReason = ptrUnderflow;
}
void BFInterpreter::incrementValue()
{
   m_vCells[m_iPosition]++;
   if (m_vCells[m_iPosition] > 255)
      m_interruptReason = cellOverflow;
}
void BFInterpreter::decrementValue(){
   m_vCells[m_iPosition]--;
   if (m_vCells[m_iPosition] < 0)
      m_interruptReason = cellUnderflow;
}
bool BFInterpreter::cellCondition() { return m_vCells[m_iPosition] > 0; }

// // // //
// SLOTS //
// // // //

void BFInterpreter::slotQueueInputs(int cs)
{
   m_bQueueInputs = (cs == Qt::Checked);
}

void BFInterpreter::slotMaxLoopIterations(int mli)
{
   m_iMaxLoopIterations = mli;
}

void BFInterpreter::slotEmptyInputHandle(int ih)
{
   m_emtpyInputHandle = (EmptyInputHandle)ih;
}

} // end namespace qt_bfint
