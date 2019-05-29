#ifndef II_DATABASE_H
#define II_DATABASE_H

#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <vector>

#include "configs.h"

using namespace pqxx;
using namespace std;

class Database {
public:
  void initOrder(int orderID, int nUnits);
  void startOrder(int orderID);
  void endOrder(int orderID);

private:
  string name = DB_NAME;
  string user = DB_USER;
  string password = DB_PASS;

  vector<vector<string>> select(string table, string filter = "true");
  void insert(string table, string fields, string values);
  void update(string table, string values, string condition);
};


#endif //II_DATABASE_H
