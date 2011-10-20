#ifndef ADDRESS_H
#define ADDRESS_H

#include <QtGui/QDialog>
#include "ui_address.h"

class Address : public QDialog
{
    Q_OBJECT

public:
    Address(QWidget *parent = 0, int codeset1=0, int codeset2=0, int codeset3=0, int codeset4=0, int codeset5=0);
    ~Address(){};

public slots:
    void choose_Region(int codeset=0);
    void choose_Subregion(int codeset=0);
    void choose_City(int codeset=0);
    void choose_Subcity(int codeset=0);
    void choose_Street(int codeset=0);
    void setPresentation();

private:

    qint64 code;
    int code1;
    int code2;
    int code3;
    int code4;
    int code5;
    QString rindex;

    Ui::AddressClass ui;
};

#endif // ADDRESS_H
