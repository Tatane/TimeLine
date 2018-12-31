#pragma once

#include <QDialog>
#include "ui_CategoryDialog.h"
#include "ACategory.h"

class AListWidgetItemCategory : public QListWidgetItem
{

public:
	AListWidgetItemCategory(std::shared_ptr<ACategory> & category, QListWidget * view)
		: QListWidgetItem(category->getName().c_str(), view)
		, mCategory(category)
	{}

	std::shared_ptr<ACategory> getCategory() const
	{
		return mCategory;
	}


private:
	std::shared_ptr<ACategory> mCategory;
};


class CategoryDialog : public QDialog
{
	Q_OBJECT

public:
	CategoryDialog(QWidget *parent = Q_NULLPTR);
	~CategoryDialog();

private:
	Ui::CategoryDialog ui;

	void displayCategories();

private slots:
	void onClickBtnAddCategory();
	void onClickBtnDelete();
	void onClickBtnEdit();
	void onItemChanged(QListWidgetItem *current);


};
