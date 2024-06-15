#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 5000
#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

int client_sockets[MAX_CLIENTS] = {0};
pthread_mutex_t lock;

void *client_handler(void *socket_desc) {
    int sock = *(int *)socket_desc;
    char buffer[BUFFER_SIZE];
    int read_size;

    while ((read_size = recv(sock, buffer, BUFFER_SIZE, 0)) > 0) {
        // Send the message to all clients
        pthread_mutex_lock(&lock);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] != 0) {
                write(client_sockets[i], buffer, strlen(buffer));
            }
        }
        pthread_mutex_unlock(&lock);
    }

    if (read_size == 0 || read_size == -1) {
        int i;
        pthread_mutex_lock(&lock);
        for (i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] == sock) {
                client_sockets[i] = 0;
                break;
            }
        }
        pthread_mutex_unlock(&lock);
    }

    free(socket_desc);
    close(sock);
    return NULL;
}

int main() {
    int server_fd, new_socket, *new_sock;
    struct sockaddr_in server, client;
    socklen_t client_size = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Could not create socket");
        return 1;
    }

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed");
        return 1;
    }

    // Listen
    listen(server_fd, 3);

    // Accept incoming connections
    puts("Waiting for incoming connections...");
    while ((new_socket = accept(server_fd, (struct sockaddr *)&client, &client_size))) {
        printf("Connection accepted from %s:%d\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        pthread_mutex_lock(&lock);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (client_sockets[i] == 0) {
                client_sockets[i] = new_socket;
                break;
            }
        }
        pthread_mutex_unlock(&lock);

        new_sock = malloc(1);
        *new_sock = new_socket;
        if (pthread_create(&thread_id, NULL, client_handler, (void*) new_sock) < 0) {
            perror("could not create thread");
            return 1;
        }
    }

    if (new_socket < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}