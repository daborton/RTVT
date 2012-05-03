#include "rtvtmainwindow.h"
#include "rtvtcontrolwindow.h"

#include <QApplication>

int main(int argc, char **argv)
{

    QApplication app(argc, argv);

    RTVTControlWindow window;
    window.show();

    return app.exec();
}
