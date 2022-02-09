#include "splash_screen.h"
#include <QApplication>
#include <QColor>

splash_screen :: splash_screen(const QPixmap* pix) {

//    QPixmap pixmap("../terrain/loader.gif");
//    this -> setPixmap(pixmap);
//    splash = new QSplashScreen(pixmap);

    stage = "Starting...";
//    QCoreApplication::processEvents();

    this -> showMessage(QSplashScreen::tr("Generating the terrain..."), Qt :: AlignCenter| Qt :: AlignHCenter, QColor(190, 190, 222, 255));
    QApplication::processEvents();
//        this -> showMessage(QSplashScreen::tr("XUUUUUY"), Qt::AlignCenter| Qt::AlignHCenter, Qt::black);

//        QCoreApplication :: processEvents();


   // this->showMessage(QSplashScreen::tr("AAAAAAA"), Qt::AlignCenter| Qt::AlignHCenter, Qt::black);
}


void splash_screen :: update_stage() {
//    QCoreApplication::processEvents();
    //this -> stage = "XUY!";
//     QCoreApplication :: processEvents();
//    this -> showMessage(QSplashScreen::tr("XUUUUUY"), Qt::AlignCenter| Qt::AlignHCenter, Qt::black);
QApplication::processEvents();

//        QCoreApplication::processEvents();
}
