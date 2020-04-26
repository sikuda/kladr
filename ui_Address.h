/********************************************************************************
** Form generated from reading UI file 'Address.ui'
**
** Created: Thu 20. Oct 10:18:52 2011
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDRESS_H
#define UI_ADDRESS_H

#include <QVariant>
#include <QAction>
#include <QApplication>
#include <QButtonGroup>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_AddressClass
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *index;
    QLabel *label_2;
    QLineEdit *region;
    QLabel *label_3;
    QLineEdit *subregion;
    QLabel *label_4;
    QLineEdit *city;
    QLabel *label_5;
    QLineEdit *subcity;
    QLabel *label_6;
    QLineEdit *street;
    QComboBox *cmb_house;
    QLineEdit *house;
    QComboBox *cmb_building;
    QLineEdit *building;
    QComboBox *cmb_flat;
    QLineEdit *flat;
    QLabel *label_8;
    QTextEdit *fullAddress;
    QLabel *label_7;
    QLineEdit *comment;
    QDialogButtonBox *buttonBox;
    QPushButton *btn_region;
    QPushButton *btn_subregion;
    QPushButton *btn_city;
    QPushButton *btn_subcity;
    QPushButton *btn_street;

    void setupUi(QDialog *AddressClass)
    {
        if (AddressClass->objectName().isEmpty())
            AddressClass->setObjectName(QString::fromUtf8("AddressClass"));
        AddressClass->resize(531, 335);
        gridLayout = new QGridLayout(AddressClass);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(AddressClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        index = new QLineEdit(AddressClass);
        index->setObjectName(QString::fromUtf8("index"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(index->sizePolicy().hasHeightForWidth());
        index->setSizePolicy(sizePolicy);
        index->setMaximumSize(QSize(120, 20));

        gridLayout->addWidget(index, 0, 1, 1, 5);

        label_2 = new QLabel(AddressClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        region = new QLineEdit(AddressClass);
        region->setObjectName(QString::fromUtf8("region"));

        gridLayout->addWidget(region, 1, 1, 1, 8);

        label_3 = new QLabel(AddressClass);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        subregion = new QLineEdit(AddressClass);
        subregion->setObjectName(QString::fromUtf8("subregion"));

        gridLayout->addWidget(subregion, 2, 1, 1, 8);

        label_4 = new QLabel(AddressClass);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        city = new QLineEdit(AddressClass);
        city->setObjectName(QString::fromUtf8("city"));

        gridLayout->addWidget(city, 3, 1, 1, 8);

        label_5 = new QLabel(AddressClass);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 4);

        subcity = new QLineEdit(AddressClass);
        subcity->setObjectName(QString::fromUtf8("subcity"));

        gridLayout->addWidget(subcity, 4, 4, 1, 5);

        label_6 = new QLabel(AddressClass);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        street = new QLineEdit(AddressClass);
        street->setObjectName(QString::fromUtf8("street"));

        gridLayout->addWidget(street, 5, 1, 1, 8);

        cmb_house = new QComboBox(AddressClass);
        cmb_house->setObjectName(QString::fromUtf8("cmb_house"));

        gridLayout->addWidget(cmb_house, 6, 0, 1, 2);

        house = new QLineEdit(AddressClass);
        house->setObjectName(QString::fromUtf8("house"));

        gridLayout->addWidget(house, 6, 2, 1, 3);

        cmb_building = new QComboBox(AddressClass);
        cmb_building->setObjectName(QString::fromUtf8("cmb_building"));

        gridLayout->addWidget(cmb_building, 6, 5, 1, 1);

        building = new QLineEdit(AddressClass);
        building->setObjectName(QString::fromUtf8("building"));

        gridLayout->addWidget(building, 6, 6, 1, 1);

        cmb_flat = new QComboBox(AddressClass);
        cmb_flat->setObjectName(QString::fromUtf8("cmb_flat"));

        gridLayout->addWidget(cmb_flat, 6, 7, 1, 1);

        flat = new QLineEdit(AddressClass);
        flat->setObjectName(QString::fromUtf8("flat"));

        gridLayout->addWidget(flat, 6, 8, 1, 2);

        label_8 = new QLabel(AddressClass);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 7, 0, 1, 3);

        fullAddress = new QTextEdit(AddressClass);
        fullAddress->setObjectName(QString::fromUtf8("fullAddress"));

        gridLayout->addWidget(fullAddress, 7, 3, 1, 7);

        label_7 = new QLabel(AddressClass);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 8, 0, 1, 3);

        comment = new QLineEdit(AddressClass);
        comment->setObjectName(QString::fromUtf8("comment"));

        gridLayout->addWidget(comment, 8, 3, 1, 7);

        buttonBox = new QDialogButtonBox(AddressClass);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 9, 0, 1, 10);

        btn_region = new QPushButton(AddressClass);
        btn_region->setObjectName(QString::fromUtf8("btn_region"));
        btn_region->setMaximumSize(QSize(30, 20));

        gridLayout->addWidget(btn_region, 1, 9, 1, 1);

        btn_subregion = new QPushButton(AddressClass);
        btn_subregion->setObjectName(QString::fromUtf8("btn_subregion"));
        btn_subregion->setMaximumSize(QSize(30, 20));

        gridLayout->addWidget(btn_subregion, 2, 9, 1, 1);

        btn_city = new QPushButton(AddressClass);
        btn_city->setObjectName(QString::fromUtf8("btn_city"));
        btn_city->setMaximumSize(QSize(30, 20));

        gridLayout->addWidget(btn_city, 3, 9, 1, 1);

        btn_subcity = new QPushButton(AddressClass);
        btn_subcity->setObjectName(QString::fromUtf8("btn_subcity"));
        btn_subcity->setMaximumSize(QSize(30, 20));

        gridLayout->addWidget(btn_subcity, 4, 9, 1, 1);

        btn_street = new QPushButton(AddressClass);
        btn_street->setObjectName(QString::fromUtf8("btn_street"));
        btn_street->setMaximumSize(QSize(30, 20));

        gridLayout->addWidget(btn_street, 5, 9, 1, 1);


        retranslateUi(AddressClass);
        QObject::connect(buttonBox, SIGNAL(accepted()), AddressClass, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), AddressClass, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddressClass);
    } // setupUi

    void retranslateUi(QDialog *AddressClass)
    {
        AddressClass->setWindowTitle(QApplication::translate("AddressClass", "\320\222\320\262\320\276\320\264 \320\260\320\264\321\200\320\265\321\201\320\260", 0));
        label->setText(QApplication::translate("AddressClass", "\320\230\320\275\320\264\320\265\320\272\321\201", 0));
        label_2->setText(QApplication::translate("AddressClass", "\320\240\320\265\320\263\320\270\320\276\320\275", 0));
        label_3->setText(QApplication::translate("AddressClass", "\320\240\320\260\320\271\320\276\320\275", 0));
        label_4->setText(QApplication::translate("AddressClass", "\320\223\320\276\321\200\320\276\320\264", 0));
        label_5->setText(QApplication::translate("AddressClass", "\320\235\320\260\321\201\320\265\320\273\320\265\320\275\320\275\321\213\320\271 \320\277\321\203\320\275\320\272\321\202", 0));
        label_6->setText(QApplication::translate("AddressClass", "\320\243\320\273\320\270\321\206\320\260", 0));
        cmb_house->clear();
        cmb_house->insertItems(0, QStringList()
         << QApplication::translate("AddressClass", "\320\264\320\276\320\274", 0)
         << QApplication::translate("AddressClass", "\320\262\320\273\320\260\320\264\320\265\320\275\320\270\320\265", 0)
        );
        cmb_building->clear();
        cmb_building->insertItems(0, QStringList()
         << QApplication::translate("AddressClass", "\320\272\320\276\321\200\320\277\321\203\321\201", 0)
         << QApplication::translate("AddressClass", "\321\201\321\202\321\200\320\276\320\265\320\275\320\270\320\265", 0)
        );
        cmb_flat->clear();
        cmb_flat->insertItems(0, QStringList()
         << QApplication::translate("AddressClass", "\320\272\320\262.", 0)
         << QApplication::translate("AddressClass", "\320\276\321\204.", 0)
        );
        label_8->setText(QApplication::translate("AddressClass", "\320\237\321\200\320\265\320\264\321\201\321\202\320\260\320\262\320\273\320\265\320\275\320\270\320\265", 0));
        label_7->setText(QApplication::translate("AddressClass", "\320\232\320\276\320\274\320\274\320\265\320\275\321\202\320\260\321\200\320\270\320\271", 0));
        btn_region->setText(QApplication::translate("AddressClass", "...", 0));
        btn_subregion->setText(QApplication::translate("AddressClass", "...", 0));
        btn_city->setText(QApplication::translate("AddressClass", "...", 0));
        btn_subcity->setText(QApplication::translate("AddressClass", "...", 0));
        btn_street->setText(QApplication::translate("AddressClass", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class AddressClass: public Ui_AddressClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDRESS_H
