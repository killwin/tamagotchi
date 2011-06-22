#ifndef SQL

#define SQL 1

#include <mysql++.h>
#include <ssqls.h>

#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

class Sql {
	
   public :
      Sql(string db, string serv, string u, string p);
      bool insert_new(vector<string> & values);
	
   private :
      string database, server, user, pass;
    
   protected :
      mysqlpp::Connection *conn;
};

#endif
