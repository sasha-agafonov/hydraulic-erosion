/********************************************************************************
** Form generated from reading UI file 'main.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_main
{
public:
    QWidget *centralwidget;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *main)
    {
        if (main->objectName().isEmpty())
            main->setObjectName(QString::fromUtf8("main"));
        main->resize(800, 600);
        centralwidget = new QWidget(main);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        main->setCentralWidget(centralwidget);
        menubar = new QMenuBar(main);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        main->setMenuBar(menubar);
        statusbar = new QStatusBar(main);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        main->setStatusBar(statusbar);

        retranslateUi(main);

        QMetaObject::connectSlotsByName(main);
    } // setupUi

    void retranslateUi(QMainWindow *main)
    {
        main->setWindowTitle(QCoreApplication::translate("main", "main", nullptr));
    } // retranslateUi

};

namespace Ui {
    class main: public Ui_main {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
