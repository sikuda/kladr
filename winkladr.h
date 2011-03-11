#ifndef WINKLADR_H
#define WINKLADR_H

#include <QtGui/QMainWindow>
#include <QtSql/QSqlQuery>
#include "ui_winkladr.h"

class winkladr : public QMainWindow
{
    Q_OBJECT

public:
    winkladr(QWidget *parent = 0);
    ~winkladr(){db.close();};

public slots:
    void updateQuery();
	void loadFromDBF();
	void inputAddress();

private:
    Ui::winkladrClass ui;
    QSqlDatabase db;

    bool insertStringFromDBF(QSqlQuery& query, int newtype = 0);
};

#endif // WINKLADR_H

void ShowErrorRecord(QSqlQuery& query);
