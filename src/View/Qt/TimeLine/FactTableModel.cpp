#include "facttablemodel.h"

FactTableModel::FactTableModel(std::vector<Fact*> * vec)
    : vecFacts(vec)
{

}

FactTableModel::FactTableModel(std::map<int, Fact*> * map)
    : mapFacts(map)
{

}

int FactTableModel::rowCount(const QModelIndex &parent) const
{
    return vecFacts->size();
    //return mapFacts->size();
}

int FactTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant FactTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    Fact* fact = vecFacts->at(index.row());

    switch (index.column()) {

    case 0:
        return QVariant(fact->getStartTime().toString().c_str());
        break;
    case 1:
        return QVariant(fact->getEndTime().toString().c_str());
        break;
    case 2:
        return QVariant(fact->getTitle().c_str());
        break;
    case 3:
        return QVariant(fact->getDescription().c_str());
        break;
    default:
        return QVariant();
        break;
    }


}

void FactTableModel::rowAppened()
{
    beginInsertRows(QModelIndex(), vecFacts->size()-1, vecFacts->size()-1);
    endInsertRows();
}

void FactTableModel::rowRemoved(int row)
{
    beginRemoveRows(QModelIndex(), row, row);
    endRemoveRows();
}
