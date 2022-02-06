#include "loading_menu.h"

loading_menu :: loading_menu(QWidget *parent) : QWidget(parent) {

    loading_label = new QLabel(this);
    loading_label  -> setText("Generating Terrain...");
    loading_label  -> setStyleSheet("QLabel { color: rgba(190, 190, 222, 1); margin-right: 6px; }");

}
