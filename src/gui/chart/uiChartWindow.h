/********************************************************************************
** Form generated from reading UI file 'uiChartWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UICHARTWINDOW_H
#define UICHARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChartWindow
{
public:
    QAction *actioncsv;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menusave;
    QMenu *menuexportar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ChartWindow)
    {
        if (ChartWindow->objectName().isEmpty())
            ChartWindow->setObjectName(QStringLiteral("ChartWindow"));
        ChartWindow->resize(498, 322);
        actioncsv = new QAction(ChartWindow);
        actioncsv->setObjectName(QStringLiteral("actioncsv"));
        centralwidget = new QWidget(ChartWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        ChartWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ChartWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 498, 24));
        menusave = new QMenu(menubar);
        menusave->setObjectName(QStringLiteral("menusave"));
        menuexportar = new QMenu(menusave);
        menuexportar->setObjectName(QStringLiteral("menuexportar"));
        ChartWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ChartWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ChartWindow->setStatusBar(statusbar);

        menubar->addAction(menusave->menuAction());
        menusave->addAction(menuexportar->menuAction());
        menuexportar->addAction(actioncsv);

        retranslateUi(ChartWindow);

        QMetaObject::connectSlotsByName(ChartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ChartWindow)
    {
        ChartWindow->setWindowTitle(QApplication::translate("ChartWindow", "ChartWindow", nullptr));
        actioncsv->setText(QApplication::translate("ChartWindow", "CSV", nullptr));
        menusave->setTitle(QApplication::translate("ChartWindow", "Arquivo", nullptr));
        menuexportar->setTitle(QApplication::translate("ChartWindow", "Exportar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChartWindow: public Ui_ChartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UICHARTWINDOW_H
