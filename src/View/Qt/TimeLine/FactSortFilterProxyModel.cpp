#include "FactSortFilterProxyModel.h"

FactSortFilterProxyModel::FactSortFilterProxyModel()
    :factTableModel(0)
    ,textFilter("")
    ,startDateFilter(QDate(1900,1,1))
    ,endDateFilter(QDate(2100, 1, 1))
{
}

void FactSortFilterProxyModel::setSourceModel(FactTableModel & sourceModel){
    QSortFilterProxyModel::setSourceModel(&sourceModel);
    factTableModel = &sourceModel;
}

void FactSortFilterProxyModel::setTextFilter(QString textFilter)
{
    beginResetModel();
    this->textFilter = textFilter;
    endResetModel();
}

void FactSortFilterProxyModel::setDatesFilter(QDate startDate, QDate endDate)
{
    beginResetModel();
    this->startDateFilter = startDate;
    this->endDateFilter = endDate;
    endResetModel();
}

bool FactSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex indexDescription = sourceModel()->index(source_row, FactTableModel::DataColumn::Description, source_parent);
    QString description = sourceModel()->data(indexDescription).toString();

    QModelIndex indexTitle = sourceModel()->index(source_row, FactTableModel::DataColumn::Title, source_parent);
    QString title = sourceModel()->data(indexTitle).toString();

    QModelIndex indexStartTime = sourceModel()->index(source_row, FactTableModel::DataColumn::StartTime, source_parent);
    QDate factStartTime = sourceModel()->data(indexStartTime).toDate();

    QModelIndex indexEndTime = sourceModel()->index(source_row, FactTableModel::DataColumn::Endtime, source_parent);
    QDate factEndTime = sourceModel()->data(indexEndTime).toDate();

    if ( (textFilter.isEmpty() || description.contains(textFilter, Qt::CaseInsensitive) || title.contains(textFilter, Qt::CaseInsensitive))
         && factStartTime >= startDateFilter
         && factEndTime <= endDateFilter
    ) {
        return true;
    } else {
        return false;
    }
}

void FactSortFilterProxyModel::rowAppened()
{
    factTableModel->rowAppened();
}

void FactSortFilterProxyModel::rowRemoved(int row)
{
    factTableModel->rowRemoved(row);
}

