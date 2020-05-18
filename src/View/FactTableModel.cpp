#include "View/FactTableModel.h"
#include <QFont>
#include "AlxColors.h"
#include <QDateTime>
#include "POCO/AConfigManager.h"

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
    return static_cast<int>(vecFacts->size());
}

int FactTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return 5;
}

QString convertDateTimeToDisplayString(ADateTime dateTime, QString format)
{
	QDateTime dt(QDate(dateTime.year(), dateTime.month(), dateTime.day()), QTime(dateTime.hour(), dateTime.minute(), dateTime.seconde()));
	return dt.toString(format);
}

QVariant FactTableModel::data(const QModelIndex &index, int role) const
{
    if (role == Qt::DisplayRole)
    {
        Fact* fact = vecFacts->at(index.row());

        switch (index.column()) {

        case DataColumn::StartTime :
		{
			QString format = AConfigManager::getDateTimeDisplayFormat().c_str();
			return QVariant(convertDateTimeToDisplayString(fact->getStartTime(), format));
			break;
		}
        case DataColumn::Endtime :
		{
			QString format = AConfigManager::getDateTimeDisplayFormat().c_str();
			return QVariant(convertDateTimeToDisplayString(fact->getEndTime(), format));
			break;
		}
        case DataColumn::Title :
            return QVariant(fact->getTitle().c_str());
            break;
        case DataColumn::Description :
            return QVariant(fact->getDescription().c_str());
            break;
        case DataColumn::Categories :
        {
            QString val;
            for(auto category : fact->getCategories())
            {
                val.append(category->getName().c_str());
            }
            return val;
            break;
        }
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
	int index = static_cast<int>(vecFacts->size() - 1);
    beginInsertRows(QModelIndex(), index, index);
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
    /*else if (role == Qt::FontRole) {
        QFont font;
        font.setBold(true);
        return QVariant(font);
    }*/
    else
    {
        return QVariant();
    }
}

