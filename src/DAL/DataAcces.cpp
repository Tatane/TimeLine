#include "DataAcces.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iomanip>
#include <sstream>
#include <qfile>
#include <qmessagebox>
#include <qtextstream>

#include "ACategory.h"

DataAcces * DataAcces::instance = NULL;

DataAcces::DataAcces()
	: db(nullptr)
{
}

std::string DataAcces::convertDateTimeToStorageString(const ADateTime & dateTime) const
{
	char buf[256];
	sprintf(buf, "%d-%d-%d %d:%d:%d", dateTime.year(), dateTime.month(), dateTime.day(), dateTime.hour(), dateTime.minute(), dateTime.seconde());
	return std::string(buf);
}

ADateTime DataAcces::convertStorageStringToDateTime(std::string str) const
{
	int year, month, day, hour, minute, second;
	sscanf(str.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);

	ADateTime ret;
	ret.set(year, month, day, hour, minute, second);

	return ret;
}

DataAcces* DataAcces::getInstance()
{
	if (instance == NULL)
	{
		instance = new DataAcces();
	}

	return instance;
}

DataAcces::~DataAcces(void)
{
}

bool DataAcces::open()
{
	return (sqlite3_open_v2("maBDD", &db, SQLITE_OPEN_READWRITE, NULL) == SQLITE_OK);
}

void DataAcces::getAllFacts(std::vector<Fact*> & vecFacts)
{
    sqlite3_stmt * statement;
    const char * requete = "SELECT * FROM Fact";
    int ret = sqlite3_prepare_v2(db, requete, static_cast<int>(strlen(requete)), &statement, NULL);
    if (ret != SQLITE_OK) {
        std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
        exit(-1);
    }

    while (sqlite3_step(statement) == SQLITE_ROW){
        Fact * fact = new Fact;
        databaseStatementToFact(statement, fact);
        vecFacts.push_back(fact);
    }

    sqlite3_finalize(statement);
}

void DataAcces::getFacts(const ADateTime &/*begin*/, const ADateTime &/*end*/)
{
    assert(false && "DataAcces::getFacts is not implemented.");
}

bool DataAcces::deleteFact(const Fact & factToDelete)
{
    sqlite3_stmt * statement;
    const char * requete = "DELETE FROM fact WHERE id=?";
    int ret = sqlite3_prepare_v2(db, requete, static_cast<int>(strlen(requete)), &statement, NULL);
    if (ret != SQLITE_OK) {
        std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
        exit(-1);
    } else {
        if (sqlite3_bind_int(statement, 1, factToDelete.getId()) == SQLITE_OK) {
            sqlite3_step(statement);
            sqlite3_finalize(statement);
            return true;
        } else {
            std::cerr<<"Error on sqlite3_bind_int"<<std::endl;
            exit(-1);
        }
    }
    return false;
}

bool DataAcces::updateFact(const Fact & factToUpdate)
{
    if (factToUpdate.getId() > 0) {

        sqlite3_stmt * statement;

        char requete[256];
        sprintf(requete, "UPDATE %s SET %s=?, %s=?, %s=?, %s=?, %s=? WHERE id=?", TABLE_FACT, TABLE_FACT_COLUMN_STARTTIME, TABLE_FACT_COLUMN_ENDTIME, TABLE_FACT_COLUMN_TITLE, TABLE_FACT_COLUMN_DESCRIPTION, TABLE_FACT_COLUMN_CATEGORYID);

        int ret = sqlite3_prepare_v2(db, requete, static_cast<int>(strlen(requete)), &statement, NULL);
        if (ret != SQLITE_OK) {
            std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
            exit(-1);
        } else {
            std::string paramStartTime = convertDateTimeToStorageString(factToUpdate.getStartTime());
            int rc = sqlite3_bind_text(statement, 1, paramStartTime.c_str(), static_cast<int>(paramStartTime.size()), SQLITE_STATIC);

            std::string paramEndtTime = convertDateTimeToStorageString(factToUpdate.getEndTime());
            rc = sqlite3_bind_text(statement, 2, paramEndtTime.c_str(), static_cast<int>(paramEndtTime.size()), SQLITE_STATIC);

            std::string paramTitle = factToUpdate.getTitle();
            rc = sqlite3_bind_text(statement, 3, paramTitle.c_str(), static_cast<int>(paramTitle.size()), SQLITE_STATIC);

            std::string paramDescription = factToUpdate.getDescription();
            rc = sqlite3_bind_text(statement, 4, paramDescription.c_str(), static_cast<int>(paramDescription.size()), SQLITE_STATIC);

			rc = sqlite3_bind_int(statement, 5, factToUpdate.getCategory()->getId());

            rc = sqlite3_bind_int(statement, 6, factToUpdate.getId());
			
            rc = sqlite3_step(statement);

            rc = sqlite3_finalize(statement);

            return true;
        }
    }
    return false;

}

