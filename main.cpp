#include "ofxget_widget.h"
#include "ofxgetmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OfxGetMainWindow main;
    main.show();

    return a.exec();
}
