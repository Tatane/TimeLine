#include "CategoryDialog.h"
#include "ACategory.h"
#include "DAL/DataAcces.h"

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
	if (!newCategoryName.isEmpty())
	{
		std::shared_ptr<ACategory> category = std::make_shared<ACategory>();
		category->setName(newCategoryName.toStdString());
		DataAcces::getInstance()->insertCategory(category);
		if (category->getId() > 0)
		{
			ACategories::getCategories()[category->getId()] = category;
		}
	}
}
