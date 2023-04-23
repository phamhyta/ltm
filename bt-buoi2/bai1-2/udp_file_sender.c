#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 40
char str[256];
char cmd[32], ipadd[20], port[5], tmp[50], file_send[50];

void input() {
    printf("Nhap lenh: ");
    fgets(str, sizeof(str), stdin);

    int ret = sscanf(str, "%s%s%s%s%s", &cmd, &ipadd, &port, &file_send, &tmp);
    if (ret < 4)
    {
        printf("ERROR thieu tham so\n");
        return ;
    }

    if (ret > 4)
    {
        printf("ERROR thua tham so\n");
        return ;
    }

    if (strcmp(cmd, "udp_file_sender") != 0)
    {
        printf("ERROR sai ma lenh\n");
        return ;
    }
}

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr;
    char filename[256];
    char buffer[BUF_SIZE];
    int bytes_read, bytes_sent;
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
    server_addr.sin_port = htons(atoi(&port));
    server_addr.sin_addr.s_addr = inet_addr(ipadd); // change this to receiver's IP address

    // open file for reading
    fp = fopen(file_send, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    // send filename
    strcat(filename, file_send);
    bytes_sent = sendto(sock, filename, strlen(filename), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bytes_sent < 0) {
        perror("Failed to send filename");
        exit(1);
    }

    // send file content
    while ((bytes_read = fread(buffer, 1, BUF_SIZE, fp)) > 0) {
        bytes_sent = sendto(sock, buffer, bytes_read, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
        if (bytes_sent < 0) {
            perror("Failed to send file content");
            exit(1);
        }
    }

    printf("File sent successfully\n");
    bytes_sent = sendto(sock, NULL, 0, 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (bytes_sent < 0) {
        printf("Error sending end of file packet.\n");
        return -1;
    }
    // close file and socket
    fclose(fp);
    close(sock);

    return 0;
}
