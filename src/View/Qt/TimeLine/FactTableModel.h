#ifndef FACTTABLEMODEL_H
#define FACTTABLEMODEL_H

#include <QAbstractTableModel>
#include <POCO/Fact.h>


class FactTableModel : public QAbstractTableModel
{
public:
    FactTableModel(std::vector<Fact *> & vecFacts);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void rowAppened();
    void rowRemoved(int row);

private:
    std::vector<Fact*> * vecFacts;
};

#endif // FACTTABLEMODEL_H