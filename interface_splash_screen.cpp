#include "interface_splash_screen.h"
#include <QApplication>
#include <QColor>
#include <QMovie>
#include <QLabel>

splash_screen :: splash_screen(QWidget* parent) {

//    this -> showMessage(QSplashScreen::tr("Building the terrain..."), Qt :: AlignCenter | Qt :: AlignHCenter, QColor(190, 190, 222, 255));
//    QApplication::processEvents();

    QMovie *movie = new QMovie("../terrain/splash_loader.gif");
    QLabel *label = new QLabel(this);
    label -> setMovie(movie);
    movie -> start();

}
