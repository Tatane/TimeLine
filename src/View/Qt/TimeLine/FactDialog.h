#ifndef FACTDIALOG_H
#define FACTDIALOG_H

#include <QDialog>
#include <POCO/Fact.h>

namespace Ui {
class FactDialog;
}

class FactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FactDialog(Fact ** editedFact, QWidget *parent = 0);
    ~FactDialog();

private:
    Ui::FactDialog *ui;
    Fact ** pEditedFact;

    void initializeFields();

private slots:
    void onBtnCancel();
    void onBtnOk();
};

#endif // FACTDIALOG_H