bool DataAcces::createDatabase()
{
	QFile fileScriptDatabaseCreation(".\\scriptDatabaseCreation.sql");
	if (!fileScriptDatabaseCreation.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(nullptr, "Error", "Cannot find SQL scheme script for database creation.");
		return false;
	}
	
	QTextStream textStream(&fileScriptDatabaseCreation);
	QString creationReq = textStream.readAll();


	if (sqlite3_open_v2("./maBDD", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL) != SQLITE_OK)
	{
		QMessageBox::information(nullptr, "Error", "Cannot create database file.");
		return false;
	}

    sqlite3_stmt * statement;

	std::string sReq = creationReq.trimmed().toStdString();
	const char * req = sReq.c_str();
	const char * pzTail = req;

	while (!QString(pzTail).trimmed().isEmpty())
	{
		sReq = QString(pzTail).trimmed().toStdString();
		req = sReq.c_str();

		//int ret = sqlite3_prepare_v2(db, req, creationReq.size(), &statement, pzTail);
		int ret = sqlite3_prepare_v2(db, req, creationReq.size(), &statement, &pzTail);
		if (ret != SQLITE_OK) {
			std::cerr << "Error on slite3_prepare_v2" << std::endl;
			QMessageBox::information(nullptr, "Error", "Error creating database.");
			sqlite3_close_v2(db);
			QFile(".\\maBDD").remove();
			exit(-1);
		}

		int err = sqlite3_step(statement);
		err = sqlite3_finalize(statement);
	} 

    return true;
}

void DataAcces::getDatesBounds(ADateTime &minimumStartDate, ADateTime &maximumEndDate)
{
    //minimumStartDate.set(1999, 01, 01, 00, 00, 00);
    //maximumEndDate.set(2039, 12, 31, 23, 59, 59);

    sqlite3_stmt * statement;
    char requete[256];
    sprintf(requete, "SELECT %s FROM %s ORDER BY %s ASC LIMIT 1", TABLE_FACT_COLUMN_STARTTIME, TABLE_FACT, TABLE_FACT_COLUMN_STARTTIME);
    int ret = sqlite3_prepare_v2(db, requete, static_cast<int>(strlen(requete)), &statement, NULL);
    if (ret != SQLITE_OK) {
        std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
        exit(-1);
    }

    while (sqlite3_step(statement) == SQLITE_ROW){
        int year, month, day, hour, minute, second;
        const unsigned char * val = sqlite3_column_text(statement, 0);
        if (val != 0){
            sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            minimumStartDate.set(year, month, day, hour, minute, second);
        } else {
            std::cout<<"No value"<<std::endl;
        }
    }

    sprintf(requete, "SELECT %s FROM %s ORDER BY %s DESC LIMIT 1", TABLE_FACT_COLUMN_ENDTIME, TABLE_FACT, TABLE_FACT_COLUMN_ENDTIME);
    ret = sqlite3_prepare_v2(db, requete, static_cast<int>(strlen(requete)), &statement, NULL);
    if (ret != SQLITE_OK) {
        std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
        exit(-1);
    }

    while (sqlite3_step(statement) == SQLITE_ROW){
        int year, month, day, hour, minute, second;
        const unsigned char * val = sqlite3_column_text(statement, 0);
        if (val != 0){
            sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
            maximumEndDate.set(year, month, day, hour, minute, second);
        } else {
            std::cout<<"No value"<<std::endl;
        }
    }

    sqlite3_finalize(statement);

}

