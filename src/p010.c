#include <stdio.h>
#include <stdlib.h>

int main() {
    char ip[46];

    printf("Enter the IP address to ping: ");
    fgets(ip, sizeof(ip), stdin);

    char command[150];
    snprintf(command, sizeof(command), "ping %s", ip);

    system(command);

    return 0;
}
