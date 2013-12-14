#include <QApplication>
#include "renderer.h"

int main( int argc, char* argv[] )
{
    QApplication a( argc, argv );
    Renderer w;
    w.show();

    return a.exec();
}

