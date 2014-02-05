#include <QtGui/QApplication>
#include <QtGui/QPushButton>

#include "UIMain.hpp"

int main(int argc, char* argv[])
{
	QApplication application(argc,argv);
	UIMain ui;
	ui.show();
	return application.exec();
}
