/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_start;
    QPushButton *pushButton_loadingLastGame;
    QPushButton *pushButton_settingBackgroupPicture;
    QPushButton *pushButton_voiceEffect;
    QPushButton *pushButton_setting;
    QPushButton *pushButton_help;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName(QString::fromUtf8("StartWindow"));
        StartWindow->resize(1113, 863);
        centralwidget = new QWidget(StartWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(380, 310, 311, 331));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_start = new QPushButton(verticalLayoutWidget);
        pushButton_start->setObjectName(QString::fromUtf8("pushButton_start"));

        verticalLayout->addWidget(pushButton_start);

        pushButton_loadingLastGame = new QPushButton(verticalLayoutWidget);
        pushButton_loadingLastGame->setObjectName(QString::fromUtf8("pushButton_loadingLastGame"));

        verticalLayout->addWidget(pushButton_loadingLastGame);

        pushButton_settingBackgroupPicture = new QPushButton(verticalLayoutWidget);
        pushButton_settingBackgroupPicture->setObjectName(QString::fromUtf8("pushButton_settingBackgroupPicture"));

        verticalLayout->addWidget(pushButton_settingBackgroupPicture);

        pushButton_voiceEffect = new QPushButton(verticalLayoutWidget);
        pushButton_voiceEffect->setObjectName(QString::fromUtf8("pushButton_voiceEffect"));

        verticalLayout->addWidget(pushButton_voiceEffect);

        pushButton_setting = new QPushButton(verticalLayoutWidget);
        pushButton_setting->setObjectName(QString::fromUtf8("pushButton_setting"));

        verticalLayout->addWidget(pushButton_setting);

        pushButton_help = new QPushButton(verticalLayoutWidget);
        pushButton_help->setObjectName(QString::fromUtf8("pushButton_help"));

        verticalLayout->addWidget(pushButton_help);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(380, 170, 281, 111));
        QFont font;
        font.setPointSize(33);
        font.setBold(true);
        font.setItalic(true);
        font.setKerning(true);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);
        StartWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1113, 27));
        StartWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(StartWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        StartWindow->setStatusBar(statusbar);

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QMainWindow *StartWindow)
    {
        StartWindow->setWindowTitle(QCoreApplication::translate("StartWindow", "MainWindow", nullptr));
        pushButton_start->setText(QCoreApplication::translate("StartWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton_loadingLastGame->setText(QCoreApplication::translate("StartWindow", "\345\212\240\350\275\275\344\270\212\344\270\200\345\261\200\346\270\270\346\210\217", nullptr));
        pushButton_settingBackgroupPicture->setText(QCoreApplication::translate("StartWindow", "\350\256\276\347\275\256\350\203\214\346\231\257\345\233\276\347\211\207", nullptr));
        pushButton_voiceEffect->setText(QCoreApplication::translate("StartWindow", "\351\237\263\346\225\210", nullptr));
        pushButton_setting->setText(QCoreApplication::translate("StartWindow", "\350\256\276\347\275\256", nullptr));
        pushButton_help->setText(QCoreApplication::translate("StartWindow", "\345\270\256\345\212\251", nullptr));
        label->setText(QCoreApplication::translate("StartWindow", "\344\270\255\345\233\275\350\261\241\346\243\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
