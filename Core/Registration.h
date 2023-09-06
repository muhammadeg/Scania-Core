#ifndef __REGISTER_H
#define __REGISTER_H

#include <Windows.h>

class Registration
{
private:
	std::string dbName;
	std::string Type;
	

public:
	Registration() { dbName = ""; };

	Registration(std::string dbName) {
		this->dbName = dbName;
		this->Type = "Integer";
		initDb();
	}

	Registration(std::string dbName, std::string Type) {
		this->dbName = dbName;
		this->Type = Type;
		initDb();
	}

	void clear() {
		sqlite3 *db;
		char *zErrMsg = 0;
		const char *pSQL;
		int rc;
		sqlite3_config(SQLITE_CONFIG_SERIALIZED);
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);

		if (rc)
		{
			sqlite3_close(db);
			return;
		}
		else
		{
			sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

			pSQL = "DELETE FROM Registration";
			rc = sqlite3_exec(db, pSQL, NULL, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				sqlite3_free(zErrMsg);
			}
		}
		sqlite3_close(db);
		return;
	}

	void createDb() {
		sqlite3 *db;
		char *zErrMsg = 0;
		std::string pSQL;
		int rc;
		sqlite3_config(SQLITE_CONFIG_SERIALIZED);
		
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc)
		{
			sqlite3_close(db);
			return;
		}
		else
		{
			sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

			pSQL = "create table Registration (PID "+this->Type+")";
			rc = sqlite3_exec(db, pSQL.c_str(), NULL, 0, &zErrMsg);
			if (rc != SQLITE_OK)
			{
				sqlite3_free(zErrMsg);
			}
		}
		sqlite3_close(db);
		return;
	}

	void initDb() {
		std::ifstream infile("./Database/" + this->dbName + ".db");
		if (!infile.good())
			this->createDb();
	}

	std::vector<int> toVector() {
		std::vector<int> vect;
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc; sqlite3_stmt *res;
		int value = 0;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return vect;
		}

		char SQL[] = "select PID from Registration";

		sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

		sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
		rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

		if (rc != SQLITE_OK) {
			sqlite3_finalize(res);
			sqlite3_close(db);
			return vect;
		}

		while (rc != SQLITE_DONE) {
			rc = sqlite3_step(res);
			if (rc != SQLITE_ROW)
				break;

			vect.push_back(sqlite3_column_int(res, 0));
		}

		sqlite3_finalize(res);
		sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		sqlite3_close(db);

		return vect;
	}

	int size() {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc; sqlite3_stmt *res;
		int value = 0;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return false;
		}

		char SQL[] = "select COUNT(PID) from Registration";

		sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

		sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
		rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

		if (rc != SQLITE_OK) {
			sqlite3_finalize(res);
			sqlite3_close(db);
			return 0;
		}

		rc = sqlite3_step(res);

		if (rc == SQLITE_ROW)
			value = sqlite3_column_int(res, 0);

		sqlite3_finalize(res);
		sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		sqlite3_close(db);
		return value;
	}

	/**************************************
		STRING PART
	**************************************/
	bool count(std::string PID) {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc; sqlite3_stmt *res;
		int value = 0;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return false;
		}

		char SQL[] = "select PID from Registration WHERE PID = ?1";

		sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

		sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
		rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

		sqlite3_bind_text(res, 1, PID.c_str(),PID.length(),SQLITE_TRANSIENT);
		if (rc != SQLITE_OK) {
			sqlite3_finalize(res);
			sqlite3_close(db);
			return false;
		}

		rc = sqlite3_step(res);

		if (rc == SQLITE_ROW)
			value = sqlite3_column_int(res, 0);

		sqlite3_finalize(res);
		sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		sqlite3_close(db);

		if (value)
			return true;

		return false;
	}

	void insert(std::string PID) {
		sqlite3 *db;
		char *zErrMsg = 0; sqlite3_stmt *res;
		std::string connection = "./Database/" + this->dbName + ".db";
		int rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return;
		}
		else
		{
			sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

			char SQL[] = "insert into Registration VALUES (?1)";

			rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);
			sqlite3_bind_text(res, 1, PID.c_str(),PID.length(), SQLITE_TRANSIENT);

			if (rc != SQLITE_OK)
			{
				sqlite3_free(zErrMsg);
				sqlite3_finalize(res);
				sqlite3_close(db);
				return;
			}
		}

		rc = sqlite3_step(res);
		sqlite3_finalize(res);

		sqlite3_close(db);

		return;
	}

	void erase(std::string PID) {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		sqlite3_stmt *res;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return;
		}
		else
		{
			sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

			char SQL[] = "DELETE from Registration WHERE PID = ?1";
			rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

			sqlite3_bind_text(res, 1, PID.c_str(), PID.length(), SQLITE_TRANSIENT);
			if (rc != SQLITE_OK)
			{
				sqlite3_free(zErrMsg);
				sqlite3_finalize(res);
				sqlite3_close(db);
				return;
			}
			rc = sqlite3_step(res);

		}
		sqlite3_finalize(res);
		sqlite3_close(db);


		return;
	}

	/**************************************
		INT PART
	**************************************/

	bool count(int PID) {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc; sqlite3_stmt *res;
		int value = 0;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return false;
		}

		char SQL[] = "select PID from Registration WHERE PID = ?1";

		sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

		sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
		rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

		sqlite3_bind_int(res, 1, PID);
		if (rc != SQLITE_OK) {
			sqlite3_finalize(res);
			sqlite3_close(db);
			return false;
		}

		rc = sqlite3_step(res);

		if (rc == SQLITE_ROW)
			value = sqlite3_column_int(res, 0);

		sqlite3_finalize(res);
		sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		sqlite3_close(db);

		if (value)
			return true;

		return false;
	}

	int randomSelect() {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc; sqlite3_stmt *res;
		int value = 0;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return false;
		}

		char SQL[] = "select PID from Registration ORDER BY RANDOM() LIMIT 1";

		sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

		sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
		rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

		if (rc != SQLITE_OK) {
			sqlite3_finalize(res);
			sqlite3_close(db);
			return false;
		}

		rc = sqlite3_step(res);

		if (rc == SQLITE_ROW)
			value = sqlite3_column_int(res, 0);

		sqlite3_finalize(res);
		sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		sqlite3_close(db);

		return value;
	}

	void insert(int PID) {
		sqlite3 *db;
		char *zErrMsg = 0; sqlite3_stmt *res;
		std::string connection = "./Database/" + this->dbName + ".db";
		int rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return;
		}
		else
		{
			sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

			char SQL[] = "insert into Registration VALUES (?1)";

			rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);
			sqlite3_bind_int(res, 1, PID);

			if (rc != SQLITE_OK)
			{
				sqlite3_free(zErrMsg);
				sqlite3_finalize(res);
				sqlite3_close(db);
				return;
			}
		}

		rc = sqlite3_step(res);
		sqlite3_finalize(res);

		sqlite3_close(db);

		return;
	}

	void erase(int PID) {
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc;
		sqlite3_stmt *res;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return;
		}
		else
		{
			sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
			sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);

			char SQL[] = "DELETE from Registration WHERE PID = ?1";
			rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

			sqlite3_bind_int(res, 1, PID);
			if (rc != SQLITE_OK)
			{
				sqlite3_free(zErrMsg);
				sqlite3_finalize(res);
				sqlite3_close(db);
				return;
			}
			rc = sqlite3_step(res);

		}
		sqlite3_finalize(res);
		sqlite3_close(db);


		return;
	}
};

#endif