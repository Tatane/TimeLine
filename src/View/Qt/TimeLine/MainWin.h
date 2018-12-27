#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>

#include "FactTableModel.h"
#include "FactSortFilterProxyModel.h"
#include "Facts.h"
#include "DAL/DataAcces.h"
#include <memory>
#include "ACategory.h"

namespace Ui {
class MainWin;
}

class MainWin : public QDialog
{
    Q_OBJECT

private slots:
    void onBtnQuit();
    void onBtnAddFact();
    void onBtnRemoveFact();
    void onBtnEditFact();
    void onFilterChanged(QString filterValue);
    void onDatesFilterChanged();

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

private:
    Ui::MainWin *ui;
    Facts facts;
	std::vector<std::unique_ptr<ACategory>> mCategories;
    std::unique_ptr<FactTableModel> factTableModel;
    std::unique_ptr<FactSortFilterProxyModel> sortFilterProxyModel;
	DataAcces* mDatabase;

    void loadModelData();

};

#endif // MAINWIN_H
