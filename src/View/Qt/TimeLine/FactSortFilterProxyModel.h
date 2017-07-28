#ifndef FACTSORTFILTERPROXYMODEL_H
#define FACTSORTFILTERPROXYMODEL_H

#include "FactTableModel.h"

#include <QSortFilterProxyModel>
#include <QString>

class FactSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    FactSortFilterProxyModel();

    void rowAppened();
    void rowRemoved(int row);
    void setSourceModel(FactTableModel & sourceModel);
    void setTextFilter(QString textFilter);

    // QSortFilterProxyModel interface
protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;

private:
    FactTableModel * factTableModel;
    QString textFilter;

};

#endif // FACTSORTFILTERPROXYMODEL_H
