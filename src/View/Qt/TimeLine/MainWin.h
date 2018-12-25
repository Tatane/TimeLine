#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>

#include "FactTableModel.h"
#include "FactSortFilterProxyModel.h"
#include "Facts.h"
#include "DAL/DataAcces.h"

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
    FactTableModel factTableModel;
    FactSortFilterProxyModel sortFilterProxyModel;
	DataAcces* mDatabase;

    void loadModelData();

};

#endif // MAINWIN_H
