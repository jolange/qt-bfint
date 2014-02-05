#ifndef UIMAIN_HPP_
#define UIMAIN_HPP_


#include "ui_UIMain.h"
#include "BFInterpreter.hpp"

#include <QMainWindow>

/*!
 * \class UIMain
 * Main Window
 */
class UIMain: public QMainWindow
{
Q_OBJECT
	
public:
	UIMain();
	virtual ~UIMain();
private:
	Ui::UIMain ui;
	BFInterpreter m_bfInt;
	
private slots:
	void slotExecute();
	void slotPut(QChar);
};

#endif // UIMAIN_HPP_
