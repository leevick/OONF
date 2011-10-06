/*
 * olsr_http.h
 *
 *  Created on: Oct 5, 2011
 *      Author: rogge
 */

#ifndef OLSR_HTTP_H_
#define OLSR_HTTP_H_

#include "common/common_types.h"
#include "common/avl.h"
#include "common/string.h"

#include "core/olsr_stream_socket.h"
#include "core/olsr_netaddr_acl.h"

#define OLSR_HTTP_MAX_HEADERS 16
#define OLSR_HTTP_MAX_FORMS 8
#define OLSR_HTTP_MAX_QUERIES 8
#define OLSR_HTTP_MAX_URI_LENGTH 256

enum olsr_http_result {
  HTTP_200_OK = 200,
  HTTP_400_BAD_REQ = 400,
  HTTP_401_UNAUTHORIZED = 401,
  HTTP_403_FORBIDDEN = STREAM_REQUEST_FORBIDDEN,
  HTTP_404_NOT_FOUND = 404,
  HTTP_413_REQUEST_TOO_LARGE = STREAM_REQUEST_TOO_LARGE,
  HTTP_501_NOT_IMPLEMENTED = 501,
  HTTP_503_SERVICE_UNAVAILABLE = STREAM_SERVICE_UNAVAILABLE,
};

struct olsr_http_session {
  const char *method; /* get/post/... */
  const char *request_uri;
  const char *http_version;

  char *header_name[OLSR_HTTP_MAX_HEADERS];
  char *header_value[OLSR_HTTP_MAX_HEADERS];
  size_t header_count;

  /* parameter of the URI for GET */
  char *query_name[OLSR_HTTP_MAX_QUERIES];
  char *query_value[OLSR_HTTP_MAX_QUERIES];
  size_t query_count;

  /* parameter of the URI for POST */
  char *form_name[OLSR_HTTP_MAX_FORMS];
  char *form_value[OLSR_HTTP_MAX_FORMS];
  size_t form_count;

  /* content type for answer, NULL means plain/html */
  const char *content_type;
};

struct olsr_http_handler {
  struct avl_node node;

  /* path of filename of content */
  const char *site;

  /* set by olsr_http_add to true if site is a directory */
  bool directory;

  /* list of base64 encoded name:password combinations */
  struct strarray auth;

  /* list of IP addresses/ranges this site can be accessed from */
  struct olsr_netaddr_acl acl;

  /* pointer to static content and length in bytes */
  const char *content;
  size_t content_size;

  /* callback for custom generated content (called if content==NULL) */
  enum olsr_http_result (*content_handler)(
      struct autobuf *out, struct olsr_http_session *);
};

void olsr_http_init(void);
void olsr_http_cleanup(void);

EXPORT void olsr_http_add(struct olsr_http_handler *);
EXPORT void olsr_http_remove(struct olsr_http_handler *);

EXPORT const char *olsr_http_get_value(char **keys, char **values,
    size_t count, const char *key);
#endif /* OLSR_HTTP_H_ */