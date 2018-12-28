#pragma once

#include <QDialog>
#include "ui_CategoryDialog.h"

class CategoryDialog : public QDialog
{
	Q_OBJECT

public:
	CategoryDialog(QWidget *parent = Q_NULLPTR);
	~CategoryDialog();

private:
	Ui::CategoryDialog ui;

private slots:
	void onClickBtnAddCategory();
};
