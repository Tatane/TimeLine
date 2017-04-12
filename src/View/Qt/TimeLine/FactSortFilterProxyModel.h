#ifndef FACTSORTFILTERPROXYMODEL_H
#define FACTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class FactSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    FactSortFilterProxyModel();

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // FACTSORTFILTERPROXYMODEL_H
