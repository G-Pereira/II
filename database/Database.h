#ifndef II_DATABASE_H
#define II_DATABASE_H

#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <vector>

#include "configs.h"

using namespace pqxx;
using namespace std;

class Database {
public:
  void orderinit(int orderID, int nUnits);
  void orderstart(int orderID);
  void orderEnd(int orderID);
  void orderUnitProcess(int orderID);
  void orderUnitEnd(int orderID);

private:
  string name = DB_NAME;
  string user = DB_USER;
  string password = DB_PASS;

  vector<vector<string>> select(string table, string filter = "true");
  void insert(string table, string fields, string values);
  void update(string table, string values, string condition);
};

#endif // II_DATABASE_H
