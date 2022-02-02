#include <QApplication>
#include "interface.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    interface* main_menu = new interface(NULL);

    main_menu -> setStyleSheet("background: rgba(40, 44, 52, 1);");
    main_menu -> resize(512, 712);
    main_menu -> show();

    app.exec();

    delete main_menu;

    return 0;
}
