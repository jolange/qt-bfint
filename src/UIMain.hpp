#ifndef UIMAIN_HPP_
#define UIMAIN_HPP_


#include "ui_UIMain.h"
#include "BFInterpreter.hpp"

#include <QMainWindow>

namespace qt_bfint { class UIMain; }

/*!
 * \class UIMain
 * Main Window
 */
class qt_bfint::UIMain: public QMainWindow
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
	
	void slotOpenFileDialog();
	void slotSaveFileDialog();
	void slotShowAboutDialog();
};

#endif // UIMAIN_HPP_