void DataAcces::getAllCategories(ACategoriesCollection * categories)
{
	sqlite3_stmt * statement;
	const char * requete = "SELECT * FROM Category";
	int ret = sqlite3_prepare_v2(db, requete, static_cast<int>(strlen(requete)), &statement, NULL);
	if (ret != SQLITE_OK) {
		std::cerr << "Error on slite3_prepare_v2" << std::endl;
		exit(-1);
	}

	while (sqlite3_step(statement) == SQLITE_ROW) {
		std::unique_ptr<ACategory> category = databaseStatementToCategory(statement);
		if (category.get() != nullptr)
		{
			(*categories)[category->getId()] = std::move(category);
		}
	}

	sqlite3_finalize(statement);
}

void DataAcces::insertCategory(std::shared_ptr<ACategory>& category)
{
	sqlite3_stmt * statement;

	char requete[256];
	sprintf(requete, "INSERT INTO %s (%s) VALUES (?)", TABLE_CATEGORY, TABLE_CATEGORY_COLUMN_NAME);
	int rc = sqlite3_prepare_v2(db, requete, static_cast<int>(strlen(requete)), &statement, nullptr);

	rc = sqlite3_bind_text(statement, 1, category->getName().c_str(), static_cast<int>(strlen(category->getName().c_str())), SQLITE_TRANSIENT);

	rc = sqlite3_step(statement);

	rc = sqlite3_finalize(statement);

	// retrieve new id field (auto increment) :
	char req[256];
	sprintf(req, "SELECT seq FROM sqlite_sequence WHERE name='%s'", TABLE_CATEGORY);
	rc = sqlite3_prepare_v2(db, req, static_cast<int>(strlen(req)), &statement, NULL);

	rc = sqlite3_step(statement);
	if (rc == SQLITE_ROW)
	{
		int val = sqlite3_column_int(statement, Columns_Category_Table::idField);
		category->setId(val);
	}

	rc = sqlite3_finalize(statement);
}

void DataAcces::insertFact(Fact & newFact)
{
	std::cout<<"insertFact"<<std::endl;
    std::cout<<convertDateTimeToStorageString(newFact.getStartTime());

	sqlite3_stmt * statement;

    char insertReq[256];
    sprintf(insertReq, "INSERT INTO %s (%s, %s, %s, %s, %s) VALUES (?, ?, ?, ?, ?)", TABLE_FACT, TABLE_FACT_COLUMN_STARTTIME, TABLE_FACT_COLUMN_ENDTIME, TABLE_FACT_COLUMN_TITLE, TABLE_FACT_COLUMN_DESCRIPTION, TABLE_FACT_COLUMN_CATEGORYID);
    int rc = sqlite3_prepare_v2(db, insertReq, static_cast<int>(strlen(insertReq)), &statement, NULL);

    std::string paramStartTime = convertDateTimeToStorageString(newFact.getStartTime());
    rc = sqlite3_bind_text(statement, 1, paramStartTime.c_str(), static_cast<int>(paramStartTime.size()), SQLITE_STATIC);

    std::string paramEndtTime = convertDateTimeToStorageString(newFact.getEndTime());
    rc = sqlite3_bind_text(statement, 2, paramEndtTime.c_str(), static_cast<int>(paramEndtTime.size()), SQLITE_STATIC);

    std::string paramTitle = newFact.getTitle();
    rc = sqlite3_bind_text(statement, 3, paramTitle.c_str(), static_cast<int>(paramTitle.size()), SQLITE_STATIC);

    std::string paramDescription = newFact.getDescription();
    rc = sqlite3_bind_text(statement, 4, paramDescription.c_str(), static_cast<int>(paramDescription.size()), SQLITE_STATIC);

	int paramCategoryId = 0; // 0 by default.
	if (newFact.getCategory() != nullptr)
	{
		paramCategoryId = newFact.getCategory()->getId();
	}
	rc = sqlite3_bind_int(statement, 5, paramCategoryId);

    rc = sqlite3_step(statement);

    rc = sqlite3_finalize(statement);

    // retrieve new id field (auto increment) :
    char req[256];
    sprintf(req, "SELECT seq FROM sqlite_sequence WHERE name='%s'", TABLE_FACT);
    rc = sqlite3_prepare_v2(db, req, static_cast<int>(strlen(req)), &statement, NULL);

    rc = sqlite3_step(statement);
    if ( rc == SQLITE_ROW)
    {
        int val = sqlite3_column_int(statement, Columns_Fact_Table::idField);
        newFact.setId(val);
    }

    rc = sqlite3_finalize(statement);
	
}

