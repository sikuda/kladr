#include <QtGui>
#include <QtSql>

#include "address.h"
#include "winkladr.h"

//constructor
Address::Address(QWidget *parent,  int codeset1, int codeset2, int codeset3, int codeset4, int codeset5) {

    ui.setupUi(this);
    connect(ui.btn_region, SIGNAL(clicked()), this, SLOT(choose_Region()));
    connect(ui.btn_subregion, SIGNAL(clicked()), this, SLOT(choose_Subregion()));
    connect(ui.btn_city, SIGNAL(clicked()), this, SLOT(choose_City()));
    connect(ui.btn_subcity, SIGNAL(clicked()), this, SLOT(choose_Subcity()));
    connect(ui.btn_street, SIGNAL(clicked()), this, SLOT(choose_Street()));
    connect(ui.house, SIGNAL(editingFinished()), this, SLOT(setPresentation()));
    connect(ui.building, SIGNAL(editingFinished()), this, SLOT(setPresentation()));
    connect(ui.flat, SIGNAL(editingFinished()), this, SLOT(setPresentation()));

    code1 = codeset1; code2 = codeset2; code3 = codeset3; code4 = codeset4; code5 = codeset5;

    if(code1!=0){
        QSqlQuery query;
        query.prepare("SELECT  CODE1, CODE2, CODE3, CODE4, CODE5, NAME, RINDEX FROM KLADR WHERE (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) AND (CODE4=:CODE4) AND (CODE5=:CODE5)");
        query.bindValue(":CODE1",code1);
        query.bindValue(":CODE2",0);
        query.bindValue(":CODE3",0);
        query.bindValue(":CODE4",0);
        query.bindValue(":CODE5",0);
        if(!query.exec()){
            ShowErrorRecord(query);
            return;
        }
        if( query.next() ){
            QString name = query.value(5).toString();
            ui.region->setText(name);
            ui.index->setText(query.value(6).toString());
        }
    }

    if(code2!=0){
        QSqlQuery query;
        query.prepare("SELECT  CODE1, CODE2, CODE3, CODE4, CODE5, NAME, RINDEX FROM KLADR WHERE (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) AND (CODE4=:CODE4) AND (CODE5=:CODE5)");
        query.bindValue(":CODE1",code1);
        query.bindValue(":CODE2",code2);
        query.bindValue(":CODE3",0);
        query.bindValue(":CODE4",0);
        query.bindValue(":CODE5",0);
        if(!query.exec()){
            ShowErrorRecord(query);
            return;
        }
        if( query.next() ){
            QString name = query.value(5).toString();
            ui.subregion->setText(name);
            ui.index->setText(query.value(6).toString());
        }
    }


    if(code3!=0){
        QSqlQuery query;
        query.prepare("SELECT  CODE1, CODE2, CODE3, CODE4, CODE5, NAME, RINDEX FROM KLADR WHERE (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) AND (CODE4=:CODE4) AND (CODE5=:CODE5)");
        query.bindValue(":CODE1",code1);
        query.bindValue(":CODE2",code2);
        query.bindValue(":CODE3",code3);
        query.bindValue(":CODE4",0);
        query.bindValue(":CODE5",0);
        if(!query.exec()){
            ShowErrorRecord(query);
            return;
        }
        if( query.next() ){
            QString name = query.value(5).toString();
            ui.city->setText(name);
            ui.index->setText(query.value(6).toString());
        }
    }

    if(code4!=0){
        QSqlQuery query;
        query.prepare("SELECT  CODE1, CODE2, CODE3, CODE4, CODE5, NAME, RINDEX FROM KLADR WHERE (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) AND (CODE4=:CODE4) AND (CODE5=:CODE5)");
        query.bindValue(":CODE1",code1);
        query.bindValue(":CODE2",code2);
        query.bindValue(":CODE3",code3);
        query.bindValue(":CODE4",code4);
        query.bindValue(":CODE5",0);
        if(!query.exec()){
            ShowErrorRecord(query);
            return;
        }
        if( query.next() ){
            QString name = query.value(5).toString();
            ui.subcity->setText(name);
            ui.index->setText(query.value(6).toString());
        }
    }

    if(code5!=0){
        QSqlQuery query;
        query.prepare("SELECT  CODE1, CODE2, CODE3, CODE4, CODE5, NAME, RINDEX FROM KLADR WHERE (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) AND (CODE4=:CODE4) AND (CODE5=:CODE5)");
        query.bindValue(":CODE1",code1);
        query.bindValue(":CODE2",code2);
        query.bindValue(":CODE3",code3);
        query.bindValue(":CODE4",code4);
        query.bindValue(":CODE5",code5);
        if(!query.exec()){
            ShowErrorRecord(query);
            return;
        }
        if( query.next() ){
            QString name = query.value(5).toString();
            ui.street->setText(name);
            ui.index->setText(query.value(6).toString());
        }
    }
}

