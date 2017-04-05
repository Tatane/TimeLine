#ifndef MAINWIN_H
#define MAINWIN_H

#include <QDialog>
#include "POCO/Fact.h"
#include "FactTableModel.h"

namespace Ui {
class MainWin;
}

class MainWin : public QDialog
{
    Q_OBJECT

private slots:
    void onBtnQuitClicked();
    void onBtnAddFact();

public:
    explicit MainWin(QWidget *parent = 0);
    ~MainWin();

private:
    Ui::MainWin *ui;
    std::vector<Fact*> vecFacts;
    FactTableModel factTableModel;

    void displayFacts();

};

#endif // MAINWIN_H
