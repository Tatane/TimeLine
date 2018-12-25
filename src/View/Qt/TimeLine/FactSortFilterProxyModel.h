#ifndef FACTSORTFILTERPROXYMODEL_H
#define FACTSORTFILTERPROXYMODEL_H

#include "FactTableModel.h"

#include <QSortFilterProxyModel>
#include <QString>
#include <QDate>

class FactSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    FactSortFilterProxyModel(std::unique_ptr<FactTableModel> & model);

    void rowAppened();
    void rowRemoved(int row);
    void setTextFilter(QString textFilter);
    void setDatesFilter(QDate startDate, QDate endDate);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    std::unique_ptr<FactTableModel> & factTableModel;
    QString textFilter;
    QDate startDateFilter, endDateFilter;

};

#endif // FACTSORTFILTERPROXYMODEL_H
