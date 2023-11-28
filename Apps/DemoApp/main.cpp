#include <QApplication>
#include "MainWindow.h"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    MainWindow mainwinndow;

    mainwinndow.show();

    return app.exec();
}
