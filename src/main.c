#include "http/http.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 4201

HttpRequest httpRequest;
HttpHeader httpHeader = {
    .key = "Content-Type",
    .value = "text/plain",
};

HttpResponse httpResponse = {
    .version = "HTTP/1.1",
    .code = OK,
    .header_head = &httpHeader,
    .body = "Hello World!",
};
int main(void) {
  int sfd;
  int opt = 1;
  struct sockaddr_in addr;
  socklen_t addr_len = sizeof(addr);

  sfd = socket(AF_INET, SOCK_STREAM, 0);

  if (sfd == -1) {
    perror("failed to open socket");
    exit(EXIT_FAILURE);
  }

  if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt,
                 sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  memset(&addr, 0, addr_len);
  addr.sin_family = AF_INET;
  addr.sin_port = htons(4201);
  addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

  if (bind(sfd, (struct sockaddr *)&addr, addr_len) == -1) {
    perror("Failed to bind");
    close(sfd);
    exit(EXIT_FAILURE);
  }

  if (listen(sfd, 1) == -1) {
    perror("Failed to listen");
    close(sfd);
    exit(EXIT_FAILURE);
  }
  printf("Listening on port %d\n", PORT);

  struct sockaddr_in cl_addr;
  socklen_t cl_addr_len;
  int cfd;
  while (1) {
    puts("Waiting for connection.");
    if ((cfd = accept(sfd, (struct sockaddr *)&cl_addr, &cl_addr_len)) == -1) {
      perror("Failed to accept client");
    }
    char cl_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &cl_addr.sin_addr, cl_ip, sizeof(cl_ip));
    printf("Client connected from %s:%d\n", cl_ip, cl_addr.sin_port);

    recv_request(cfd, &httpRequest);

    //    char buffer[4096];
    //    ssize_t n = recv(cfd, buffer, sizeof(buffer) - 1, 0);
    //    if (n > 0) {
    //      buffer[n] = '\0';
    //      printf("%s", buffer);
    //    }
    send_404(cfd);
  }
}
