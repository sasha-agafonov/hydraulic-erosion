#include <QApplication>
#include "interface_controller.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    interface_controller* main_menu = new interface_controller(NULL);

    // set a stylesheet
    QFile style_sheet("../terrain/style.qss");
    style_sheet.open(QFile::ReadOnly);
    app.setStyleSheet(style_sheet.readAll());

    main_menu -> setMinimumWidth(1080);
    main_menu -> setMinimumHeight(985);
    main_menu -> show();

    app.exec();

    delete main_menu;

    return 0;
}
