#include <QtGui/QApplication>
#include <QtGui/QPushButton>

#include "UIMain.hpp"

int main(int argc, char* argv[])
{
	QApplication application(argc,argv);
	//QPushButton button("HEYA");
	//button.show();
	UIMain ui;
	ui.show();
	ui.show();
	return application.exec();
}
