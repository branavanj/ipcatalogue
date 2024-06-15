#include "db_connect.h"
#include <stdio.h>

// Définition des informations de connexion en tant que constantes
static const char *server = "86.246.138.2";
static const char *user = "esgi";
static const char *password = "esgi"; // Remplacez par votre mot de passe réel
static const char *database = "projetc";


MYSQL* db_connect() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return NULL;
    }

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection Error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return NULL;
    }

    return conn;
}

void db_disconnect(MYSQL *conn) {
    mysql_close(conn);
}


