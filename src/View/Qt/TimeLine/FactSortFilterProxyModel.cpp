#include "FactSortFilterProxyModel.h"

FactSortFilterProxyModel::FactSortFilterProxyModel()
    :factTableModel(0)
    ,textFilter("")
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
    QModelIndex indexDescription = sourceModel()->index(source_row, FactTableModel::DataColumn::Description, source_parent);
    QString description = sourceModel()->data(indexDescription).toString();

    QModelIndex indexTitle = sourceModel()->index(source_row, FactTableModel::DataColumn::Title, source_parent);
    QString title = sourceModel()->data(indexTitle).toString();

    if (textFilter.isEmpty() || description.contains(textFilter) || title.contains(textFilter)) {
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

