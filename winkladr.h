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

private slots:
    void on_lineFind_editingFinished();
    void on_tableView_entered(const QModelIndex &index);
    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::winkladrClass ui;
    QSqlDatabase db;

    QString strFind;

    bool insertStringFromDBF(QSqlQuery& query);
    void ViewAddress(const QModelIndex &index);
};

#endif // WINKLADR_H

void ShowErrorRecord(QSqlQuery& query);
