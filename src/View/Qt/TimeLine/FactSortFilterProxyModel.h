#ifndef FACTSORTFILTERPROXYMODEL_H
#define FACTSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>
#include "FactTableModel.h"

class FactSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    FactSortFilterProxyModel();

    void rowAppened();
    void rowRemoved(int row);
    void setSourceModel(FactTableModel & sourceModel);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    FactTableModel * factTableModel;

};

#endif // FACTSORTFILTERPROXYMODEL_H