//region
void Address::choose_Region( int codeset ) {
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query;
    query.prepare("SELECT CODE, RINDEX, NAME FROM REGIONS ORDER BY CODE");
    if(!query.exec()){
        ShowErrorRecord(query);
        return;
    }
    model->setQuery(query);
    tableView->setModel(model);
    tableView->hideColumn(0);
    tableView->hideColumn(1);
    //tableView->verticalHeader()->hide();
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
        code = rec.field("CODE").value().toString();
        bool ok;
        code1 = code.left(2).toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.region->setText(name);
        ui.subregion->clear();
        ui.city->clear();
        ui.subcity->clear();
        ui.street->clear();
        rindex = rec.field("RINDEX").value().toString();
        ui.index->setText(rindex);
    }
    setPresentation();
}

//sub region
void Address::choose_Subregion( int codeset ) {
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query;
    query.prepare("SELECT  CODE, CODE1, CODE2, RINDEX , NAME FROM KLADR WHERE (RTYPE = 2) AND (CODE1=:CODE1) ORDER BY NAME");
    query.bindValue(":CODE1", code1);
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
        code = rec.field("CODE").value().toString();
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.subregion->setText(name);
        ui.city->clear();
        ui.subcity->clear();
        ui.street->clear();
        rindex = rec.field("RINDEX").value().toString();
        ui.index->setText(rindex);
    }
    setPresentation();
}

//city or town
void Address::choose_City( int codeset )
{
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query;
    query.prepare("SELECT CODE, CODE1, CODE2, CODE3, RINDEX, NAME FROM KLADR WHERE (RTYPE = 3) AND (CODE1=:CODE1) AND (CODE2=:CODE2) ORDER BY NAME");
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
        code = rec.field("CODE").value().toString();
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        code3 = rec.field("CODE3").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.city->setText(name);
        ui.subcity->clear();
        ui.street->clear();
        rindex = rec.field("RINDEX").value().toString();
        ui.index->setText(rindex);
    }
    setPresentation();
}

//city or village
void Address::choose_Subcity(int codeset)
{
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query;
    query.prepare("SELECT  CODE, CODE1, CODE2, CODE3, CODE4, RINDEX, NAME FROM KLADR WHERE (RTYPE = 4) AND (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) ORDER BY NAME");
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
        code = rec.field("CODE").value().toString();
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        code3 = rec.field("CODE3").value().toInt(&ok);
        code4 = rec.field("CODE4").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.subcity->setText(name);
        ui.street->clear();
        rindex = rec.field("RINDEX").value().toString();
        ui.index->setText(rindex);
    }
    setPresentation();
}

//street
void Address::choose_Street( int codeset )
{
    QTableView* tableView = new QTableView(this);
    QSqlQueryModel* model = new QSqlQueryModel(this);
    QSqlQuery query;
    query.prepare("SELECT  CODE, CODE1, CODE2, CODE3, CODE4, CODE5, RINDEX, NAME FROM KLADR WHERE (RTYPE = 5) AND (CODE1=:CODE1) AND (CODE2=:CODE2) AND (CODE3=:CODE3) AND (CODE4=:CODE4) ORDER BY NAME");
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
    tableView->hideColumn(6);
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
        code = rec.field("CODE").value().toString();
        code1 = rec.field("CODE1").value().toInt(&ok);
        code2 = rec.field("CODE2").value().toInt(&ok);
        code3 = rec.field("CODE3").value().toInt(&ok);
        code4 = rec.field("CODE4").value().toInt(&ok);
        code5 = rec.field("CODE5").value().toInt(&ok);
        QString name = rec.field("NAME").value().toString();
        ui.street->setText(name);
        rindex = rec.field("RINDEX").value().toString();
        ui.index->setText(rindex);
    }
    setPresentation();
}

//set all view in fullAdress
void Address::setPresentation()
{
    QTextCodec* codec = QTextCodec::codecForLocale();
    if(!codec) return;

    QString txtPresent = ui.region->text();
    QString txtIndex = ui.index->text();
    if( !txtIndex.isEmpty() ) txtPresent = ui.index->text() + ", " + txtPresent;
    QString txtSubregion = ui.subregion->text();
    QString txtCity  = ui.city->text();
    if( !txtCity.isEmpty() ) txtPresent = txtPresent + ", г. " + txtCity;
    QString txtStreet  = ui.street->text();
    if( !txtStreet.isEmpty() ) txtPresent = txtPresent + ", ул. " + txtStreet;
    QString txtHouse  = ui.house->text();
    if( !txtHouse.isEmpty()) txtPresent = txtPresent + " " +ui.cmb_house->currentText() + " " + txtHouse;
    QString txtBilding  = ui.building->text();
    if( !txtBilding.isEmpty()) txtPresent = txtPresent + " " +ui.cmb_building->currentText() + " " + txtBilding;
    QString txtFlat  = ui.flat->text();
    if( !txtFlat.isEmpty()) txtPresent = txtPresent + " " +ui.cmb_flat->currentText() + " " + txtFlat;

    ui.fullAddress->setText(txtPresent);
}
