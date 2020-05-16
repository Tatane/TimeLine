#ifndef FACTTABLEMODEL_H
#define FACTTABLEMODEL_H

#include <QAbstractTableModel>
#include <POCO/Fact.h>


class FactTableModel : public QAbstractTableModel
{
public:
    FactTableModel();
    FactTableModel(std::vector<Fact *> *vecFacts);

    void setVectFacts(std::vector<Fact*> * iVecFacts);


    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex & = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    void rowAppened();
    void rowRemoved(int row);

    class DataColumn
    {
    public:
        enum {
            StartTime,
            Endtime,
            Title,
            Description
        };
    };

private:
    std::vector<Fact*> * vecFacts;
};

#endif // FACTTABLEMODEL_H
