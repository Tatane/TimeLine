#include "facttablemodel.h"

FactTableModel::FactTableModel(std::vector<Fact*> * vec)
    : vecFacts(vec)
{

}


int FactTableModel::rowCount(const QModelIndex &parent) const
{
    return vecFacts->size();
}

int FactTableModel::columnCount(const QModelIndex &parent) const
{
    return 3;
}

QVariant FactTableModel::data(const QModelIndex &index, int role) const
{
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    Fact* fact = vecFacts->at(index.row());

    switch (index.column()) {
    case 0:
        return QVariant(fact->getDescription().c_str());
        break;
    case 1:
        return QVariant(fact->getStartTime().toString().c_str());
        break;
    default:
        return QVariant();
        break;
    }


}
