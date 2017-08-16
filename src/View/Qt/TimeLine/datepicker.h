#ifndef DATEPICKER_H
#define DATEPICKER_H

#include <QDialog>
#include <QCalendarWidget>

class DatePicker : public QDialog
{
    Q_OBJECT

public:
    DatePicker(QWidget * parent);
    QDate selectedDate() const;

private:
    QCalendarWidget calendar;

private slots:
    void calendarDateActivated(QDate date);
};

#endif // DATEPICKER_H
