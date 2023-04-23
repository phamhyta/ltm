#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 40
char str[256];
char cmd[32], port[5], tmp[50];

void input() {
    printf("Nhap lenh: ");
    fgets(str, sizeof(str), stdin);

    int ret = sscanf(str, "%s%s%s", &cmd, &port, &tmp);
    if (ret < 2)
    {
        printf("ERROR thieu tham so\n");
        return ;
    }

    if (ret > 2)
    {
        printf("ERROR thua tham so\n");
        return ;
    }

    if (strcmp(cmd, "udp_file_receiver") != 0)
    {
        printf("ERROR sai ma lenh\n");
        return ;
    }
}


int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char filename[256];
    char buffer[BUF_SIZE];
    int bytes_received, bytes_written;
    FILE *fp;
    input();

    // create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // setup server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(atoi(&port));

    // bind socket to port
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind socket");
        exit(1);
    }

    printf("Listening on port %s...\n", port);

    while (1) {
        char ndsend[1024] = "";
        // receive filename
        memset(filename, 0, sizeof(filename));
        client_addr_len = sizeof(client_addr);
        bytes_received = recvfrom(sock, filename, sizeof(filename), 0, (struct sockaddr*)&client_addr, &client_addr_len);
        if (bytes_received < 0) {
            perror("Failed to receive filename");
            continue;
        }

        printf("Receiving file: %s\n", filename);

        // receive file content
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            bytes_received = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_addr_len);
            printf("Receiving: %s \n", buffer);
            if (bytes_received < 0) {
                perror("Failed to receive file content");
                break;
            } else if (bytes_received == 0) {
                // end of file
                break;
            }
            
            strcat(ndsend, buffer);
        }

        printf("File nhận được: %s\n", ndsend);
        int count = 0;
        char *p = strstr(ndsend, "0123456789");
        while (p != NULL) {
            count++;
            p = strstr(p+1, "0123456789");
        }
        printf("So lan xuat hien cua chuoi '123456789' la: %d\n", count);
        printf("File received successfully\n");
        // close file
    }

    // close socket
    close(sock);

    return 0;
}
