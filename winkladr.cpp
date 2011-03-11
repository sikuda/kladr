#include <QtGui>
#include <QtSql>

#include "winkladr.h"
#include "address.h"

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
        ui.tableView->setAlternatingRowColors(true);
        ui.tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
        updateQuery();
    }
}

void winkladr::updateQuery() {

    QSqlQueryModel* model = new QSqlQueryModel(this);
    model->setQuery("SELECT * FROM KLADR", db);
    ui.tableView->setModel(model);
}

void winkladr::loadFromDBF() {

    QString dir = QFileDialog::getExistingDirectory(this, tr(
                                                        "Open DBF directory"));
    if (dir != "") {

        QSqlDatabase dbDBF = QSqlDatabase::addDatabase("QODBC", "dbDBF");
        dbDBF.setDatabaseName("DRIVER={Microsoft dBase Driver (*.dbf)};FIL={dBase IV;};DefaultDir="+ dir);
        if (!dbDBF.open()) {
            QSqlError err = dbDBF.lastError();
            QString errs = err.driverText();
            QMessageBox::warning(this, errs, err.text());
            return;
        }
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        QSqlDatabase::database().transaction();
        QSqlQuery queryInsert1(db);
        queryInsert1.prepare("DELETE FROM KLADR");
        queryInsert1.exec();
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
                }
                bool ok = insertStringFromDBF(query);
                QApplication::processEvents();
                if (!ok) break;
                //count--;
            }
        }

        query.clear();
        query.prepare("SELECT CODE, NAME, SOCR, INDEX FROM STREET.DBF");
        count = 1000;
        if (query.exec()) {
            while (query.next()) {
                if (count <= 0) {
                    QSqlDatabase::database().commit();
                    QSqlDatabase::database().transaction();
                    count = 1000;
                }
                bool ok = insertStringFromDBF(query,5);
                QApplication::processEvents();
                if (!ok) break;
                count--;
            }
        }

        query.clear();
        query.prepare("SELECT CODE, NAME, SOCR, INDEX FROM DOMA.DBF");
        count = 1000;
        if (query.exec()) {
            while (query.next()) {
                if (count <= 0) {
                    QSqlDatabase::database().commit();
                    QSqlDatabase::database().transaction();
                    count = 1000;
                }
                bool ok = insertStringFromDBF(query,6);
                QApplication::processEvents();
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

bool winkladr::insertStringFromDBF(QSqlQuery& query, int newtype) {
    QString strCode = query.value(0).toString();
    QString strCode1 = strCode.left(2);
    QString strCode2 = strCode.mid(2, 3);  //region
    QString strCode3 = strCode.mid(5, 3);  //city
    QString strCode4 = strCode.mid(8, 3);  //town
    QString strCode5 = strCode.mid(11, 4); //street
    QString strCode6 = strCode.mid(15, 4); //bilding
    QString strCode7 = strCode.mid(19, 4); //flat
    QString strCode8 = strCode.mid(23, 2); //activity

    bool ok;
    quint64 code = strCode.toLongLong(&ok, 10);
    if (!ok) code = 0;
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
    int code6 = strCode6.toInt(&ok, 10);
    if (!ok) code6 = 0;
    int code7 = strCode7.toInt(&ok, 10);
    if (!ok) code7 = 0;

    int type = 0;
    if (code7 != 0) type = 7;
    else if (code6 != 0) type = 6;
    else if (code5 != 0) type = 5;
    else if (code4 != 0) type = 4;
    else if (code3 != 0) type = 3;
    else if (code2 != 0) type = 2;
    else if (code1 != 0) type = 1;

    QString name = query.value(1).toString();
    QString socr = query.value(2).toString();
    int intIndex = query.value(3).toInt(&ok);

    QSqlQuery queryInsert(db);
    queryInsert.clear();
    queryInsert.prepare("INSERT INTO KLADR ( CODE, NAME, SOCR, RINDEX, ALTNAME, RTYPE, CODE1, CODE2, CODE3, CODE4, CODE5) VALUES(:CODE, :NAME, :SOCR, :RINDEX ,:ALTNAME, :RTYPE, :CODE1, :CODE2, :CODE3, :CODE4, :CODE5)");
    queryInsert.bindValue(":RTYPE", type);
    queryInsert.bindValue(":CODE1", code1);
    queryInsert.bindValue(":CODE2", code2);
    queryInsert.bindValue(":CODE3", code3);
    queryInsert.bindValue(":CODE4", code4);
    queryInsert.bindValue(":CODE5", code5);
    queryInsert.bindValue(":CODE", code);
    queryInsert.bindValue(":NAME", name);
    queryInsert.bindValue(":SOCR", socr);
    queryInsert.bindValue(":RINDEX", intIndex);
    queryInsert.bindValue(":ALTNAME", "");
    ok = queryInsert.exec();
    if (!ok) {
        ShowErrorRecord(queryInsert);
        return false;
    }
    return true;
}

void winkladr::inputAddress() {
    Address* dialog = new Address(this);
    dialog->setModal(true);
    dialog->show();
}

//
// Show last sql error
//
void ShowErrorRecord(QSqlQuery& query) {
    QSqlError err = query.lastError();
    QApplication* app = qobject_cast<QApplication *> (qApp);
    if (app)
        QMessageBox::warning(app->activeWindow(), err.driverText(),
                             query.executedQuery() + ": " + err.text());
}

