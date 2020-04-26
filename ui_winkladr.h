/********************************************************************************
** Form generated from reading UI file 'winkladr.ui'
**
** Created: Thu 20. Oct 10:26:00 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINKLADR_H
#define UI_WINKLADR_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QGridLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>
#include <QTableView>
#include <QWidget>

QT_BEGIN_NAMESPACE

class Ui_winkladrClass
{
public:
    QAction *actionExit;
    QAction *actionLoad_form_DBF;
    QAction *actionInputAddress;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QGroupBox *groupBoxFind;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineFind;
    QTableView *tableView;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuTest;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *winkladrClass)
    {
        if (winkladrClass->objectName().isEmpty())
            winkladrClass->setObjectName(QString::fromUtf8("winkladrClass"));
        winkladrClass->resize(800, 600);
        actionExit = new QAction(winkladrClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionLoad_form_DBF = new QAction(winkladrClass);
        actionLoad_form_DBF->setObjectName(QString::fromUtf8("actionLoad_form_DBF"));
        actionInputAddress = new QAction(winkladrClass);
        actionInputAddress->setObjectName(QString::fromUtf8("actionInputAddress"));
        centralwidget = new QWidget(winkladrClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        groupBoxFind = new QGroupBox(centralwidget);
        groupBoxFind->setObjectName(QString::fromUtf8("groupBoxFind"));
        groupBoxFind->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBoxFind->sizePolicy().hasHeightForWidth());
        groupBoxFind->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(groupBoxFind);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(groupBoxFind);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(label);

        lineFind = new QLineEdit(groupBoxFind);
        lineFind->setObjectName(QString::fromUtf8("lineFind"));

        horizontalLayout->addWidget(lineFind);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBoxFind, 0, 0, 1, 1);

        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));

        gridLayout_2->addWidget(tableView, 1, 0, 1, 1);

        winkladrClass->setCentralWidget(centralwidget);
        menubar = new QMenuBar(winkladrClass);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTest = new QMenu(menubar);
        menuTest->setObjectName(QString::fromUtf8("menuTest"));
        winkladrClass->setMenuBar(menubar);
        statusbar = new QStatusBar(winkladrClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        winkladrClass->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuTest->menuAction());
        menuFile->addAction(actionLoad_form_DBF);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTest->addAction(actionInputAddress);

        retranslateUi(winkladrClass);

        QMetaObject::connectSlotsByName(winkladrClass);
    } // setupUi

    void retranslateUi(QMainWindow *winkladrClass)
    {
        winkladrClass->setWindowTitle(QApplication::translate("winkladrClass", "\320\240\320\276\321\201\321\201\320\270\320\271\321\201\320\272\320\270\320\271 \320\260\320\264\321\200\320\265\321\201\320\275\321\213\320\271 \321\201\320\277\321\200\320\260\320\262\320\276\321\207\320\275\320\270\320\272", 0));
        actionExit->setText(QApplication::translate("winkladrClass", "\320\222\321\213\321\205\320\276\320\264", 0));
        actionLoad_form_DBF->setText(QApplication::translate("winkladrClass", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\270\320\267  DBF...", 0));
        actionInputAddress->setText(QApplication::translate("winkladrClass", "\320\222\320\262\320\276\320\264 \320\260\320\264\321\200\320\265\321\201\320\260", 0 ));
        groupBoxFind->setTitle(QString());
        label->setText(QApplication::translate("winkladrClass", "\320\235\320\260\320\271\321\202\320\270:", 0));
        menuFile->setTitle(QApplication::translate("winkladrClass", "\320\244\320\260\320\271\320\273", 0));
        menuTest->setTitle(QApplication::translate("winkladrClass", "\320\237\321\200\320\276\320\262\320\265\321\200\320\272\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class winkladrClass: public Ui_winkladrClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINKLADR_H
