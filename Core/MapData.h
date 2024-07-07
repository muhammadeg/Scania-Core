#ifndef __MAPDATA_H
#define __MAPDATA_H

void *__fastcall CIOCriticalSectionEnter(struct _RTL_CRITICAL_SECTION *a1)
{
	PRTL_CRITICAL_SECTION_DEBUG v4; // ST10_4@2
	LONG v5; // ST14_4@2
	LONG v8; // ST14_4@5
	void *result; // eax@5
	struct _RTL_CRITICAL_SECTION *lpCriticalSection; // [sp+0h] [bp-Ch]@1
	int vars0; // [sp+Ch] [bp+0h]@0
	void *retaddr; // [sp+10h] [bp+4h]@5

	if (a1->LockCount != 0) {
		lpCriticalSection = a1;
		if (!TryEnterCriticalSection(a1))
		{
			v4 = lpCriticalSection[1].DebugInfo;
			v5 = lpCriticalSection[1].LockCount;
			if (lpCriticalSection->LockCount != 0)
				EnterCriticalSection(lpCriticalSection);
		}
		v8 = *(DWORD *)(vars0 + 4);
		result = retaddr;
		lpCriticalSection[1].DebugInfo = (PRTL_CRITICAL_SECTION_DEBUG)retaddr;
		lpCriticalSection[1].LockCount = v8;
	}
	return result;
}

#include <Windows.h>

class MapData
{
private:
	std::string dbName;
	std::string Type;

public:
	MapData() { dbName = ""; };

	MapData(std::string dbName) {
		this->dbName = dbName;
		this->Type = "Integer";
		initDb();
	}

	MapData(std::string dbName, std::string Type) {
		this->dbName = dbName;
		this->Type = Type;
		initDb();
	}

	void SetupQuery(sqlite3 *db, char* zErrMsg) {
		sqlite3_exec(db, "PRAGMA cache_size = 900000", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA synchronous=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA count_changes=OFF", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA journal_mode=MEMORY", NULL, NULL, &zErrMsg);
		sqlite3_exec(db, "PRAGMA temp_store=MEMORY", NULL, NULL, &zErrMsg);
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
			SetupQuery(db, zErrMsg);

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
			SetupQuery(db, zErrMsg);
			pSQL = "create table Registration (Key " + this->Type + ", Value " + this->Type +")";
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

	std::map<int, int> toMap() {
		std::map<int, int> Map;
		sqlite3 *db;
		char *zErrMsg = 0;
		int rc; sqlite3_stmt *res;
		int value = 0;
		std::string connection = "./Database/" + this->dbName + ".db";
		rc = sqlite3_open(connection.c_str(), &db);
		if (rc) {
			sqlite3_close(db);
			return Map;
		}

		char SQL[] = "select Key,Value from Registration";

		SetupQuery(db, zErrMsg);

		sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
		rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

		if (rc != SQLITE_OK) {
			sqlite3_finalize(res);
			sqlite3_close(db);
			return Map;
		}
		
		while (rc != SQLITE_DONE) {
			rc = sqlite3_step(res);
			if (rc != SQLITE_ROW)
				break;

			Map[sqlite3_column_int(res, 0)] = sqlite3_column_int(res, 1);
		}

		sqlite3_finalize(res);
		sqlite3_exec(db, "COMMIT", NULL, NULL, &zErrMsg);
		sqlite3_close(db);

		return Map;
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

		char SQL[] = "select COUNT(Key) from Registration";

		SetupQuery(db, zErrMsg);

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
	INT PART
	**************************************/

	int find(int Key) {
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

		char SQL[] = "select Value from Registration WHERE Key = ?1";

		SetupQuery(db, zErrMsg);

		sqlite3_exec(db, "BEGIN", NULL, NULL, &zErrMsg);
		rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

		sqlite3_bind_int(res, 1, Key);
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

	void insert(int Key, int Value) {
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
			SetupQuery(db, zErrMsg);

			char* SQL = "insert into Registration VALUES (?1,?2)";
			if (this->find(Key))
				SQL = "UPDATE Registration SET Value = ?2 WHERE Key = ?1";

			rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);
			sqlite3_bind_int(res, 1, Key);
			sqlite3_bind_int(res, 2, Value);

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

	void erase(int Key) {
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
			SetupQuery(db, zErrMsg);

			char SQL[] = "DELETE from Registration WHERE Key = ?1";
			rc = sqlite3_prepare_v2(db, SQL, strlen(SQL), &res, 0);

			sqlite3_bind_int(res, 1, Key);
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