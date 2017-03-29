#include "mainwin.h"
#include "ui_mainwin.h"

#include <QMessageBox>
#include "DAL/DataAcces.h"

MainWin::MainWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWin),
    model(0)
{
    ui->setupUi(this);

    connect(ui->btnQuit, SIGNAL(clicked(bool)), this, SLOT(onBtnQuitClicked()));

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

    model = new FactTableModel(&vecFacts);

    ui->tableView->setModel(model);
/*
    // put the Facts in the view
    std::vector<Fact*>::const_iterator it;
    for(it=vecFacts.begin(); it != vecFacts.end(); ++it) {


    }
    */
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
