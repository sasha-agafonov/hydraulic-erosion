#ifndef INTERFACE_SPLASH_SCREEN_H
#define INTERFACE_SPLASH_SCREEN_H

#include <QSplashScreen>
#include <QPixmap>
#include <QObject>
#include <string>


class splash_screen : public QSplashScreen {

    Q_OBJECT

public:
    splash_screen(QWidget* parent);

};

#endif // INTERFACE_SPLASH_SCREEN_H
