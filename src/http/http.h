#ifndef HTTP_H
#define HTTP_H

// These are all arbitrary.
#define HTTPMSG_BODY_MAX 14000 // body size max 14kB
#define HTTPMSG_VERSION_MAX 64 // version max 64 characters
#define HTTPMSG_METHOD_MAX 255
#define HTTPMSG_URI_MAX 2048

typedef enum {
  CONTINUE = 100,
  SWITCHING_PROTOCOLS = 101,
  PROCESSING = 102,
  EARLY_HINT = 103,
  //
  OK = 200,
  CREATED = 201,
  ACCEPTED = 202,
  NON_AUTHORIZED_INFORMATION = 203,
  NO_CONTENT = 204,
  RESET_CONENT = 205,
  PARTIAL_CONENT = 206,
  MULTI_STATUS = 207,
  ALREADY_REPORTED = 208,
  IM_USED = 226,
  //
  MULTIPLE_CHOICE = 300,
  MOVED_PERMANENTLY = 301,
  FOUND = 302,
  SEE_OTHER = 303,
  NOT_MOTIFIED = 304,
  TEMPORARY_REDIREACT = 307,
  PERMANENT_REDIRECT = 308,
  //
  BAD_REQUEST = 400,
  UNAUTHORIZED = 401,
  PAYMENT_REQUIRED = 402,
  FORBIDDEN = 403,
  NOT_FOUND = 404,
  METHOD_NOT_ALLOWED = 405,
  NOT_ACCEPTABLE = 406,
  PROXY_AUTH_REQ = 407,
  REQUEST_TIMEOUT = 408,
  CONFLICT = 409,
  GONE = 410,
  LENGTH_REQUIRED = 411,
  PRECONDITION_FAILED = 412,
  CONTENT_TOO_LARGE = 413,
  URI_TOO_LONG = 414,
  UNSUPPORTED_MEDIA_TYPE = 415,
  RANGE_NOT_SATISFIABLE = 416,
  EXCEPTION_FAILED = 417,
  //
  INTERNAL_SERVER_ERROR = 500,
  NOT_IMPLEMENTED = 501,
  BAD_GATEWAY = 502,
  HTTP_VERSION_NOT_SUPPORTED = 505
} ResponseCode;

typedef struct httpheader_s {
  char *key;
  char *value;
  struct httpheader_s *next;

} HttpHeader;

typedef struct {
  char version[HTTPMSG_VERSION_MAX + 1];
  ResponseCode code;
  HttpHeader *header_head;
  char body[HTTPMSG_BODY_MAX + 1];
} HttpResponse;

typedef struct {
  char method[HTTPMSG_METHOD_MAX + 1];
  char version[HTTPMSG_VERSION_MAX + 1];
  char uri[HTTPMSG_URI_MAX + 1];
  HttpHeader *header_head;
  char body[HTTPMSG_BODY_MAX + 1];
} HttpRequest;

int send_response(int client_fd, HttpResponse *reps);
void send_404(int client_fd);
int recv_request(int client_fd, HttpRequest *req);

#endif
