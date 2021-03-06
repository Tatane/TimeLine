#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>
#include <QMenuBar>

#include "FactTableModel.h"
#include "FactSortFilterProxyModel.h"
#include "POCO/Facts.h"
#include "DAL/DataAcces.h"
#include <memory>
#include "POCO/ACategory.h"

namespace Ui {
class MainWin;
}

class MainWin : public QMainWindow
{
    Q_OBJECT

private slots:
    void onBtnQuit();
    void onBtnAddFact();
    void onBtnRemoveFact();
    void onBtnEditFact();
    void onFilterChanged(QString filterValue);
    void onDatesFilterChanged();
    void OnManageCategories();

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

    QMenu * mMenuSettings;
    QAction * mActionManageCategories;

    void loadModelData();

};

#endif // MAINWIN_H
