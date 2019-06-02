#include "Database.h"

MYSQL* Database::execQuery(string query) {
	MYSQL* conn = mysql_init(NULL);
	if (!conn)
		throw runtime_error("Database Initialization Failed");

	conn = mysql_real_connect(conn, "db.fe.up.pt", user.c_str(),
		password.c_str(), name.c_str(), 3306, NULL, 0);

	if (!conn)
		throw runtime_error("Error Connecting to Database");

  if (mysql_query(conn, query.c_str()))
    throw runtime_error("Query failed: " + query + "\n" + string(mysql_error(conn)));

  return conn;
}

vector<vector<string>> Database::select(string table, string filter) {
	vector<vector<string>> result;
		string query = "SELECT * FROM " + table + " WHERE " + filter;

		MYSQL_RES* res;
		MYSQL* conn = execQuery(query);
		MYSQL_ROW row;

		res = mysql_store_result(conn);
		int nfields = mysql_num_fields(res);
		while (row = mysql_fetch_row(res)) {
			vector<string> results_row;
			for (int i = 0; i < nfields; i++) {
				results_row.push_back(row[i] == NULL ? "":row[i]);
			}
			result.push_back(results_row);
		}
		mysql_free_result(res);
		mysql_close(conn);
  return result;
}

void Database::insert(string table, string fields, string values) {
	string query =
      "INSERT INTO " + table + " (" + fields + ") VALUES (" + values + ")";
	mysql_close(execQuery(query));
}

void Database::update(string table, string values, string condition) {
	string query =
      "UPDATE " + table + " SET " + values + " WHERE " + condition;

	mysql_close(execQuery(query));
}

void Database::orderInit(int orderID, int nUnits) {
  insert("orders", "id, npending",
         to_string(orderID) + ", " + to_string(nUnits));
}

void Database::orderStart(int orderID) {
  update("orders", "timestart=now(), state=1", "id=" + to_string(orderID)); // TODO: Update state
}

void Database::orderUnitProcess(int orderID) {
  if (stoi(select("orders", "id=" + to_string(orderID)).at(0).at(2)) == 0)
    throw(std::runtime_error(
        "Database was requested to increase number of units "
        "in process but there is no units pending of that order"));
  update("orders", "npending = npending - 1, nprocess = nprocess + 1, state = 1",
         "id = " + to_string(orderID));
}

void Database::orderUnitEnd(int orderID) {
  if (stoi(select("orders", "id=" + to_string(orderID)).at(0).at(3)) == 0)
    throw(std::runtime_error(
        "Database was requested to increase number of units "
        "processed but there is no units in processing of that order"));
  update("orders", "nprocess = nprocess - 1, ndone = ndone + 1",
         "id = " + to_string(orderID));
  vector<string> newState = select("orders", "id=" + to_string(orderID)).at(0);
  if (stoi(newState.at(2)) == 0 && stoi(newState.at(3)) == 0) {
	  update("orders", "timeend=now(), state=2", "id=" + to_string(orderID));
  }
}

void Database::machineOperation(string machineID, int top, int unitType) {
  if (select("machine", "id = \"" + machineID + "\"").size() == 0)
    insert("machine", "id, top, n1",
           "\"" + machineID + "\", " + to_string(top) + ", 1");
  else
    update("machine", "top = top + " + to_string(top) + ", n1 = n1 + 1",
           "id = \"" + machineID + "\"");
}

void Database::unloadUnit(int pusherID, int unitType) {
  if (select("pusher", "id=" + to_string(pusherID)).size() == 0)
    insert("pusher", "id, n" + to_string(unitType),
           to_string(pusherID) + ", 1");
  else
    update("pusher",
           "n" + to_string(unitType) + " = n" + to_string(unitType) + " + 1",
           "id = " + to_string(pusherID));
}