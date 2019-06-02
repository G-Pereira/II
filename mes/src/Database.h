#ifndef II_DATABASE_H
#define II_DATABASE_H

#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>

#include "configs.h"

using namespace std;

class Database {
public:
  Database(bool cleanDB = true);
  void orderInit(int orderID, int nUnits);
  void orderStart(int orderID);
  void orderUnitProcess(int orderID);
  void orderUnitEnd(int orderID);
  void machineOperation(string machineID, int top, int unitType = 1);
  void unloadUnit(int pusherID, int unitType);

private:
  string name = DB_NAME;
  string user = DB_USER;
  string password = DB_PASS;

  MYSQL* execQuery(string query);
  vector<vector<string>> select(string table, string filter = "true");
  void insert(string table, string fields, string values);
  void update(string table, string values, string condition);
  void _delete(string table, string condition);
};

#endif // II_DATABASE_H
