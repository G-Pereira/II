#include "Database.h"

vector<vector<string>> Database::select(string table, string filter) {
  string query = "SELECT * FROM ii." + table + " WHERE " + filter;
  vector<vector<string>> res;

  try {
    connection C("dbname = sinfa23 user = " + user + " password = " + password +
                 " hostaddr = 192.168.50.131 port = 5432");

    nontransaction N(C);

    result R(N.exec(query));

    for (auto line : R) {
      vector<string> row;
      for (auto value : line) {
        row.push_back(value.as<string>());
      }
      res.push_back(row);
    }
    C.disconnect();
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
    return vector<vector<string>>();
  }
  return res;
}

void Database::insert(string table, string fields, string values) {
  string query =
      "INSERT INTO ii." + table + " (" + fields + ") VALUES (" + values + ")";

  try {
    connection C("dbname = " + name + " user = " + user + " password = " +
                 password + " hostaddr = 10.227.240.130 port = 5432");
    work W(C);
    W.exec(query);
    W.commit();
    C.disconnect();
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
    return;
  }
}

void Database::update(string table, string values, string condition) {
  string query =
      "UPDATE ii." + table + " SET " + values + " WHERE " + condition;
  try {
    connection C("dbname = " + name + " user = " + user + " password = " +
                 password + " hostaddr = 10.227.240.130 port = 5432");
    work W(C);
    W.exec(query);
    W.commit();
    C.disconnect();
  } catch (const std::exception &e) {
    cerr << e.what() << std::endl;
    return;
  }
}

void Database::orderinit(int orderID, int nUnits) {
  insert("order", "id, npending",
         to_string(orderID) + ", " + to_string(nUnits));
}

void Database::orderstart(int orderID) {
  update("order", "timestart=now(), state=1", "id=" + to_string(orderID));
}

void Database::orderEnd(int orderID) {
  update("order", "timeend=now(), state=2", "id=" + to_string(orderID));
}

void Database::orderUnitProcess(int orderID) {
  update("order", "npending = npending - 1, nprocess = nprocess + 1",
         "id=" + to_string(orderID));
}

void Database::orderUnitEnd(int orderID) {
  if (stoi(select("order", "id=" + to_string(orderID)).at(0).at(3)) == 0)
    throw(
        std::runtime_error("Database was requested to increase number of units "
                           "processed but there is no units in processing"));
  update("order", "nprocess = nprocess - 1, ndone = ndone + 1",
         "id=" + to_string(orderID));
}