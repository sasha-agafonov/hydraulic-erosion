#include <QApplication>
#include "interface_controller.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    interface_controller* main_menu = new interface_controller(NULL);

    main_menu -> setStyleSheet("background: rgba(40, 44, 52, 1);");
    main_menu -> resize(512, 712);
    main_menu -> show();

    app.exec();

    delete main_menu;

    return 0;
}
