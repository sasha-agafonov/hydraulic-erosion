#ifndef GENERATION_MENU_H
#define GENERATION_MENU_H

#include <QWidget>
#include <QGridLayout>
#include <QObject>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
#include <QComboBox>


class generation_menu : public QWidget {

    Q_OBJECT

public:
    generation_menu(QWidget *parent);

    QGridLayout* grid;
    QSlider* persistence_slider;
    QLabel* persistence_label;

    QPushButton* paramgen_button;
    QPushButton* randgen_button;

};

#endif // GENERATION_MENU_H
