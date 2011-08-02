#ifndef ADDRESS_H
#define ADDRESS_H

#include <QtGui/QDialog>
#include "ui_address.h"

class Address : public QDialog
{
    Q_OBJECT

public:
    Address(QWidget *parent = 0);
    ~Address(){};

public slots:
    void choose_Region();
    void choose_Subregion();
    void choose_City();
    void choose_Subcity();
    void choose_Street();

private:
    qint64 code;
    int code1;
    int code2;
    int code3;
    int code4;
    int code5;

    Ui::AddressClass ui;
};

#endif // ADDRESS_H
