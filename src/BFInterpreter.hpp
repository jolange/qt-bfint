#ifndef BFINTERPRETER_HPP_
#define BFINTERPRETER_HPP_

#include <QVector>
#include <QString>

class BFInterpreter
{
public:
	BFInterpreter(QString bfSequence);
private:
	static const int m_iNumberOfCells = 5000;
	QVector<int>     m_vCells;
	int              m_iPosition;
	
	void interpret(QString bfSequence);
	
	void putCLI();
	void incrementPointer();
	void decrementPointer();
	void incrementValue();
	void decrementValue();
};

#endif // BFINTERPRETER_HPP_
