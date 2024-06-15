#ifndef DB_CONNECT_H
#define DB_CONNECT_H

#include <mysql/mysql.h>

MYSQL* db_connect(void);
void db_disconnect(MYSQL *conn);

#endif
