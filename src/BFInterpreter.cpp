#include "BFInterpreter.hpp"

#include <iostream>
//#include <QChar>

BFInterpreter::BFInterpreter(QString bfSequence)
{
	// init cells
	m_vCells    = QVector<int>(m_iNumberOfCells,0);
	m_iPosition = 0;

	// TODO clean sequence
	
	std::cout << bfSequence.toStdString() << std::endl;
	//m_vCells[m_iPosition] = 65;
	//putCLI();
	interpret(bfSequence);
	
	std::cout << std::endl;
}

void BFInterpreter::interpret(QString bfSequence)
{
	QString::const_iterator it = bfSequence.constBegin();
	for(; it != bfSequence.constEnd(); it++){
		//std::cout << it->toAscii();
		switch (it->toAscii()){
			case '+': incrementValue();   break;
			case '-': decrementValue();   break;
			case '>': incrementPointer(); break;
			case '<': decrementPointer(); break;
			case '.': putCLI();           break;
			case '[': break;
			case ']': break;
			default : break;
		}
	}
}

void BFInterpreter::putCLI()
{
	//std::cout << QChar(m_vCells[m_iPosition]).toAscii() << std::flush;
	std::cout << (char)m_vCells[m_iPosition] << std::flush;
	//std::cout << m_vCells[m_iPosition] << std::flush;
}

// TODO: range checks
void BFInterpreter::incrementPointer() { m_iPosition++; }
void BFInterpreter::decrementPointer() { m_iPosition--; }
void BFInterpreter::incrementValue()   { m_vCells[m_iPosition]++; }
void BFInterpreter::decrementValue()   { m_vCells[m_iPosition]--; }
