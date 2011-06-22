#include "sql.h"

sql_create_2(client, 1, 2,
mysqlpp::sql_char, name,
mysqlpp::sql_char, passwd)

sql_create_1(tama, 1, 0,
mysqlpp::sql_char, name)

sql_create_2(obj_tama_client, 1, 2,
mysqlpp::sql_int, id_client,
mysqlpp::sql_int, id_tama)

Sql::Sql(string db, string serv, string u, string p) : database(db), server(serv), user(u), pass(p)
{

   // Connect to the database.
   conn = new mysqlpp::Connection(false);
   try {
      conn->connect(database.c_str(), server.c_str(), user.c_str(), pass.c_str());
   }
   catch (const mysqlpp::Exception& er) {
      cerr << "SQL connect error: " << er.what() << endl;
      throw string("SQL connect error");
   }
   cout << "Connected to " << server.c_str() << endl;
}

bool Sql::insert_new(vector<string> & values) {

   string req;

   client row_client(values[0], values[1]);
   tama row_tama(values[2]);

   try {
      mysqlpp::Query query = conn->query();
      mysqlpp::Transaction trans(*conn);

      // client name exists ?
      req = "select id from client where name = '" + values[0] + "'";      
      query.store(req);

      if(query.affected_rows())
         return false;

      // insert names into client and tama
      query.insert(row_client);
      query.execute();
      query.insert(row_tama);
      query.execute();
      
      // get client.id and tama.id
      req = "select client.id, tama.id from client, tama where client.name = '" + values[0] + "' and tama.name = '" + values[2] + "'";
      mysqlpp::StoreQueryResult res = query.store(req);

      if(!res)
         throw string("-1- Failed to get item list");

      // insert client.id and tama.id into obj_tama_client table
      obj_tama_client row_obj_tama_client(res[0][0], res[0][1]);
      query.reset();
      query.insert(row_obj_tama_client);
      query.execute();
      
      trans.commit();

      cout << "insert client name and tama name OK" << endl;

   }
   catch (const mysqlpp::BadQuery& er) {
      cerr << "SQL bad query: " << er.what() << endl;
      throw string("SQL bad query");
   }
   catch (const mysqlpp::BadConversion& er) {
      cerr << "SQL bad conversion: " << er.what() << endl;
      throw string("SQL bad conversion");
   }
   catch (const mysqlpp::Exception& er) {
      cerr << "SQL error: " << er.what() << endl;
      throw string("SQL error");
   }
   catch(string &caught) {
	   cerr << caught << endl;
	   throw;
   }

   return true;
}
