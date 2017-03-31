#include "FactDialog.h"
#include "ui_FactDialog.h"

FactDialog::FactDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactDialog)
{
    ui->setupUi(this);

    connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(onBtnCancel()));
    connect(ui->btnOK, SIGNAL(clicked(bool)), this, SLOT(onBtnOk()));
    connect(ui->chkAllDayStartTime, SIGNAL(toggled(bool)), ui->startTimeEdit, SLOT(setDisabled(bool)));
    connect(ui->chkAllDayEndTime, SIGNAL(toggled(bool)), ui->endTimeEdit, SLOT(setDisabled(bool)));

    ui->startDateEdit->setDateTime(QDateTime::currentDateTime());
    ui->endDateEdit->setDateTime(QDateTime::currentDateTime());
}

FactDialog::~FactDialog()
{
    delete ui;
}

void FactDialog::onBtnCancel()
{
    close();
}

void FactDialog::onBtnOk()
{
    // Save


    close();
}
