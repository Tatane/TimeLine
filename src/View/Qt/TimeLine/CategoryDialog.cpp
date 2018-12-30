#include "CategoryDialog.h"
#include "ACategory.h"
#include "DAL/DataAcces.h"
#include <QMessageBox>

CategoryDialog::CategoryDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	connect(ui.btnAddCategory, SIGNAL(clicked(bool)), this, SLOT(onClickBtnAddCategory()));
}

CategoryDialog::~CategoryDialog()
{
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
			QMessageBox::information(this, "", "Category '" + QString(category->getName().c_str()) + "' has been created.");
		}
		else
		{
			QMessageBox::warning(this, "Error", "Category '" + QString(category->getName().c_str()) + "' could not been created.");
		}
	}
}
