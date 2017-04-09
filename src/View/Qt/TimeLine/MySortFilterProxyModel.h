#ifndef MYSORTFILTERPROXYMODEL_H
#define MYSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class MySortFilterProxyModel : public QSortFilterProxyModel
{
public:
    MySortFilterProxyModel();

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
};

#endif // MYSORTFILTERPROXYMODEL_H