void DataAcces::databaseStatementToFact(sqlite3_stmt * statement, Fact * fact)
{
    const unsigned char * val = sqlite3_column_text(statement, Columns_Fact_Table::idField);
    if (val != 0){
        int id = 0;
        std::cout<<"Field "<<Columns_Fact_Table::idField<<" = "<<val<<std::endl;
        sscanf((const char *)val, "%d", &id);
        fact->setId(id);
    } else {
        std::cout<<"No value"<<std::endl;
    }

    val = sqlite3_column_text(statement, Columns_Fact_Table::startField);
	if (val != 0){
        std::cout<<"Field "<<Columns_Fact_Table::startField<<" = "<<val<<std::endl;
		ADateTime startDateTime = convertStorageStringToDateTime((const char *) val);
		fact->setStartTime(startDateTime);
	} else {
		std::cout<<"No value"<<std::endl;
	}

    val = sqlite3_column_text(statement, Columns_Fact_Table::endField);
	if (val != 0){
        std::cout<<"Field "<<Columns_Fact_Table::endField<<" = "<<val<<std::endl;
		ADateTime endDateTime = convertStorageStringToDateTime((const char *)val);
		fact->setEndTime(endDateTime);
	} else {
		std::cout<<"No value"<<std::endl;
	}

    val = sqlite3_column_text(statement, Columns_Fact_Table::titleField);
    if (val != 0){
        std::cout<<"Field "<<Columns_Fact_Table::titleField<<" = "<<val<<std::endl;
        //sscanf((const char*)val, "%s")
        fact->setTitle((const char*)val);
    }

    val = sqlite3_column_text(statement, Columns_Fact_Table::descriptionField);
    if (val != 0){
        std::cout<<"Field "<<Columns_Fact_Table::descriptionField<<" = "<<val<<std::endl;
        //sscanf((const char*)val, "%s")
        fact->setDescription((const char*)val);
    }

	int valInt = sqlite3_column_int(statement, Columns_Fact_Table::categoryIdField);
	if (valInt != 0) { // HOW TO CHECK RESULT VALIDITY ?
		std::cout << "Field " << Columns_Fact_Table::categoryIdField << " = " << valInt << std::endl;
		//sscanf((const char*)val, "%s")
		if (ACategories::getCategories().count(valInt) == 1)
		{

			std::shared_ptr<ACategory> & category = ACategories::getCategories().at(valInt);
			fact->setCategory(category);
		}
	}
}

std::unique_ptr<ACategory> DataAcces::databaseStatementToCategory(sqlite3_stmt * stmt)
{
	std::unique_ptr<ACategory> category = std::make_unique<ACategory>();

	const unsigned char * val = sqlite3_column_text(stmt, Columns_Category_Table::idField);
	if (val != 0) {
		int id = 0;
		std::cout << "Field " << Columns_Category_Table::idField << " = " << val << std::endl;
		sscanf((const char *)val, "%d", &id);
		category->setId(id);
	}
	else {
		std::cout << "No value" << std::endl;
	}

	val = sqlite3_column_text(stmt, Columns_Category_Table::nameField);
	if (val != 0) {
		std::cout << "Field " << Columns_Category_Table::nameField << " = " << val << std::endl;
		category->setName((const char*)val);
	}

	return category;
}

