#include "facttablemodel.h"
#include <QFont>
#include "AlxColors.h"
#include <QDateTime>

FactTableModel::FactTableModel()
    : vecFacts(nullptr)
{

}

FactTableModel::FactTableModel(std::vector<Fact*> * vec)
    : vecFacts(vec)
{

}

void FactTableModel::setVectFacts(std::vector<Fact *> * iVecFacts)
{
    vecFacts = iVecFacts;
}

int FactTableModel::rowCount(const QModelIndex &) const
{
    return vecFacts->size();
}

int FactTableModel::columnCount(const QModelIndex &parent) const
{
    return 4;
}

QVariant FactTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        Fact* fact = vecFacts->at(index.row());

        switch (index.column()) {

        case DataColumn::StartTime :
			return QVariant(fact->getStartTime().toString().c_str());
            break;
        case DataColumn::Endtime :
            return QVariant(fact->getEndTime().toString().c_str());
            break;
        case DataColumn::Title :
            return QVariant(fact->getTitle().c_str());
            break;
        case DataColumn::Description :
            return QVariant(fact->getDescription().c_str());
            break;
        default:
            return QVariant();
            break;
        }
    }
    else if (role == Qt::BackgroundColorRole)
    {
        if (index.row() % 2 == 0)
        {
            return QVariant(AlxColors::COLOR_2);
        }
        else
        {
            return QVariant(AlxColors::COLOR_3);
        }
    }
    else
    {
        return QVariant();
    }

    return QVariant();
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


QVariant FactTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        switch (section) {

		case DataColumn::StartTime:
            return QVariant("START");
            break;
		case DataColumn::Endtime:
            return QVariant("END");
            break;
		case DataColumn::Title:
            return QVariant("TITLE");
            break;
		case DataColumn::Description:
            return QVariant("DESCRIPTION");
            break;
        default:
            return QVariant();
            break;
        }
    }
    else if (role == Qt::FontRole) {
        QFont font;
        font.setBold(true);
        return QVariant(font);
    }
    else
    {
        return QVariant();
    }
}

