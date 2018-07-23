#include "DataAcces.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>

DataAcces * DataAcces::instance = NULL;

DataAcces::DataAcces(void)
{
    if (sqlite3_open_v2("../maBDD", &db, SQLITE_OPEN_READWRITE, NULL) != SQLITE_OK)
	{
        std::cerr<<sqlite3_errmsg(db)<<std::endl;
        exit(-1);
	} else {
		std::cout<<"Database opened"<<std::endl;
	}
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

void DataAcces::getAllFacts(std::vector<Fact*> & vecFacts)
{
    sqlite3_stmt * statement;
    const char * requete = "SELECT * FROM fact";
    int ret = sqlite3_prepare_v2(db, requete, strlen(requete), &statement, NULL);
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

void DataAcces::getFacts(const TimeHour &begin, const TimeHour &end)
{
    assert(false && "DataAcces::getFacts is not implemented.");
}

bool DataAcces::deleteFact(const Fact & factToDelete)
{
    sqlite3_stmt * statement;
    const char * requete = "DELETE FROM fact WHERE id=?";
    int ret = sqlite3_prepare_v2(db, requete, strlen(requete), &statement, NULL);
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
        sprintf(requete, "UPDATE %s SET %s=?, %s=?, %s=?, %s=? WHERE id=?", TABLE_FACT, TABLE_FACT_COLUMN_STARTTIME, TABLE_FACT_COLUMN_ENDTIME, TABLE_FACT_COLUMN_TITLE, TABLE_FACT_COLUMN_DESCRIPTION);

        int ret = sqlite3_prepare_v2(db, requete, strlen(requete), &statement, NULL);
        if (ret != SQLITE_OK) {
            std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
            exit(-1);
        } else {
            std::string paramStartTime = factToUpdate.getStartTime().toString();
            int rc = sqlite3_bind_text(statement, 1, paramStartTime.c_str(), paramStartTime.size(), SQLITE_STATIC);

            std::string paramEndtTime = factToUpdate.getEndTime().toString();
            rc = sqlite3_bind_text(statement, 2, paramEndtTime.c_str(), paramEndtTime.size(), SQLITE_STATIC);

            std::string paramTitle = factToUpdate.getTitle();
            rc = sqlite3_bind_text(statement, 3, paramTitle.c_str(), paramTitle.size(), SQLITE_STATIC);

            std::string paramDescription = factToUpdate.getDescription();
            rc = sqlite3_bind_text(statement, 4, paramDescription.c_str(), paramDescription.size(), SQLITE_STATIC);

            rc = sqlite3_bind_int(statement, 5, factToUpdate.getId());

            rc = sqlite3_step(statement);

            rc = sqlite3_finalize(statement);

            return true;
        }
    }
    return false;

}

bool DataAcces::recreateDatabase()
{
    assert(false && "DataAcces::recreateDatabase is not implemented.");

    // TODO


    sqlite3_stmt * statement;

    const char * creationReq = "CREATE TABLE 'Fact'('startTime' DateTime NOT NULL, 'endTime' DateTime NOT NULL)";
    //'title'	varchar(100),
    //'description'	varchar(1000),
    //'id'	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE


    int ret = sqlite3_prepare_v2(db, creationReq, strlen(creationReq), &statement, NULL);
    if (ret != SQLITE_OK) {
        std::cerr<<"Error on slite3_prepare_v2"<<std::endl;
        exit(-1);
    }

    sqlite3_step(statement);

    sqlite3_finalize(statement);

    return false;
}

void DataAcces::getDatesBounds(TimeHour &minimumStartDate, TimeHour &maximumEndDate)
{
    //minimumStartDate.set(1999, 01, 01, 00, 00, 00);
    //maximumEndDate.set(2039, 12, 31, 23, 59, 59);

    sqlite3_stmt * statement;
    char requete[256];
    sprintf(requete, "SELECT %s FROM %s ORDER BY %s ASC LIMIT 1", TABLE_FACT_COLUMN_STARTTIME, TABLE_FACT, TABLE_FACT_COLUMN_STARTTIME);
    int ret = sqlite3_prepare_v2(db, requete, strlen(requete), &statement, NULL);
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
    ret = sqlite3_prepare_v2(db, requete, strlen(requete), &statement, NULL);
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

void DataAcces::insertFact(Fact & newFact)
{
	std::cout<<"insertFact"<<std::endl;
    std::cout<<newFact.getStartTime().toString();

	sqlite3_stmt * statement;

    char insertReq[256];
    sprintf(insertReq, "INSERT INTO %s (%s, %s, %s, %s) VALUES (?, ?, ?, ?)", TABLE_FACT, TABLE_FACT_COLUMN_STARTTIME, TABLE_FACT_COLUMN_ENDTIME, TABLE_FACT_COLUMN_TITLE, TABLE_FACT_COLUMN_DESCRIPTION);
    int rc = sqlite3_prepare_v2(db, insertReq, strlen(insertReq), &statement, NULL);

    std::string paramStartTime = newFact.getStartTime().toString();
    rc = sqlite3_bind_text(statement, 1, paramStartTime.c_str(), paramStartTime.size(), SQLITE_STATIC);

    std::string paramEndtTime = newFact.getEndTime().toString();
    rc = sqlite3_bind_text(statement, 2, paramEndtTime.c_str(), paramEndtTime.size(), SQLITE_STATIC);

    std::string paramTitle = newFact.getTitle();
    rc = sqlite3_bind_text(statement, 3, paramTitle.c_str(), paramTitle.size(), SQLITE_STATIC);

    std::string paramDescription = newFact.getDescription();
    rc = sqlite3_bind_text(statement, 4, paramDescription.c_str(), paramDescription.size(), SQLITE_STATIC);
	
    rc = sqlite3_step(statement);

    rc = sqlite3_finalize(statement);

    // retrieve new id field (auto increment) :
    char req[256];
    sprintf(req, "SELECT seq FROM sqlite_sequence WHERE name='%s'", TABLE_FACT);
    rc = sqlite3_prepare_v2(db, req, strlen(req), &statement, NULL);

    rc = sqlite3_step(statement);
    if ( rc == SQLITE_ROW)
    {
        int val = sqlite3_column_int(statement, 0);
        newFact.setId(val);
    }

    rc = sqlite3_finalize(statement);
	
}

void DataAcces::databaseStatementToFact(sqlite3_stmt * statement, Fact * fact)
{
	int year, month, day, hour, minute, second;

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
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		fact->setStartTime(year, month, day, hour, minute, second);
	} else {
		std::cout<<"No value"<<std::endl;
	}

    val = sqlite3_column_text(statement, Columns_Fact_Table::endField);
	if (val != 0){
        std::cout<<"Field "<<Columns_Fact_Table::endField<<" = "<<val<<std::endl;
		sscanf((const char *)val, "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
		fact->setEndTime(year, month, day, hour, minute, second);
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
}

