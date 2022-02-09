#ifndef SPLASH_SCREEN_H
#define SPLASH_SCREEN_H

#include <QSplashScreen>
#include <QPixmap>
#include <QObject>
#include <string>


class splash_screen : public QSplashScreen {

    Q_OBJECT

public:
    splash_screen(const QPixmap* pix);

        std :: string stage;

public slots:
    //void update_progress(int progress);
    void update_stage();



//    QSplashScreen* splash;

};

#endif // SPLASH_SCREEN_H
