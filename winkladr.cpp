#include <QFileDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlQueryModel>

#include "winkladr.h"
#include "address.h"

//constructor
winkladr::winkladr(QWidget *parent) :
    QMainWindow(parent) {
    ui.setupUi(this);

    connect(ui.actionExit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui.actionLoad_form_DBF, SIGNAL(triggered()), this, SLOT(loadFromDBF()));
    connect(ui.actionInputAddress, SIGNAL(triggered()), this, SLOT(inputAddress()));

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("kladr.sqlite");

    if (!db.open()) {
        QSqlError err = db.lastError();
        QString errs = err.driverText();
        QMessageBox::warning(this, errs, err.text());
    } else {
        updateQuery();
        ui.tableView->setAlternatingRowColors(true);
        ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        //ui.tableView->horizontalHeader()->setStretchLastSection(true);
        //ui.tableView->horizontalHeader()->setResizeMode(0, QHeaderView::ResizeToContents);
    }
}

//update main window
void winkladr::updateQuery() {

    QSqlQueryModel* model = new QSqlQueryModel(this);
    QString strQuery = "SELECT * FROM KLADR";
    if( !strFind.isEmpty()) strQuery = strQuery + " WHERE KLADR.NAME LIKE '%"+strFind+"%'";
    model->setQuery(strQuery, db);
    ui.tableView->setModel(model);
}

//load form directiry with DBF(KLADR, STREET)
void winkladr::loadFromDBF() {

    QString dir = QFileDialog::getExistingDirectory(this, tr("Open DBF directory"));
    if (dir != "") {

        //load slow, but universal driver QODBC
        QSqlDatabase dbDBF = QSqlDatabase::addDatabase("QODBC", "dbDBF");
        //dbDBF.setDatabaseName("Driver={Microsoft dBASE Driver (*.dbf)};DriverID=277;Dbq="+ dir);
        dbDBF.setDatabaseName("DRIVER={Microsoft dBase Driver (*.dbf)};FIL={dBase IV;};DefaultDir="+ dir);
        if (!dbDBF.open()) {
            QSqlError err = dbDBF.lastError();
            QString errs = err.driverText();
            QMessageBox::warning(this, errs, err.text());
            return;
        }
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        QSqlDatabase::database().transaction();
        QSqlQuery queryInsert(db);
        queryInsert.clear();
        queryInsert.prepare("DROP TABLE KLADR");
        queryInsert.exec();
        QSqlDatabase::database().commit();
        queryInsert.prepare("CREATE TABLE KLADR(CODE TEXT, NAME TEXT, SOCR TEXT, RINDEX INTEGER, ALTNAME TEXT, RTYPE INTEGER, CODE1 INTEGER, CODE2 INTEGER, CODE3 INTEGER, CODE4 INTEGER, CODE5 INTEGER);");
        queryInsert.exec();
        QSqlDatabase::database().commit();
        queryInsert.clear();
        queryInsert.prepare("DROP TABLE REGIONS");
        queryInsert.exec();
        QSqlDatabase::database().commit();
        queryInsert.prepare("CREATE TABLE REGIONS(CODE TEXT, NAME TEXT, RINDEX INTEGER);");
        queryInsert.exec();
        QSqlDatabase::database().commit();

        QSqlDatabase::database().transaction();
        QSqlQuery query(dbDBF);
        query.clear();
        query.prepare("SELECT CODE, NAME, SOCR, INDEX FROM KLADR.DBF");
        int count = 1000;
        if (query.exec()) {
            while (query.next()) {
                if (count <= 0) {
                    QSqlDatabase::database().commit();
                    QSqlDatabase::database().transaction();
                    count = 1000;
                    QApplication::processEvents();
                }
                bool ok = insertStringFromDBF(query, queryInsert);
                if (!ok) break;
                count--;
            }
        }
        QSqlDatabase::database().commit();
        query.clear();
        query.prepare("SELECT CODE, NAME, SOCR, INDEX FROM STREET.DBF");
        count = 1000;
        if (query.exec()) {
            while (query.next()) {
                if (count <= 0) {
                    QSqlDatabase::database().commit();
                    QSqlDatabase::database().transaction();
                    count = 1000;
                    QApplication::processEvents();
                }
                bool ok = insertStringFromDBF(query, queryInsert);
                if (!ok) break;
                count--;
            }
        }
        QSqlDatabase::database().commit();
        dbDBF.close();
        updateQuery();
        QApplication::restoreOverrideCursor();
    }
}

