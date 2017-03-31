#include "mainwin.h"
#include "ui_mainwin.h"

#include <QMessageBox>
#include "DAL/DataAcces.h"
#include "FactTableModel.h"
#include "FactDialog.h"

MainWin::MainWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);

    connect(ui->btnQuit, SIGNAL(clicked(bool)), this, SLOT(onBtnQuitClicked()));
    connect(ui->btnAddFact, SIGNAL(clicked(bool)), this, SLOT(onBtnAddFact()));

    displayFacts();
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::displayFacts()
{
    // read from database
    DataAcces::getInstance()->getAllFacts(&vecFacts);

    ui->tableView->setModel(new FactTableModel(&vecFacts));
}

void MainWin::onBtnQuitClicked()
{
    QMessageBox msg;
    msg.setText(tr("Do you want to quit ?"));
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    if (msg.exec() == QMessageBox::Yes) {
        exit(0);
    }
}

void MainWin::onBtnAddFact()
{
    // Open Fact dialog.
    FactDialog factDialog;
    factDialog.exec();
}
