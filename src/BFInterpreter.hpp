#ifndef BFINTERPRETER_HPP_
#define BFINTERPRETER_HPP_

#include <QObject>
#include <QVector>
#include <QString>

/*!
 * \class BFInterpreter
 * Interprets BF-Sequences in QString-Format
 */
class BFInterpreter: public QObject
{
Q_OBJECT
public:
	/*! constructor
	 *  \param bfSequence sequence to interpret
	 */
	BFInterpreter(QString bfSequence="");
	//! copy-constructor
	BFInterpreter& operator=(const BFInterpreter& that);
	
	//! actual interpreting
	void interpret();
	
private:
	static const int m_iNumberOfCells = 5000;
	QVector<int>     m_vCells;
	int              m_iPosition;
	QString          m_bfSequence;
	
	void interpret(QString bfSequence);
	void loop(QString bfSequence, QString::const_iterator &itLoopStart);
		
	void putCLI();
	void put();
	void incrementPointer();
	void decrementPointer();
	void incrementValue();
	void decrementValue();
	bool cellCondition();
signals:
	void signalPut(QChar);
};

#endif // BFINTERPRETER_HPP_
