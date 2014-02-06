#include <QtGui/QApplication>
#include <QtGui/QPushButton>

#include "UIMain.hpp"

int main(int argc, char* argv[])
{
   using namespace qt_bfint;
   QApplication application(argc,argv);
   UIMain ui;
   ui.show();
   return application.exec();
}
