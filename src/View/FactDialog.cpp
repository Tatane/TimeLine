#include "FactDialog.h"
#include "ui_factdialog.h"
#include "POCO/Fact.h"
#include "DAL/DataAcces.h"

#include "POCO/ACategory.h"
#include "CategoryDialog.h"

FactDialog::FactDialog(Fact **fact, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FactDialog),
    pEditedFact(fact)
{
    ui->setupUi(this);

    connect(ui->btnCancel, SIGNAL(clicked(bool)), this, SLOT(onBtnCancel()));
    connect(ui->btnOK, SIGNAL(clicked(bool)), this, SLOT(onBtnOk()));
    connect(ui->chkAllDayStartTime, SIGNAL(toggled(bool)), ui->startTimeEdit, SLOT(setDisabled(bool)));
    connect(ui->chkAllDayEndTime, SIGNAL(toggled(bool)), ui->endTimeEdit, SLOT(setDisabled(bool)));
	connect(ui->btnManageCategories, SIGNAL(clicked(bool)), this, SLOT(onBtnManageCategories()));

    initializeFields();
}

FactDialog::~FactDialog()
{
    delete ui;
}

void FactDialog::initializeFields()
{
	ui->comboBoxCategory->addItem("");
	for (auto & pair : ACategories::getCategories())
	{
		ui->comboBoxCategory->addItem(pair.second->getName().c_str(), pair.first);
	}

    if (*pEditedFact != NULL) {
        Fact * fact = *pEditedFact;
        ui->lineEditTitle->setText(QString::fromStdString(fact->getTitle()));
        ui->textEditDescription->setText(QString::fromStdString(fact->getDescription()));
        QDate date(fact->getStartTime().get().tm_year + 1900, fact->getStartTime().get().tm_mon + 1, fact->getStartTime().get().tm_mday);
        ui->startDateEdit->setDate(date);

        date = QDate(fact->getEndTime().get().tm_year + 1900, fact->getEndTime().get().tm_mon + 1, fact->getEndTime().get().tm_mday);
        ui->endDateEdit->setDate(date);

        ui->startTimeEdit->setTime(QTime(fact->getStartTime().get().tm_hour, fact->getStartTime().get().tm_min, fact->getStartTime().get().tm_sec));

        ui->endTimeEdit->setTime(QTime(fact->getEndTime().get().tm_hour, fact->getEndTime().get().tm_min, fact->getEndTime().get().tm_sec));

/* TODO
		if ((*pEditedFact)->getCategory() != nullptr)
		{
			ui->comboBoxCategory->setCurrentText((*pEditedFact)->getCategory()->getName().c_str());
		}
*/
		

		

    } else {
        ui->startDateEdit->setDateTime(QDateTime::currentDateTime());
        ui->endDateEdit->setDateTime(QDateTime::currentDateTime());
    }
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
        /* TODO
	int comboCategoryCurrentSelectedId = ui->comboBoxCategory->currentData().toInt();
	if (ACategories::getCategories().count(comboCategoryCurrentSelectedId) == 1)
	{
		std::shared_ptr<ACategory> category = ACategories::getCategories().at(comboCategoryCurrentSelectedId);
		fact->setCategory(category);
	}
*/
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

void FactDialog::onBtnManageCategories()
{
	CategoryDialog categoryDialog;
	categoryDialog.exec();
}
