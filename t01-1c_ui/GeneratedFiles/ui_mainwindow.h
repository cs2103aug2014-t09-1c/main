/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "clineedit.h"
#include "cmenubar.h"
#include "cprogressbar.h"
#include "ctable.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    CMenuBar *title;
    QPushButton *closeButton;
    QPushButton *minimiseButton;
    QGroupBox *terminalBox;
    QLabel *commandLabel;
    CLineEdit *lineEdit;
    QLabel *toDoLabel;
    CTable *tableWidget;
    CProgressBar *progressBar;
    QLabel *completedToday;
    QLabel *consoleOutput;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(750, 500);
        MainWindow->setStyleSheet(QLatin1String("MainWindow {border-image: url(:/Button/Resources/BORDER.png);}\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        title = new CMenuBar(centralWidget);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(0, 0, 750, 20));
        title->setMinimumSize(QSize(750, 20));
        title->setMaximumSize(QSize(750, 20));
        QFont font;
        font.setFamily(QStringLiteral("Segoe UI"));
        font.setPointSize(12);
        title->setFont(font);
        title->setAlignment(Qt::AlignCenter);
        closeButton = new QPushButton(centralWidget);
        closeButton->setObjectName(QStringLiteral("closeButton"));
        closeButton->setGeometry(QRect(720, 1, 29, 22));
        closeButton->setStyleSheet(QLatin1String("QPushButton          {border-image: url(:/Button/Resources/CLOSE_BUTTON.png); }\n"
"QPushButton:focus:pressed  { border-image: url(:/Button/Resources/CLOSE_BUTTON_PRESSED.png); }\n"
"QPushButton:hover    {border-image: url(:/Button/Resources/CLOSE_BUTTON_HOVER.png); }\n"
""));
        minimiseButton = new QPushButton(centralWidget);
        minimiseButton->setObjectName(QStringLiteral("minimiseButton"));
        minimiseButton->setGeometry(QRect(691, 1, 29, 22));
        minimiseButton->setStyleSheet(QLatin1String("QPushButton          {border-image: url(:/Button/Resources/MINIMISE_BUTTON.png); }\n"
"QPushButton:focus:pressed  { border-image: url(:/Button/Resources/MINIMISE_BUTTON_PRESSED.png); }\n"
"QPushButton:hover    {border-image: url(:/Button/Resources/MINIMISE_BUTTON_HOVER.png); }\n"
""));
        terminalBox = new QGroupBox(centralWidget);
        terminalBox->setObjectName(QStringLiteral("terminalBox"));
        terminalBox->setGeometry(QRect(20, 30, 711, 81));
        QFont font1;
        font1.setFamily(QStringLiteral("Segoe UI"));
        font1.setPointSize(18);
        terminalBox->setFont(font1);
        terminalBox->setStyleSheet(QLatin1String("QGroupBox {border:2px solid gray;}\n"
"QGroupBox::title { \n"
"     subcontrol-position: top left; /* position at the top left*/ \n"
"     padding:0 30px;\n"
" } "));
        commandLabel = new QLabel(terminalBox);
        commandLabel->setObjectName(QStringLiteral("commandLabel"));
        commandLabel->setGeometry(QRect(150, 10, 551, 21));
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI"));
        font2.setPointSize(14);
        commandLabel->setFont(font2);
        lineEdit = new CLineEdit(terminalBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(10, 37, 691, 36));
        lineEdit->setStyleSheet(QStringLiteral("QLineEdit {padding: 2px ; border-image: url(:/Button/Resources/BORDER_COMBO.png);}"));
        toDoLabel = new QLabel(centralWidget);
        toDoLabel->setObjectName(QStringLiteral("toDoLabel"));
        toDoLabel->setGeometry(QRect(53, 106, 171, 31));
        QFont font3;
        font3.setFamily(QStringLiteral("Segoe UI"));
        font3.setPointSize(17);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        toDoLabel->setFont(font3);
        toDoLabel->setStyleSheet(QStringLiteral("QLabel {color : black;}"));
        tableWidget = new CTable(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(20, 137, 711, 321));
        progressBar = new CProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(122, 470, 261, 20));
        QFont font4;
        font4.setFamily(QStringLiteral("Segoe UI"));
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setWeight(75);
        progressBar->setFont(font4);
        progressBar->setStyleSheet(QLatin1String("QProgressBar {\n"
"     border: 2px solid grey;\n"
"     border-radius: 5px;\n"
"     text-align: center;\n"
" }\n"
"\n"
" QProgressBar::chunk {\n"
"	background-color: rgb(146, 176, 240);\n"
" }"));
        progressBar->setValue(24);
        completedToday = new QLabel(centralWidget);
        completedToday->setObjectName(QStringLiteral("completedToday"));
        completedToday->setGeometry(QRect(10, 471, 111, 16));
        QFont font5;
        font5.setFamily(QStringLiteral("Segoe UI"));
        font5.setPointSize(10);
        completedToday->setFont(font5);
        consoleOutput = new QLabel(centralWidget);
        consoleOutput->setObjectName(QStringLiteral("consoleOutput"));
        consoleOutput->setGeometry(QRect(390, 469, 351, 21));
        consoleOutput->setFont(font);
        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(lineEdit, tableWidget);
        QWidget::setTabOrder(tableWidget, minimiseButton);
        QWidget::setTabOrder(minimiseButton, closeButton);

        retranslateUi(MainWindow);
        QObject::connect(closeButton, SIGNAL(clicked()), MainWindow, SLOT(close()));
        QObject::connect(minimiseButton, SIGNAL(clicked()), MainWindow, SLOT(showMinimized()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        title->setText(QApplication::translate("MainWindow", "T09-1c", 0));
        closeButton->setText(QString());
        minimiseButton->setText(QString());
        terminalBox->setTitle(QApplication::translate("MainWindow", "Terminal", 0));
        commandLabel->setText(QString());
        toDoLabel->setText(QApplication::translate("MainWindow", "My To-Do List : ", 0));
        completedToday->setText(QApplication::translate("MainWindow", "Completed Today :", 0));
        consoleOutput->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
