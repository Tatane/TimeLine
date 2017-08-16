#include "datepicker.h"

#include <QCalendarWidget>

DatePicker::DatePicker(QWidget *parent)
    : QDialog(parent)
{
    calendar.setParent(this);

    setMaximumWidth(calendar.sizeHint().width());
    setMaximumHeight(calendar.sizeHint().height());

    connect(&calendar, SIGNAL(activated(QDate)), this, SLOT(calendarDateActivated(QDate)));
}

QDate DatePicker::selectedDate() const
{
    return calendar.selectedDate();
}

void DatePicker::calendarDateActivated(QDate date)
{
    done(0);
}
