#include "BFInterpreter.hpp"

#include <iostream>
//#include <QChar>

BFInterpreter::BFInterpreter(QString bfSequence):
	QObject(),
	m_bfSequence(bfSequence)
{
	// init cells
	m_vCells    = QVector<int>(m_iNumberOfCells,0);
	m_iPosition = 0;
}

BFInterpreter& BFInterpreter::operator=(const BFInterpreter& that)
{
	// init cells
	m_vCells     = that.m_vCells;
	m_iPosition  = that.m_iPosition;
	m_bfSequence = that.m_bfSequence;
	return *this;
}

void BFInterpreter::interpret()
{
	interpret(m_bfSequence);
}

void BFInterpreter::interpret(QString bfSequence)
{
	std::cout << "interpreting " << bfSequence.toStdString() << std::endl;
	QString::const_iterator it = bfSequence.constBegin();
	for(; it != bfSequence.constEnd(); it++){
		//std::cout << it->toAscii();
		switch (it->toAscii()){
			case '+': incrementValue();   break;
			case '-': decrementValue();   break;
			case '>': incrementPointer(); break;
			case '<': decrementPointer(); break;
			case '.': putCLI(); put();    break;
			case '[': loop(bfSequence,it);break;
			case ']': break;
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
	while (cellCondition()) interpret(loopSequence);
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

// TODO: range checks
void BFInterpreter::incrementPointer() { m_iPosition++; }
void BFInterpreter::decrementPointer() { m_iPosition--; }
void BFInterpreter::incrementValue()   { m_vCells[m_iPosition]++; }
void BFInterpreter::decrementValue()   { m_vCells[m_iPosition]--; }
bool BFInterpreter::cellCondition()    { return m_vCells[m_iPosition] > 0; }
