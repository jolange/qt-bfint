#include "BFInterpreter.hpp"

#include <iostream>
#include <QInputDialog>


namespace qt_bfint{

BFInterpreter::BFInterpreter(QString bfSequence):
   QObject(),
   m_bfSequence(bfSequence),
   m_bInterrupted(false)
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
   return *this;
}

bool BFInterpreter::interpret()
{
   interpret(m_bfSequence);
   return m_bInterrupted;
}

void BFInterpreter::interpret(QString bfSequence)
{
   std::cout << "interpreting " << bfSequence.toStdString() << std::endl;
   QString::const_iterator it = bfSequence.constBegin();
   for(; it != bfSequence.constEnd() && !m_bInterrupted; it++){
      //std::cout << it->toAscii();
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
   std::cout << std::endl;
}

void BFInterpreter::loop(QString bfSequence, QString::const_iterator &itLoopStart)
{
   std::cout << "loop:";
   QString loopSequence;
   QString::const_iterator &it = itLoopStart;
   it++;
   QChar c;
   for(; it != bfSequence.constEnd(); it++){
      c = it->toAscii();
      if(c == ']') break;
      loopSequence += c;
   }
   std::cout << loopSequence.toStdString() << std::endl;
   int iLoopCount = 0;
   while (cellCondition() && !m_bInterrupted){
      interpret(loopSequence);
      iLoopCount++;
      if (iLoopCount > 2000)
         m_bInterrupted = true;
   }
}

void BFInterpreter::putCLI()
{
   //std::cout << QChar(m_vCells[m_iPosition]).toAscii() << std::flush;
   std::cout << (char)m_vCells[m_iPosition] << std::flush;
   //std::cout << m_vCells[m_iPosition] << std::flush;
}

void BFInterpreter::put()
{
   emit signalPut(QChar(m_vCells[m_iPosition]));
}

void BFInterpreter::get()
{
   bool ok;
   QString text = QInputDialog::getText(0, "Input requested!", "Input:",
                                        QLineEdit::Normal, "", &ok);
   if (ok && !text.isEmpty()){
      m_vCells[m_iPosition] = text[0].toAscii();
   }else{
      m_bInterrupted = true;
   }
}


void BFInterpreter::incrementPointer() { m_iPosition++; }
void BFInterpreter::decrementPointer() { m_iPosition--; }
void BFInterpreter::incrementValue()   { m_vCells[m_iPosition]++; }
void BFInterpreter::decrementValue()   { m_vCells[m_iPosition]--; }
bool BFInterpreter::cellCondition()    { return m_vCells[m_iPosition] > 0; }


} // end namespace qt_bfint
