#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>
#include "POCO/Fact.h"
#include "FactTableModel.h"
#include "FactSortFilterProxyModel.h"

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
    void onBtnDatePickerStart();

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

private:
    Ui::MainWin *ui;
    std::vector<Fact*> vecFacts;
    FactTableModel factTableModel;
    FactSortFilterProxyModel sortFilterProxyModel;

    void loadModelData();

};

#endif // MAINWIN_H
