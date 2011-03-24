#include <QtGui>
#include <QtSql>

#include "address.h"
#include "winkladr.h"

Address::Address(QWidget *parent) {
    ui.setupUi(this);
    connect(ui.btn_region, SIGNAL(clicked()), this, SLOT(choose_Region()));
    connect(ui.btn_subregion, SIGNAL(clicked()), this, SLOT(choose_Subregion()));
    connect(ui.btn_city, SIGNAL(clicked()), this, SLOT(choose_City()));
    connect(ui.btn_subcity, SIGNAL(clicked()), this, SLOT(choose_Subcity()));
    connect(ui.btn_street, SIGNAL(clicked()), this, SLOT(choose_Street()));

    code1 = 0; code2 = 0; code3 = 0; code4 = 0; code5 = 0;
}

void Address::choose_Region() {
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query;
    query.prepare("SELECT CODE, NAME FROM REGIONS ORDER BY CODE");
    if(!query.exec()){
        ShowErrorRecord(query);
        return;
    }
    model->setQuery(query);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->verticalHeader()->hide();
    tableView->setAlternatingRowColors(true);
    //tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);

    QDialog* dialog = new QDialog(this);
    QGridLayout* gridLayout = new QGridLayout(dialog);
    gridLayout->addWidget(tableView, 0, 0, 1, 1);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    dialog->exec();
    if (dialog->result() == QDialog::Accepted) {
        QItemSelectionModel* selmodel = qobject_cast<QItemSelectionModel*> (
                    tableView->selectionModel());
        if (!selmodel)
            return;
        if (selmodel->selectedIndexes().empty())
            return;

        //choose only one element
        QModelIndex index = selmodel->selectedIndexes().at(0);
        QSqlRecord rec = model->record(index.row());
        bool ok;
        code1 = rec.field("CODE").value().toInt(&ok);
        code = code1 * 100000000000000000000000; //23 - 0 code 25 digital
        QString name = rec.field("NAME").value().toString();
        ui.region->setText(name);
        ui.subregion->clear();
        ui.city->clear();
        ui.subcity->clear();
        ui.street->clear();
    }
}
void Address::choose_Subregion() {
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query;
    query.prepare("SELECT  CODE, CODE1, CODE2, NAME FROM KLADR WHERE (RTYPE = 2) AND (CODE1=:CODE1) ORDER BY NAME");
    query.bindValue(":CODE1",code1);
    if(!query.exec()){
        ShowErrorRecord(query);
        return;
    }
    model->setQuery(query);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->hideColumn(1);
    tableView->hideColumn(2);
    tableView->setAlternatingRowColors(true);
    //tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);

    QDialog* dialog = new QDialog(this);
    QGridLayout* gridLayout = new QGridLayout(dialog);
    gridLayout->addWidget(tableView, 0, 0, 1, 1);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel
                                  | QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    dialog->exec();
    if (dialog->result() == QDialog::Accepted) {
        QItemSelectionModel* selmodel = qobject_cast<QItemSelectionModel*> (
                    tableView->selectionModel());
        if (!selmodel)
            return;
        if (selmodel->selectedIndexes().empty())
            return;

        //choose only one element
        QModelIndex index = selmodel->selectedIndexes().at(0);
        QSqlRecord rec = model->record(index.row());
        bool ok;
        code = rec.field("CODE").value().toDouble(&ok);
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.subregion->setText(name);
        ui.city->clear();
        ui.subcity->clear();
        ui.street->clear();
    }
}
void Address::choose_City() {
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query("SELECT CODE, CODE1, CODE2, CODE3, NAME FROM KLADR WHERE (RTYPE = 3) AND (CODE1=:CODE1) AND (CODE2=:CODE2) ORDER BY NAME");
    query.bindValue(":CODE1",code1);
    query.bindValue(":CODE2",code2);
    if(!query.exec()){
        ShowErrorRecord(query);
        return;
    }
    model->setQuery(query);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->hideColumn(1);
    tableView->hideColumn(2);
    tableView->hideColumn(3);
    tableView->setAlternatingRowColors(true);
    //tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);

    QDialog* dialog = new QDialog(this);
    QGridLayout* gridLayout = new QGridLayout(dialog);
    gridLayout->addWidget(tableView, 0, 0, 1, 1);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel
                                  | QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    dialog->exec();
    if (dialog->result() == QDialog::Accepted) {
        QItemSelectionModel* selmodel = qobject_cast<QItemSelectionModel*> (
                    tableView->selectionModel());
        if (!selmodel)
            return;
        if (selmodel->selectedIndexes().empty())
            return;

        //choose only one element
        QModelIndex index = selmodel->selectedIndexes().at(0);
        QSqlRecord rec = model->record(index.row());
        bool ok;
        code = rec.field("CODE").value().toDouble(&ok);
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        code3 = rec.field("CODE3").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.city->setText(name);
        ui.subcity->clear();
        ui.street->clear();
    }
}

