#ifndef LOADING_MENU_H
#define LOADING_MENU_H

#include <QWidget>
#include <QObject>
#include <QLabel>

class loading_menu : public QWidget {

    Q_OBJECT

public:
    loading_menu(QWidget *parent);

        QLabel* loading_label;
};

#endif // LOADING_MENU_H
