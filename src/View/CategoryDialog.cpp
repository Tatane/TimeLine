#include "CategoryDialog.h"
#include "POCO/ACategory.h"
#include "DAL/DataAcces.h"
#include <QMessageBox>
#include <QListWidget>

CategoryDialog::CategoryDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnAddCategory, SIGNAL(clicked(bool)), this, SLOT(onClickBtnAddCategory()));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(onClickBtnDelete()));
	connect(ui.btnEdit, SIGNAL(clicked(bool)), this, SLOT(onClickBtnEdit()));
	connect(ui.listWidgetCategories, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(onItemChanged(QListWidgetItem *)));

	displayCategories();
}

CategoryDialog::~CategoryDialog()
{
}

void CategoryDialog::displayCategories()
{	
	ui.listWidgetCategories->clear();

	for (auto pair : ACategories::getCategories())
	{
		ui.listWidgetCategories->insertItem(0, new AListWidgetItemCategory(pair.second, ui.listWidgetCategories));
	}

	ui.listWidgetCategories->sortItems();	
}

void CategoryDialog::onClickBtnDelete()
{
	AListWidgetItemCategory * listWidgetCategory = dynamic_cast<AListWidgetItemCategory*>(ui.listWidgetCategories->currentItem());
	if (listWidgetCategory != nullptr)
	{
		if (QMessageBox::Ok == QMessageBox::question(this, "Delete", "Category '" + QString(listWidgetCategory->getCategory()->getName().c_str()) + "' will be deleted.", QMessageBox::Ok | QMessageBox::Cancel))
		{
			std::shared_ptr<ACategory> category = listWidgetCategory->getCategory();
			if (DataAcces::getInstance()->deleteCategory(category))
			{
				ACategories::getCategories().erase(category->getId());
				displayCategories();
			}
		}
	}
}

void CategoryDialog::onClickBtnEdit()
{
	AListWidgetItemCategory * item = dynamic_cast<AListWidgetItemCategory*>(ui.listWidgetCategories->currentItem());
	if (item != nullptr)
	{
		std::shared_ptr<ACategory> category = item->getCategory();
		QString oldName = category->getName().c_str();
		QString newName = ui.lineEditCategory->text();

		if (QMessageBox::Ok == QMessageBox::question(this, "", "Category '" + oldName + "' will be updated to '" + newName + "'.", QMessageBox::Ok | QMessageBox::Cancel))
		{
			category->setName(newName.toStdString());
			if (DataAcces::getInstance()->updateCategory(category))
			{
				QMessageBox::information(this, "", "Category '" + oldName + "' has been updated to '" + newName +"'");
				displayCategories();
			}
		}

	}
}

void CategoryDialog::onItemChanged(QListWidgetItem * current)
{
	if (current != nullptr)
	{
		ui.lineEditCategory->setText(current->text());
	}
}

void CategoryDialog::onClickBtnAddCategory()
{
	QString newCategoryName = ui.lineEditCategory->text();

	if (newCategoryName.isEmpty())
	{
		QMessageBox::information(this, "", "The category need a name.");
	}
	else if (ACategories::containsCategoryName(newCategoryName.toStdString()))
	{
		QMessageBox::information(this, "", "A Category with this name already exists.");
	}
	else 
	{
		std::shared_ptr<ACategory> category = std::make_shared<ACategory>();
		category->setName(newCategoryName.toStdString());
		DataAcces::getInstance()->insertCategory(category);
		if (category->getId() > 0)
		{
			ACategories::getCategories()[category->getId()] = category;
			displayCategories();
			QMessageBox::information(this, "", "Category '" + QString(category->getName().c_str()) + "' has been created.");
		}
		else
		{
			QMessageBox::warning(this, "Error", "Category '" + QString(category->getName().c_str()) + "' could not been created.");
		}
	}
}
