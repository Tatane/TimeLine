#include "FactSortFilterProxyModel.h"
#include "AConfigManager.h"

FactSortFilterProxyModel::FactSortFilterProxyModel(std::unique_ptr<FactTableModel> & model)
    :mFactTableModel(model)
    ,mTextFilter("")
    ,mStartDateFilter(QDate(1900,1,1))
    ,mEndDateFilter(QDate(2100, 1, 1))
{
	setSourceModel(mFactTableModel.get());
}

void FactSortFilterProxyModel::setTextFilter(QString textFilter)
{
    beginResetModel();
    this->mTextFilter = textFilter;
    endResetModel();
}

void FactSortFilterProxyModel::setDatesFilter(QDate startDate, QDate endDate)
{
    beginResetModel();
    this->mStartDateFilter = startDate;
    this->mEndDateFilter = endDate;
    endResetModel();
}

bool FactSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    QModelIndex indexDescription = sourceModel()->index(source_row, FactTableModel::DataColumn::Description, source_parent);
    QString description = sourceModel()->data(indexDescription).toString();

    QModelIndex indexTitle = sourceModel()->index(source_row, FactTableModel::DataColumn::Title, source_parent);
    QString title = sourceModel()->data(indexTitle).toString();

    QModelIndex indexStartTime = sourceModel()->index(source_row, FactTableModel::DataColumn::StartTime, source_parent);
	QDateTime factStartTime = QDateTime::fromString(sourceModel()->data(indexStartTime).toString(), AConfigManager::getDateTimeDisplayFormat().c_str());

    QModelIndex indexEndTime = sourceModel()->index(source_row, FactTableModel::DataColumn::Endtime, source_parent);
    QDateTime factEndTime =QDateTime::fromString(sourceModel()->data(indexEndTime).toString(), AConfigManager::getDateTimeDisplayFormat().c_str());

    if ( (mTextFilter.isEmpty() || description.contains(mTextFilter, Qt::CaseInsensitive) || title.contains(mTextFilter, Qt::CaseInsensitive))
		&& factStartTime.date() >= mStartDateFilter
		&& factEndTime.date() <= mEndDateFilter
    ) {
        return true;
    } else {
        return false;
    }
}

void FactSortFilterProxyModel::rowAppened()
{
    mFactTableModel->rowAppened();
}

void FactSortFilterProxyModel::rowRemoved(int row)
{
    mFactTableModel->rowRemoved(row);
}

