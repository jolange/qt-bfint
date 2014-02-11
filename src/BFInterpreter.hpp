#ifndef BFINTERPRETER_HPP_
#define BFINTERPRETER_HPP_

#include <QObject>
#include <QVector>
#include <QString>

namespace qt_bfint
{
   class BFInterpreter; 
   enum  EmptyInputHandle {breakProgram = 0, keepCell = 1, zeroCell = 2};
   enum  InterruptReason  
   {
      exitedNormally = 0, genericError, openBracketMissing, closeBracketMissing,
      inputInterrupt, maxLoopsExceed,
      cellUnderflow, cellOverflow, ptrUnderflow, ptrOverflow
   };
}


/*!
 * \class BFInterpreter
 * Interprets BF-Sequences in QString-Format
 */
class qt_bfint::BFInterpreter: public QObject
{
Q_OBJECT
public:
   /*! constructor
    *  \param bfSequence sequence to interpret
    */
   BFInterpreter(QString bfSequence="");
   //! copy-constructor
   BFInterpreter& operator=(const BFInterpreter& that);

   /*! actual interpreting
    *  \returns false if interrupted
    */
   InterruptReason interpret();

private:
   static const int m_iNumberOfCells = 5000;
   QVector<int>     m_vCells;
   int              m_iPosition;
   QString          m_bfSequence;
   QString          m_sInputQueue;

   InterruptReason  m_interruptReason;
   bool             m_bQueueInputs;
   int              m_iMaxLoopIterations;
   EmptyInputHandle m_emtpyInputHandle;

   void interpret(QString bfSequence);
   void loop(QString bfSequence, QString::const_iterator &itLoopStart);

   void put();
   void get();
   void incrementPointer();
   void decrementPointer();
   void incrementValue();
   void decrementValue();
   bool cellCondition();
signals:
   void signalPut(QChar);
public slots:
   void slotQueueInputs(int cs); // int is Qt::CheckState
   void slotMaxLoopIterations(int mli);
   void slotEmptyInputHandle(int ih); // int is qt_bfint::EmptyInputHandle
};

#endif // BFINTERPRETER_HPP_
