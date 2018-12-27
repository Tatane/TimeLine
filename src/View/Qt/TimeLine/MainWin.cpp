#include "mainwin.h"
#include "ui_mainwin.h"

#include <QMessageBox>
#include "DAL/DataAcces.h"
#include "FactTableModel.h"
#include "FactDialog.h"
#include <algorithm>
#include <QSortFilterProxyModel>

#include <QApplication>
#include "AlxColors.h"

MainWin::MainWin(QWidget *parent) :
    QDialog(parent),
    factTableModel(std::make_unique<FactTableModel>()),
    sortFilterProxyModel(std::make_unique<FactSortFilterProxyModel>(factTableModel)),
    ui(new Ui::MainWin)
{
    ui->setupUi(this);

    connect(ui->btnQuit, SIGNAL(clicked(bool)), this, SLOT(onBtnQuit()));
    connect(ui->btnAddFact, SIGNAL(clicked(bool)), this, SLOT(onBtnAddFact()));
    connect(ui->btnRemoveFact, SIGNAL(clicked(bool)), this, SLOT(onBtnRemoveFact()));
    connect(ui->btnEditFact, SIGNAL(clicked(bool)), this, SLOT(onBtnEditFact()));

    connect(ui->filter, SIGNAL(textEdited(QString)), this, SLOT(onFilterChanged(QString)));

    connect(ui->dateEditStartTime, SIGNAL(dateChanged(QDate)), this, SLOT(onDatesFilterChanged()));
    connect(ui->dateEditEndTime, SIGNAL(dateChanged(QDate)), this, SLOT(onDatesFilterChanged()));

	// Enable Maximize window button :
	setWindowFlag(Qt::WindowMaximizeButtonHint);


	mDatabase = DataAcces::getInstance();
	if ( ! mDatabase->open() )
	{
		QMessageBox msg;
		msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msg.setText("Database file cannot be found. Do you want to create a new empty database ? Choose Cancel to close application.");
		msg.setIcon(QMessageBox::Question);
		int ret = msg.exec();

		if (ret == QMessageBox::Yes)
		{
			mDatabase->createDatabase();
		}
		else
		{
			exit(0);
		}
	}

    loadModelData();

    // Resize all columns to fit their contents :
    ui->tableView->resizeColumnsToContents();

    // Set the background color of the main window :
    qApp->palette().setColor(QPalette::Window, AlxColors::COLOR_1);
}

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::loadModelData()
{
	if (mDatabase)
	{
		// Read from database all Categories :
		mDatabase->getAllCategories(&ACategories::getCategories());

		// Read from database and fill the Model :
		mDatabase->getAllFacts(*(facts.getVecFacts()));

		// Set the TableModel with the Model :
		factTableModel->setVectFacts(facts.getVecFacts());

		// Set the ProxyModel with the TableModel :
		sortFilterProxyModel->setSourceModel(factTableModel.get());

		// Set the View with the ProxyModel :
		ui->tableView->setModel(sortFilterProxyModel.get());
		//ui->tableView->setItemDelegateForColumn(FactTableModel::DataColumn::StartTime, &mDateTimeItemDelegate);

		// Initialize the Start and End time widgets with the bounds of the database :
		if (factTableModel->rowCount() >= 1) {
			ADateTime minimumStartDate, maximumEndDate;
			DataAcces::getInstance()->getDatesBounds(minimumStartDate, maximumEndDate);
			ui->dateEditStartTime->setDate(QDate(minimumStartDate.year(), minimumStartDate.month(), minimumStartDate.day()));
			ui->dateEditEndTime->setDate(QDate(maximumEndDate.year(), maximumEndDate.month(), maximumEndDate.day()));
		}
	}
 }

void MainWin::onBtnQuit()
{
	/*
    QMessageBox msg;
    msg.setText(tr("Do you want to quit ?"));
    msg.setIcon(QMessageBox::Question);
    msg.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    msg.setDefaultButton(QMessageBox::Yes);

    if (msg.exec() == QMessageBox::Yes) {
        exit(0);
    }
	*/
	exit(0);
}

void MainWin::onBtnAddFact()
{
    // Open Fact dialog.
    Fact * newFact = NULL;
    Fact ** pFact = &newFact;
    FactDialog factDialog(pFact);
    int ret = factDialog.exec();
    if (ret == QDialog::Accepted && *pFact != NULL) {
        facts.add(*pFact);

        sortFilterProxyModel->rowAppened();
		int index = static_cast<int>(facts.size() - 1);
        ui->tableView->selectRow(index);
    }
}

void MainWin::onBtnRemoveFact()
{
    QModelIndexList selectedRowsIndexes = ui->tableView->selectionModel()->selectedRows();
    if (selectedRowsIndexes.size() == 0) {
        QMessageBox msg;
        msg.setText("Select at least one row.");
        msg.setIcon(QMessageBox::Information);
        msg.exec();
        return;
    } else {
        QMessageBox msg;
        msg.setText("Permanently remove selected rows ?");
        msg.setIcon(QMessageBox::Question);
        msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msg.setDefaultButton(QMessageBox::Cancel);
        if (msg.exec() == QMessageBox::Ok) {
            std::vector<int> selectedRows;
            foreach (QModelIndex index, selectedRowsIndexes) {
                index = sortFilterProxyModel->mapToSource(index);
                selectedRows.push_back(index.row());
            }
            // Sort descending, because deleting a row will shift indexes of nexts rows. So we want to start to delete from the end.
            std::sort(selectedRows.begin(), selectedRows.end(), std::greater<int>());

            foreach (int row, selectedRows) {
                DataAcces::getInstance()->deleteFact(*(facts[row])); // delete from the database.
                sortFilterProxyModel->rowRemoved(row); // remove the row from the table.
                delete facts[row];   // delete the instance.
                facts.erase(row); // remove from the container.
            }

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
        QModelIndex index = sortFilterProxyModel->mapToSource(selectedRowsIndexes.first());
        Fact* fact = facts[index.row()];
        if (fact != NULL) {
            FactDialog factDialog(&fact);
            factDialog.exec();
        }
    }
}

void MainWin::onFilterChanged(QString filterValue)
{
    sortFilterProxyModel->setTextFilter(filterValue);
    ui->tableView->update();
}

void MainWin::onDatesFilterChanged()
{
    sortFilterProxyModel->setDatesFilter(ui->dateEditStartTime->date(), ui->dateEditEndTime->date());
    ui->tableView->update();
}


