#include <QtGui/QApplication>
#include <QtGui/QGtkStyle>
#include <QtGui/QPushButton>

#include "UIMain.hpp"

int main(int argc, char* argv[])
{
   using namespace qt_bfint;
   QApplication application(argc,argv);
   #ifndef _WIN32
   application.setStyle(new QGtkStyle());
   #endif // _WIN32
   UIMain ui;
   ui.show();
   return application.exec();
}
