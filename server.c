#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define MAX_QUEUED_REQUESTS 10
#define BUFFER_SIZE 1024

void handle_client(int client) {
  char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

  ssize_t bytes_received = recv(client, buffer, BUFFER_SIZE, 0);

  if (bytes_received <= 0)
    goto _close;

  printf("%s\n", buffer);

  char *reply = "HTTP/1.1 200 OK\n"
                "\n"
                "Success!";

  send(client, reply, strlen(reply), 0);

_close:
  close(client);
  free(buffer);
}

int main() {
  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  int server;

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    fprintf(stderr, "Error: %s - failed to create socket\n", strerror(errno));
    exit(1);
  }

  setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int));

  if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    fprintf(stderr, "Error: %s - failed to bind server\n", strerror(errno));
    exit(1);
  }

  if (listen(server, MAX_QUEUED_REQUESTS) < 0) {
    fprintf(stderr, "Error: %s - failed to listen\n", strerror(errno));
    exit(1);
  }

  printf("Server running at port %d\n\n", PORT);

  while (1) {
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int *client = malloc(sizeof(int));

    if ((*client = accept(server, (struct sockaddr *)&client_addr,
                          &client_addr_len)) < 0) {
      fprintf(stderr, "Failed to accept client request:(\n");
      continue;
    }
    handle_client(*client);
  }
}
