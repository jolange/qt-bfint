#ifndef UIMAIN_HPP_
#define UIMAIN_HPP_

#include <QMainWindow>

#include "ui_UIMain.h"

class UIMain: public QMainWindow
{
Q_OBJECT
	
public:
	UIMain();
	virtual ~UIMain();
private:
	Ui::UIMain ui;
	
private slots:
	void slotExecute();
};

#endif // UIMAIN_HPP_
