#include "FactSortFilterProxyModel.h"

FactSortFilterProxyModel::FactSortFilterProxyModel()
    :factTableModel(0)
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

bool FactSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 3, source_parent);
    QString str = sourceModel()->data(index).toString();
    if (textFilter.isEmpty() || str.contains(textFilter)) {
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