//
inline bool winkladr::insertStringFromDBF(QSqlQuery& query, QSqlQuery& queryInsert) {
    QString strCode = query.value(0).toString();
    QString strCode1 = strCode.left(2);
    QString strCode2 = strCode.mid(2, 3);  //region
    QString strCode3 = strCode.mid(5, 3);  //city
    QString strCode4 = strCode.mid(8, 3);  //town
    QString strCode5 = strCode.mid(11, 4); //street
    //QString strCode6 = strCode.mid(15, 4); //bilding
    //QString strCode7 = strCode.mid(19, 4); //flat
    //QString strCode8 = strCode.mid(23, 2); //activity

    bool ok = true;
    //double code = strCode.toDouble(&ok);
    //if (!ok) code = 0;
    int code1 = strCode1.toInt(&ok, 10);
    if (!ok) code1 = 0;
    int code2 = strCode2.toInt(&ok, 10);
    if (!ok) code2 = 0;
    int code3 = strCode3.toInt(&ok, 10);
    if (!ok) code3 = 0;
    int code4 = strCode4.toInt(&ok, 10);
    if (!ok) code4 = 0;
    int code5 = strCode5.toInt(&ok, 10);
    if (!ok) code5 = 0;
    //int code6 = strCode6.toInt(&ok, 10);
    //if (!ok) code6 = 0;
    //int code7 = strCode7.toInt(&ok, 10);
    //if (!ok) code7 = 0;

    int type = 0;
    //if (code7 != 0) type = 7;
    //else if (code6 != 0) type = 6;
    if (code5 != 0) type = 5;
    else if (code4 != 0) type = 4;
    else if (code3 != 0) type = 3;
    else if (code2 != 0) type = 2;
    else if (code1 != 0) type = 1;

    //ignore last levels(bildings and flats) of kladr
    //if((type == 7) || (type == 6)) return true;

    QString name = query.value(1).toString();
    QString socr = query.value(2).toString();
    int intIndex = query.value(3).toInt(&ok);

    queryInsert.clear();
    queryInsert.prepare("INSERT INTO KLADR ( CODE, NAME, SOCR, RINDEX, ALTNAME, RTYPE, CODE1, CODE2, CODE3, CODE4, CODE5) VALUES(:CODE, :NAME, :SOCR, :RINDEX ,:ALTNAME, :RTYPE, :CODE1, :CODE2, :CODE3, :CODE4, :CODE5)");
    queryInsert.bindValue(":RTYPE", type);
    queryInsert.bindValue(":CODE1", code1);
    queryInsert.bindValue(":CODE2", code2);
    queryInsert.bindValue(":CODE3", code3);
    queryInsert.bindValue(":CODE4", code4);
    queryInsert.bindValue(":CODE5", code5);
    queryInsert.bindValue(":CODE", strCode);
    queryInsert.bindValue(":NAME", name);
    queryInsert.bindValue(":SOCR", socr);
    queryInsert.bindValue(":RINDEX", intIndex);
    queryInsert.bindValue(":ALTNAME", "");
    ok = queryInsert.exec();
    if (!ok) {
        ShowErrorRecord(queryInsert);
        return false;
    }

    if(type == 1){
      queryInsert.clear();
      queryInsert.prepare("INSERT INTO REGIONS( CODE, NAME, RINDEX) VALUES(:CODE, :NAME, :RINDEX)");
      queryInsert.bindValue(":CODE", strCode);
      queryInsert.bindValue(":NAME", name);
      queryInsert.bindValue(":RINDEX", intIndex);
      ok = queryInsert.exec();
      if (!ok) {
          ShowErrorRecord(queryInsert);
          return false;
      }
    }
    return true;
}

//show dialog to input address
void winkladr::inputAddress() {
    Address* dialog = new Address(this);
    dialog->setModal(true);
    dialog->show();
}


//show last sql error
void ShowErrorRecord(QSqlQuery& query) {
    QSqlError err = query.lastError();
    QApplication* app = qobject_cast<QApplication *> (qApp);
    if (app)
        QMessageBox::warning(app->activeWindow(), err.driverText(),
                             query.executedQuery() + ": " + err.text());
}

//find by pattern
void winkladr::on_lineFind_editingFinished()
{
    strFind = ui.lineFind->text();
    updateQuery();
}

//for TO DO
void winkladr::on_tableView_entered(const QModelIndex &index)
{
   //ViewAddress(index);
}

void winkladr::on_tableView_doubleClicked(const QModelIndex &index)
{
    ViewAddress(index);
}

void winkladr::ViewAddress(const QModelIndex &index)
{
    bool ok;

    QModelIndex  index_code = index.model()->index(index.row(), 6);
    int code1 = index.model()->data(index_code).toInt(&ok);
    index_code = index.model()->index(index.row(), 7);
    int code2 = index.model()->data(index_code).toInt(&ok);
    index_code = index.model()->index(index.row(), 8);
    int code3 = index.model()->data(index_code).toInt(&ok);
    index_code = index.model()->index(index.row(), 9);
    int code4 = index.model()->data(index_code).toInt(&ok);
    index_code = index.model()->index(index.row(), 10);
    int code5 = index.model()->data(index_code).toInt(&ok);

    Address* dialog = new Address(this, code1, code2, code3 ,code4,code5);
    dialog->setModal(true);
    dialog->show();

}
