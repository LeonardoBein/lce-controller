/********************************************************************************
** Form generated from reading UI file 'uiMainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionexit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QSpinBox *start_freq;
    QSpinBox *stop_freq;
    QSpinBox *step_angle;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *startButton;
    QPushButton *resetButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(530, 340);
        MainWindow->setMinimumSize(QSize(530, 340));
        MainWindow->setMaximumSize(QSize(730, 540));
        actionexit = new QAction(MainWindow);
        actionexit->setObjectName(QStringLiteral("actionexit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(200, 200));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 90, 67, 19));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 30, 67, 19));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 150, 81, 19));
        start_freq = new QSpinBox(groupBox);
        start_freq->setObjectName(QStringLiteral("start_freq"));
        start_freq->setGeometry(QRect(10, 50, 111, 28));
        start_freq->setMaximum(300000);
        stop_freq = new QSpinBox(groupBox);
        stop_freq->setObjectName(QStringLiteral("stop_freq"));
        stop_freq->setGeometry(QRect(10, 110, 111, 28));
        stop_freq->setMaximum(300000);
        step_angle = new QSpinBox(groupBox);
        step_angle->setObjectName(QStringLiteral("step_angle"));
        step_angle->setGeometry(QRect(10, 170, 111, 28));
        step_angle->setMaximum(360);
        step_angle->setValue(45);

        verticalLayout_4->addWidget(groupBox);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_2->setContentsMargins(0, 0, -1, -1);
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        progressBar = new QProgressBar(groupBox_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 40, 231, 23));
        progressBar->setValue(24);

        verticalLayout_2->addWidget(groupBox_2);


        horizontalLayout->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        startButton = new QPushButton(centralWidget);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setMinimumSize(QSize(0, 0));
        startButton->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_3->addWidget(startButton);

        resetButton = new QPushButton(centralWidget);
        resetButton->setObjectName(QStringLiteral("resetButton"));

        horizontalLayout_3->addWidget(resetButton);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 530, 24));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Emissao Radiada", nullptr));
        actionexit->setText(QApplication::translate("MainWindow", "exit", nullptr));
        groupBox->setTitle(QApplication::translate("MainWindow", "Config", nullptr));
        label->setText(QApplication::translate("MainWindow", "Stop Freq", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Start Freq", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Step Angle", nullptr));
        start_freq->setSuffix(QApplication::translate("MainWindow", " Hz", nullptr));
        start_freq->setPrefix(QString());
        stop_freq->setSuffix(QApplication::translate("MainWindow", " Hz", nullptr));
        step_angle->setSuffix(QApplication::translate("MainWindow", "\302\272", nullptr));
        step_angle->setPrefix(QString());
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Progress", nullptr));
        startButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        resetButton->setText(QApplication::translate("MainWindow", "Reset", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UIMAINWINDOW_H
