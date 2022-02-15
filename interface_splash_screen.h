#ifndef INTERFACE_SPLASH_SCREEN_H
#define INTERFACE_SPLASH_SCREEN_H

#include <QVBoxLayout>
#include <QSplashScreen>
#include <QPixmap>
#include <QObject>
#include <string>


class splash_screen : public QSplashScreen {

    Q_OBJECT

public:
    splash_screen(QWidget* parent);

    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    QVBoxLayout* v_box;
    //QLabel* text_label;

};

#endif // INTERFACE_SPLASH_SCREEN_H
