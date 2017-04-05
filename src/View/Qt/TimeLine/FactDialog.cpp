#include "FactDialog.h"
#include "ui_FactDialog.h"
#include "POCO/Fact.h"
#include "DAL/DataAcces.h"

FactDialog::FactDialog(Fact **fact, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactDialog),
    //editedFact(fact),
    pEditedFact(fact)
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

    Fact * fact = 0;

    // If Editing existing Fact
    if (*pEditedFact == NULL)
    {
        fact = new Fact;
    } else {
        fact = *pEditedFact;
    }

    fact->setTitle(ui->lineEditTitle->text().toStdString());
    fact->setDescription(ui->textEditDescription->document()->toPlainText().toStdString());
    fact->setStartTime(ui->startDateEdit->date().year(), ui->startDateEdit->date().month(), ui->startDateEdit->date().day(),
                          ui->startTimeEdit->time().hour(), ui->startTimeEdit->time().minute(), ui->startTimeEdit->time().second());
    fact->setEndTime(ui->endDateEdit->date().year(), ui->endDateEdit->date().month(), ui->endDateEdit->date().day(),
                          ui->endTimeEdit->time().hour(), ui->endTimeEdit->time().minute(), ui->endTimeEdit->time().second());

    // UPdate ou INSERT in DB
    if (*pEditedFact == NULL) {
        DataAcces::getInstance()->insertFact(*fact);
        *pEditedFact = fact;
    } else {
        DataAcces::getInstance()->updateFact(*fact);
    }


    accept();

//    close();
}
