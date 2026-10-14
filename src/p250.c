#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "192.168.0.166";
    const char *user = "www-user";
    const char *password = "F7Kl009SamH53";
    const char *database = "tokenstore";

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        return 1;
    }

    if (mysql_query(conn, "SELECT id, token FROM tokens")) {
        fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
        return 1;
    }

    res = mysql_store_result(conn);

    int num_fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        unsigned long *lengths;
        lengths = mysql_fetch_lengths(res);
        for(int i = 0; i < num_fields; i++) {
            printf("[%.*s] ", (int) lengths[i],
                    row[i] ? row[i] : "NULL");
        }
        printf("\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}
