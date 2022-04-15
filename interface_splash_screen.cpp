#include "interface_splash_screen.h"
#include <QApplication>
#include <QColor>
#include <QMovie>
#include <QLabel>

splash_screen :: splash_screen(QWidget* parent) {

    v_box = new QVBoxLayout(this);
    v_box -> setAlignment(Qt:: AlignHCenter | Qt:: AlignVCenter);

    QMovie *movie = new QMovie("../terrain/ringer.gif");
    QLabel *label = new QLabel(this);
    label -> setStyleSheet("QLabel { background-color: rgba(1,1,1,0); } ");
    label -> setMovie(movie);

    QLabel* message_label = new QLabel("Building Terrain...", this);
    message_label -> setAlignment(Qt::AlignHCenter);
    message_label -> setStyleSheet("QLabel { background-color: rgba(1,1,1,0); margin-top: 15px;} ");

    v_box -> addWidget(label);
    v_box -> addWidget(message_label);

    movie -> start();

}

void splash_screen :: mousePressEvent(QMouseEvent* event) { return; }

void splash_screen :: keyPressEvent(QKeyEvent* event) { return; }