void Address::choose_Subcity() {
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query("SELECT  CODE, CODE1, CODE2, CODE3, CODE4, NAME FROM KLADR WHERE (RTYPE = 4) AND (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) ORDER BY NAME");
    query.bindValue(":CODE1",code1);
    query.bindValue(":CODE2",code2);
    query.bindValue(":CODE3",code3);
    if(!query.exec()){
        ShowErrorRecord(query);
        return;
    }
    model->setQuery(query);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->hideColumn(1);
    tableView->hideColumn(2);
    tableView->hideColumn(3);
    tableView->hideColumn(4);
    tableView->setAlternatingRowColors(true);
    //tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);

    QDialog* dialog = new QDialog(this);
    QGridLayout* gridLayout = new QGridLayout(dialog);
    gridLayout->addWidget(tableView, 0, 0, 1, 1);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel
                                  | QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    dialog->exec();
    if (dialog->result() == QDialog::Accepted) {
        QItemSelectionModel* selmodel = qobject_cast<QItemSelectionModel*> (
                    tableView->selectionModel());
        if (!selmodel)
            return;
        if (selmodel->selectedIndexes().empty())
            return;

        //choose only one element
        QModelIndex index = selmodel->selectedIndexes().at(0);
        QSqlRecord rec = model->record(index.row());
        bool ok;
        code = rec.field("CODE").value().toDouble(&ok);
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        code3 = rec.field("CODE3").value().toInt(&ok);
        code4 = rec.field("CODE4").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.subcity->setText(name);
        ui.street->clear();
    }
}

void Address::choose_Street() {
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query("SELECT  CODE, CODE1, CODE2, CODE3, CODE4, CODE5, NAME FROM KLADR WHERE (RTYPE = 5) AND (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) AND (CODE4=:CODE4) ORDER BY NAME");
    query.bindValue(":CODE1",code1);
    query.bindValue(":CODE2",code2);
    query.bindValue(":CODE3",code3);
    query.bindValue(":CODE4",code4);
    if(!query.exec()){
        ShowErrorRecord(query);
        return;
    }
    model->setQuery(query);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->hideColumn(1);
    tableView->hideColumn(2);
    tableView->hideColumn(3);
    tableView->hideColumn(4);
    tableView->hideColumn(5);
    tableView->setAlternatingRowColors(true);
    //tableView->horizontalHeader()->setResizeMode(QHeaderView::ResizeToContents);
    tableView->horizontalHeader()->setStretchLastSection(true);

    QDialog* dialog = new QDialog(this);
    QGridLayout* gridLayout = new QGridLayout(dialog);
    gridLayout->addWidget(tableView, 0, 0, 1, 1);

    QDialogButtonBox* buttonBox = new QDialogButtonBox(this);
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel
                                  | QDialogButtonBox::Ok);
    connect(buttonBox, SIGNAL(accepted()), dialog, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), dialog, SLOT(reject()));
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    dialog->exec();
    if (dialog->result() == QDialog::Accepted) {
        QItemSelectionModel* selmodel = qobject_cast<QItemSelectionModel*> (
                    tableView->selectionModel());
        if (!selmodel)
            return;
        if (selmodel->selectedIndexes().empty())
            return;

        //choose only one element
        QModelIndex index = selmodel->selectedIndexes().at(0);
        QSqlRecord rec = model->record(index.row());
        bool ok;
        code = rec.field("CODE").value().toDouble(&ok);
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        code3 = rec.field("CODE3").value().toInt(&ok);
        code4 = rec.field("CODE4").value().toInt(&ok);
        code5 = rec.field("CODE5").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.street->setText(name);
    }
}
