#ifndef BFINTERPRETER_HPP_
#define BFINTERPRETER_HPP_

#include <QObject>
#include <QVector>
#include <QString>

namespace qt_bfint { class BFInterpreter; }

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
   bool interpret();
   
private:
   static const int m_iNumberOfCells = 5000;
   QVector<int>     m_vCells;
   int              m_iPosition;
   QString          m_bfSequence;
   QString          m_sInputQueue;

   bool             m_bInterrupted;
   bool             m_bQueueInputs;

   void interpret(QString bfSequence);
   void loop(QString bfSequence, QString::const_iterator &itLoopStart);

   void putCLI(); // TODO remove
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
};

#endif // BFINTERPRETER_HPP_
