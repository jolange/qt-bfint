#include <QtGui/QApplication>
#include <QtGui/QGtkStyle>
#include <QtGui/QPushButton>

#include "UIMain.hpp"

int main(int argc, char* argv[])
{
   using namespace qt_bfint;
   QApplication application(argc,argv);
   application.setStyle(new QGtkStyle());
   UIMain ui;
   ui.show();
   return application.exec();
}
