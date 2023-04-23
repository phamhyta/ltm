#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 40
#define PORT 9000

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr;
    char filename[256];
    char buffer[BUF_SIZE];
    int bytes_read, bytes_sent;
    FILE *fp;

    // if (argc < 2) {
    //     printf("Usage: %s send.txt\n", argv[0]);
    //     exit(1);
    // }
    // printf("aaa");

    // create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // setup server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // change this to receiver's IP address

    // open file for reading
    strcpy(filename, "send.txt");
    fp = fopen(filename, "rb");
    if (fp == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    // send filename
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
        usleep(1000); // delay for a short time to reduce sending speed
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
