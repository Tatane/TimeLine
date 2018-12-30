#include "CategoryDialog.h"
#include "ACategory.h"
#include "DAL/DataAcces.h"
#include <QMessageBox>
#include <QListWidget>

CategoryDialog::CategoryDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnAddCategory, SIGNAL(clicked(bool)), this, SLOT(onClickBtnAddCategory()));
	connect(ui.btnDelete, SIGNAL(clicked(bool)), this, SLOT(onClickBtnDelete()));

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
	AListWidgetItemCategory * listWidgetCategory = dynamic_cast<AListWidgetItemCategory*>(ui.listWidgetCategories->selectedItems().first());
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
