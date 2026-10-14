#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sqlite3.h>

int isValidUsername(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isalpha(input[i])) {
            return 0;
        }
    }
    return 1;
}

int isValidPassword(char *input) {
    for (int i = 0; i < strlen(input); i++) {
        if (!isalpha(input[i]) && !isdigit(input[i])) {
            return 0;
        }
    }
    return 1;
}

int main() {
    sqlite3 *db;
    sqlite3_stmt *res;
    int rc;

    rc = sqlite3_open("users.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    char username[32];
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    char password[32];
    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    if (isValidUsername(username) == 0 || isValidPassword(password) == 0) {
        fprintf(stderr, "Username or password is not valid\n");
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "INSERT INTO users (username, password) VALUES (?, ?);";

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_text(res, 1, username, -1, SQLITE_STATIC);
    sqlite3_bind_text(res, 2, password, -1, SQLITE_STATIC);

    rc = sqlite3_step(res);

    if (rc != SQLITE_DONE) {
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Record inserted successfully.\n");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}
