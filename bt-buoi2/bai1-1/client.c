#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
    int client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(9000);

    int ret = connect(client, (struct sockaddr *)&addr, sizeof(addr));
    if (ret == -1)
    {
        perror("connect() failed");
        return 1;
    }

    char arr[100][1000];
    char name[10];
    int numbuer_disk;
    char buf[256];
    printf("Vui long nhap thong tin: \n");
    printf("Ten may: ");
    fgets(name, sizeof(name), stdin);
    printf("So o dia: ");
    scanf("%d", &numbuer_disk);
    for(int i = 0;i < numbuer_disk; i++) {
        char temp[30];
        fgets(temp, sizeof(temp), stdin);
        sprintf(buf, "%s %s", buf, temp);
    }
    // Gui mang sang server
    send(client, buf, sizeof(buf), 0);
    printf("buf: %s", buf);
    
    close(client);
}