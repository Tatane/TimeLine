#include "mainwin.h"
#include "ui_mainwin.h"

#include <QMessageBox>
#include "DAL/DataAcces.h"
#include "FactTableModel.h"
#include "FactDialog.h"
#include <algorithm>
#include <QSortFilterProxyModel>

MainWin::MainWin(QWidget *parent) :
    QDialog(parent),
    factTableModel(vecFacts),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);

    connect(ui->btnQuit, SIGNAL(clicked(bool)), this, SLOT(onBtnQuit()));
    connect(ui->btnAddFact, SIGNAL(clicked(bool)), this, SLOT(onBtnAddFact()));
    connect(ui->btnRemoveFact, SIGNAL(clicked(bool)), this, SLOT(onBtnRemoveFact()));
    connect(ui->btnEditFact, SIGNAL(clicked(bool)), this, SLOT(onBtnEditFact()));

    displayFacts();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::displayFacts()
{
    // Read from database. The Model already has a reference to this container.
    DataAcces::getInstance()->getAllFacts(vecFacts);

    // Init the Proxy model with the "real" model :
    proxyModel.setSourceModel(&factTableModel);

    // Use the Porxy model to display in the View :
    ui->tableView->setModel(&proxyModel);
}

void MainWin::onBtnQuit()
{
    QMessageBox msg;
    msg.setText(tr("Do you want to quit ?"));
    msg.setIcon(QMessageBox::Question);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    if (msg.exec() == QMessageBox::Yes) {
        exit(0);
    }
}

void MainWin::onBtnAddFact()
{
    // Open Fact dialog.
    Fact * newFact = NULL;
    Fact ** pFact = &newFact;
    FactDialog factDialog(pFact);
    int ret = factDialog.exec();
    if (ret == QDialog::Accepted && *pFact != NULL) {
        vecFacts.push_back(*pFact);

        factTableModel.rowAppened();
        ui->tableView->selectRow(vecFacts.size()-1);
    }
}

void MainWin::onBtnRemoveFact()
{
    QMessageBox msg;
    msg.setText("Permanently remove selected rows ?");
    msg.setIcon(QMessageBox::Question);
    msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Cancel);
    if (msg.exec() == QMessageBox::Ok) {

        QModelIndexList selectedRowsIndexes = ui->tableView->selectionModel()->selectedRows();
        std::vector<int> selectedRows;
        foreach (QModelIndex index, selectedRowsIndexes) {
            index = proxyModel.mapToSource(index);
            selectedRows.push_back(index.row());
        }
        // Sort descending, because deleting a row will shift indexes of nexts rows. So we want to start to delete from the end.
        std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>());

        foreach (int row, selectedRows) {
            DataAcces::getInstance()->deleteFact(*(vecFacts[row])); // delete from the database.
            factTableModel.rowRemoved(row); // remove the row from the table.
            delete vecFacts[row];   // delete the instance.
            vecFacts.erase(vecFacts.begin()+row); // remove from the container.
        }

    }
}

void MainWin::onBtnEditFact()
{
    QModelIndexList selectedRowsIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedRowsIndexes.size() != 1) {
        QMessageBox msg;
        msg.setText("Select one, and only one row.");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
        return;
    } else {
        QModelIndex index = proxyModel.mapToSource(selectedRowsIndexes.first());
        Fact* fact = vecFacts[index.row()];
        if (fact != NULL) {
            FactDialog factDialog(&fact);
            factDialog.exec();
        }
    }
}
