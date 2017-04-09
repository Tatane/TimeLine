#include "MySortFilterProxyModel.h"

MySortFilterProxyModel::MySortFilterProxyModel()
{

}


bool MySortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex index = sourceModel()->index(source_row, 3, source_parent);
    QString str = sourceModel()->data(index).toString();
    if (str.contains("a")) return true; else return false;
}
