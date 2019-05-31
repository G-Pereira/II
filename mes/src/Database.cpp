#include "Database.h"

vector<vector<string>> Database::select(string table, string filter) {
  vector<vector<string>> result;

  PGconn* conn;
  PGresult* res;

  /* Make a connection to the database */
  conn = PQconnectdb(("host = db.fe.up.pt port = 5432 user = " + user + " password = "+ password + " dbname = " + name).c_str());

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK)
  {
	  PQfinish(conn);
	  throw std::runtime_error("Error Connecting to database");
  }

  /* Start a transaction block */
  res = PQexec(conn, "BEGIN");
  PQclear(res);
  res = PQexec(conn, ("DECLARE cur CURSOR FOR SELECT * FROM ii." + table + " WHERE " + filter).c_str());
  PQclear(res);
  res = PQexec(conn, "FETCH ALL in cur");

  for (int i = 0; i < PQntuples(res); i++)
  {
	  vector<string> row;
	  for (int j = 0; j < PQnfields(res); j++)
		row.push_back(string(PQgetvalue(res, i, j)));
	  result.push_back(row);
  }

  PQclear(res);

  /* close the portal ... we don't bother to check for errors ... */
  res = PQexec(conn, "CLOSE cur");
  PQclear(res);

  /* end the transaction */
  res = PQexec(conn, "END");
  PQclear(res);

  /* close the connection to the database and cleanup */
  PQfinish(conn);
  
  return result;
}

void Database::insert(string table, string fields, string values) {
  PGconn* conn;
  PGresult* res;

  /* Make a connection to the database */
  conn = PQconnectdb(("host = db.fe.up.pt port = 5432 user = " + user + " password = " + password + " dbname = " + name).c_str());

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK)
  {
	  PQfinish(conn);
	  throw std::runtime_error("Error Connecting to database");
  }

  /* Start a transaction block */
  res = PQexec(conn, "BEGIN");
  PQclear(res);
  res = PQexec(conn, ("DECLARE cur CURSOR FOR INSERT INTO ii." + table + " (" + fields + ") VALUES(" + values + ")").c_str());
  PQclear(res);

  /* close the portal ... we don't bother to check for errors ... */
  res = PQexec(conn, "CLOSE cur");
  PQclear(res);

  /* end the transaction */
  res = PQexec(conn, "END");
  PQclear(res);

  /* close the connection to the database and cleanup */
  PQfinish(conn);
}

void Database::update(string table, string values, string condition) {
  PGconn* conn;
  PGresult* res;

  /* Make a connection to the database */
  conn = PQconnectdb(("host = db.fe.up.pt port = 5432 user = " + user + " password = " + password + " dbname = " + name).c_str());

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(conn) != CONNECTION_OK)
  {
	  PQfinish(conn);
	  throw std::runtime_error("Error Connecting to database");
  }

  /* Start a transaction block */
  res = PQexec(conn, "BEGIN");
  PQclear(res);
  res = PQexec(conn, ("DECLARE cur CURSOR FOR UPDATE ii." + table + " SET " + values + " WHERE " + condition).c_str());
  PQclear(res);

  /* close the portal ... we don't bother to check for errors ... */
  res = PQexec(conn, "CLOSE cur");
  PQclear(res);

  /* end the transaction */
  res = PQexec(conn, "END");
  PQclear(res);

  /* close the connection to the database and cleanup */
  PQfinish(conn);
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
    throw(
        std::runtime_error("Database was requested to increase number of units "
                           "in process but there is no units pending of that order"));
  update("order", "npending = npending - 1, nprocess = nprocess + 1",
         "id=" + to_string(orderID));
}

void Database::orderUnitEnd(int orderID) {
  if (stoi(select("order", "id=" + to_string(orderID)).at(0).at(3)) == 0)
    throw(
        std::runtime_error("Database was requested to increase number of units "
                           "processed but there is no units in processing of that order"));
  update("order", "nprocess = nprocess - 1, ndone = ndone + 1",
         "id=" + to_string(orderID));
}

void Database::machineOperation(int orderID) {

}