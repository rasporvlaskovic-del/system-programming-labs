#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <sys/wait.h>

#define PORT 8080

void run_server() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // [cite: 78]
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed"); exit(EXIT_FAILURE); // [cite: 80]
    }
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed"); exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen failed"); exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept failed"); exit(EXIT_FAILURE);
    }

    recv(new_socket, buffer, 1024, 0);
    for(int i = 0; buffer[i]; i++){
        buffer[i] = toupper(buffer[i]);
    }
    send(new_socket, buffer, strlen(buffer), 0);
    close(new_socket);
    close(server_fd);
}

void run_client() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *hello = "hello from client";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("Socket creation error"); exit(EXIT_FAILURE);
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("Connection Failed"); exit(EXIT_FAILURE);
    }

    send(sock, hello, strlen(hello), 0);
    printf("[Клиент] Отправлено: %s\n", hello);
    recv(sock, buffer, 1024, 0);
    printf("[Клиент] Получено от сервера: %s\n", buffer);
    close(sock);
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sleep(1); // Ждем пока сервер запустится
        run_client();
        exit(0);
    } else {
        run_server();
        wait(NULL);
    }
    return 0;
}