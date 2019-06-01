#include "Database.h"

MYSQL *Database::execQuery(string query) {
  MYSQL *conn = mysql_init(NULL);

  if (!conn)
    throw runtime_error("Database Initialization Failed");

  conn = mysql_real_connect(conn, "10.227.240.130", user.c_str(),
                            password.c_str(), name.c_str(), 3306, NULL, 0);

  if (!conn)
    throw runtime_error("Error Connecting to Database");

  if (mysql_query(conn, query.c_str()))
    throw runtime_error("Query failed: " + string(mysql_error(conn)));

  return conn;
}

vector<vector<string>> Database::select(string table, string filter) {
  string query = "SELECT * FROM ii." + table + " WHERE " + filter;

  MYSQL_RES *res;
  MYSQL *conn = execQuery(query);
  MYSQL_ROW row;

  vector<vector<string>> result;

  res = mysql_store_result(conn);
  uint8_t nfields = mysql_num_fields(res);
  while (row = mysql_fetch_row(res)) {
    vector<string> results_row;
    for (uint8_t i = 0; i < nfields; i++) {
      results_row.push_back(row[i]);
    }
    result.push_back(results_row);
  }
  return result;
}

void Database::insert(string table, string fields, string values) {
  string query =
      "INSERT INTO ii." + table + " (" + fields + ") VALUES (" + values + ")";

  MYSQL *conn = execQuery(query);
}

void Database::update(string table, string values, string condition) {
  string query =
      "UPDATE ii." + table + " SET " + values + " WHERE " + condition;

  MYSQL *conn = execQuery(query);
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
  if (stoi(select("order", "id=" + to_string(orderID)).at(0).at(2)) == 0)
    throw(std::runtime_error(
        "Database was requested to increase number of units "
        "in process but there is no units pending of that order"));
  update("order", "npending = npending - 1, nprocess = nprocess + 1",
         "id = " + to_string(orderID));
}

void Database::orderUnitEnd(int orderID) {
  if (stoi(select("order", "id=" + to_string(orderID)).at(0).at(3)) == 0)
    throw(std::runtime_error(
        "Database was requested to increase number of units "
        "processed but there is no units in processing of that order"));
  update("order", "nprocess = nprocess - 1, ndone = ndone + 1",
         "id = " + to_string(orderID));
}

void Database::machineOperation(string machineID, int top) {
  if (select("machine", "id=" + machineID).size() == 0)
    insert("machine", "id, top, nunits",
           machineID + ", " + to_string(top) + ", 1");
  else
    update("machine", "top = top + " + to_string(top) + ", nunits = nunits + 1",
           "id = " + machineID);
}

void Database::unloadUnit(int pusherID, int unitType) {
  if (select("pusher", "id=" + to_string(pusherID)).size() == 0)
    insert("pusher", "id, n" + to_string(unitType),
           to_string(pusherID) + ", 1");
  else
    update("pusher",
           "n" + to_string(unitType) + " = n" + to_string(unitType) + " + 1",
           "id = " + pusherID);
}