#ifndef II_DATABASE_H
#define II_DATABASE_H

#include <pqxx/pqxx>
#include <string>
#include <cstdlib>
#include <vector>
#include <string>

#include "configs.h"

using namespace pqxx;
using namespace std;

class Database {
public:
  vector<vector<string>> Select(string table, string filter = "true");
  void Insert(string table, string fields, string values);

private:
  string name = DB_NAME;
  string user = DB_USER;
  string password = DB_PASS;
};


#endif //II_DATABASE_H
