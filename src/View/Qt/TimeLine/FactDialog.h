#ifndef FACTDIALOG_H
#define FACTDIALOG_H

#include <QDialog>

namespace Ui {
class FactDialog;
}

class FactDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FactDialog(QWidget *parent = 0);
    ~FactDialog();

private:
    Ui::FactDialog *ui;

private slots:
    void onBtnCancel();
    void onBtnOk();
};

#endif // FACTDIALOG_H
