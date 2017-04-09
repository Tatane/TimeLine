#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>
#include "POCO/Fact.h"
#include "FactTableModel.h"
//#include <QSortFilterProxyModel>
#include "MySortFilterProxyModel.h"

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

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

private:
    Ui::MainWin *ui;
    std::vector<Fact*> vecFacts;
    FactTableModel factTableModel;
    MySortFilterProxyModel proxyModel;

    void displayFacts();

};

#endif // MAINWIN_H
