#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

char str[256];
char cmd[16], ip[50], port[5], tmp[50];

void input() {
    printf("Nhap lenh: ");
    fgets(str, sizeof(str), stdin);

    int ret = sscanf(str, "%s%s%s%s", &cmd, &ip, &port, &tmp);
    if (ret < 3)
    {
        printf("ERROR thieu tham so\n");
        return ;
    }

    if (ret > 3)
    {
        printf("ERROR thua tham so\n");
        return ;
    }

    if (strcmp(cmd, "tcp_client") != 0)
    {
        printf("ERROR sai ma lenh\n");
        return ;
    }
}
int main()
{
    input();

    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(&ip);
    addr.sin_port = htons(atoi(&port));

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }

    char buf[256];
    ret = recv(client, buf, sizeof(buf), 0);
    if (ret <= 0)
    {
        printf("Connection closed\n");
        return 1;
    }

    if (ret < sizeof(buf))
        buf[ret] = 0;
    printf("Server: %s\n", buf);

    while (1)
    {
        printf("Enter string:");
        fgets(buf, sizeof(buf), stdin);

        send(client, buf, strlen(buf), 0);

        if (strncmp(buf, "exit", 4) == 0)
            break;
    }

    close(client);
}