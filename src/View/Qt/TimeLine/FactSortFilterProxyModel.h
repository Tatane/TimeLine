#ifndef FACTSORTFILTERPROXYMODEL_H
#define FACTSORTFILTERPROXYMODEL_H

#include "FactTableModel.h"

#include <QSortFilterProxyModel>
#include <QString>
#include <QDate>

class FactSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    FactSortFilterProxyModel();

    void rowAppened();
    void rowRemoved(int row);
    void setSourceModel(FactTableModel & sourceModel);
    void setTextFilter(QString textFilter);
    void setDatesFilter(QDate startDate, QDate endDate);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    FactTableModel * factTableModel;
    QString textFilter;
    QDate startDateFilter, endDateFilter;

};

#endif // FACTSORTFILTERPROXYMODEL_H
