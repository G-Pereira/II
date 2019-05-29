#include <iostream>
#include "Database.h"

vector<vector<string>> Database::Select(string table, string filter) {
  string query = "SELECT * FROM ii." + table + " WHERE " + filter;
  connection C(
    "dbname = sinfa23 user = " + user + " password = " + password + " hostaddr = 192.168.50.131 port = 5432");
  vector<vector<string>> res;

  nontransaction N(C);

  result R(N.exec(query));

  for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
    vector<string> row;
    int i;
    for (i = 0; i < c.size(); i++) {
      row.push_back(c[i].as<string>());
    }
    res.push_back(row);
  }
  C.disconnect();
  return res;
}

void Database::Insert(string table, string fields, string values) {
  string query = "INSERT INTO ii." + table + " (" + fields + ") VALUES (" + values + ")";
  connection C(
    "dbname = " + name + " user = " + user + " password = " + password + " hostaddr = 192.168.50.131 port = 5432");
  work W(C);
  W.exec(query);
  W.commit();
  C.disconnect();
}

void Database::Update(string table, string values, string condition){
  string query = "UPDATE ii." + table + " SET " + values + " WHERE " + condition;
  connection C(
    "dbname = " + name + " user = " + user + " password = " + password + " hostaddr = 192.168.50.131 port = 5432");
  work W(C);
  W.exec(query);
  W.commit();
  C.disconnect();
}
