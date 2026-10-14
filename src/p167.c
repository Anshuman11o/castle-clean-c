#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = getenv("DB_ADDRESS");
    const char *user = getenv("DB_USERNAME");
    const char *password = getenv("DB_PASSWORD");
    const char *database = getenv("DB_DATABASE");
    if (server == NULL || user == NULL || password == NULL || database == NULL) {
        printf("Missing database credentials\n");
        return 1;
    }

    conn = mysql_init(NULL);
    if (conn == NULL) {
        printf("Failed to allocate memory.\n");
        return 1;
    }

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(conn));
        return 1;
    }
    printf("Connection successful!\n");

    char id[32];
    printf("ID: ");
    fgets(id, sizeof(id), stdin);

    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT * FROM tokens WHERE id = %s", id);

    if (mysql_query(conn, sql)) {
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
