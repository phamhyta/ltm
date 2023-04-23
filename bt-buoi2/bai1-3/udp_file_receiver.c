#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define BUF_SIZE 4096
#define PORT 9000

int main(int argc, char *argv[]) {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len;
    char filename[256];
    char buffer[BUF_SIZE];
    int bytes_received, bytes_written;
    FILE *fp;

    // create socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Failed to create socket");
        exit(1);
    }

    // setup server address
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(PORT);

    // bind socket to port
    if (bind(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind socket");
        exit(1);
    }

    printf("Listening on port %d...\n", PORT);

    while (1) {
        // receive filename
        memset(filename, 0, sizeof(filename));
        client_addr_len = sizeof(client_addr);
        bytes_received = recvfrom(sock, filename, sizeof(filename), 0, (struct sockaddr*)&client_addr, &client_addr_len);
        if (bytes_received < 0) {
            perror("Failed to receive filename");
            continue;
        }

        printf("Receiving file: %s\n", filename);

        // open file for writing
        fp = fopen("receive.txt", "wb");
        if (fp == NULL) {
            perror("Failed to open file");
            continue;
        }

        // receive file content
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            bytes_received = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr*)&client_addr, &client_addr_len);
            if (bytes_received <= 0) {
                perror("Failed to receive file content");
                break;
            } else if (bytes_received == 0) {
                // end of file
                break;
            }
            bytes_written = fwrite(buffer, 1, bytes_received, fp);
            if (bytes_written < bytes_received) {
                perror("Failed to write file content");
                break;
            }
        }

        printf("File received successfully\n");

        // close file
        fclose(fp);
    }

    // close socket
    close(sock);

    return 0;
}
