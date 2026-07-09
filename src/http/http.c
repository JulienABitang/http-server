#include "http.h"
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int send_response(int client_fd, HttpResponse *reps) {
  char header_buff[14000] = {'\0'};
  char *buff_ptr = header_buff;
  HttpHeader *hdr = reps->header_head;

  while (hdr != NULL) {
    memcpy(buff_ptr, hdr->key, strlen(hdr->key));
    buff_ptr += strlen(hdr->key);
    memcpy(buff_ptr, ": ", 2);
    buff_ptr += 2;
    memcpy(buff_ptr, hdr->value, strlen(hdr->value));
    buff_ptr += strlen(hdr->value);
    memcpy(buff_ptr, "\r\n", 2);
    hdr = hdr->next;
  }

  char *buff;

  asprintf(&buff, "%s %d\r\n%s\r\n%s\r\n", reps->version, reps->code,
           header_buff, reps->body);

  send(client_fd, buff, strlen(buff), 0);
  close(client_fd);
  return strlen(buff);
}

void send_404(int client_fd) {
  HttpResponse _404_response = {
      .version = "HTTP/2.1",
      .code = NOT_FOUND,
      .header_head = NULL,
      .body = "\0",
  };
  send_response(client_fd, &_404_response);
}

/**
 * http_request_parse_ws
 *
 * parses a http request for each whitespace, not including whitespaces.
 *
 * @param[in] char * request the buffer containing the http request.
 * @param[out] char * dest the buffer to put the parsed field in.
 * @param[in] int n the maximum amount of characters to put into dest.
 *
 * @return char * the whitespace character landed on?
 * @return NULL if newline/null byte/EOF encountered.
 */
char *http_request_parse(char *req, char *dest, const char *delim, int n) {
  char *ptr = strtok(req, delim);
  if ((ptr - req) > n) {
    return NULL;
  }
  strncpy(dest, req, n);
  return ptr;
}

int recv_request(int client_fd, HttpRequest *req) {
  char buff[32000] = {'\0'};
  int length = recv(client_fd, buff, sizeof(buff), 0);
  printf("received request!\n%s\n--------\n Begin Parsing...\n", buff);

  char *end = http_request_parse(buff, req->method, " \t", HTTPMSG_METHOD_MAX);
  printf("Parsed Method: %s\n", req->method);

  end = http_request_parse(end, req->uri, " \t", HTTPMSG_URI_MAX);
  printf("Parsed URI: %s\n", req->uri);

  end = http_request_parse(end, req->version, "\n", HTTPMSG_VERSION_MAX);
  printf("Parsed Version: %s\n", req->version);

  return length;
}
