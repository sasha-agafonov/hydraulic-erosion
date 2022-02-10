#include <QApplication>
#include "interface_controller.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    interface_controller* main_menu = new interface_controller(NULL);

    QFile style_sheet("../terrain/style.qss");
    style_sheet.open(QFile::ReadOnly);
    app.setStyleSheet(style_sheet.readAll());

    main_menu -> resize(512, 712);
    main_menu -> show();

    app.exec();

    delete main_menu;

    return 0;
}
