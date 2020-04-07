/**
 * @brief http-parser callbacks & types
 * 
 * @file http_parser_callbacks.h
 */

#ifndef HTTP_PARSER_CALLBACKS_H
#define HTTP_PARSER_CALLBACKS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* Includes -------------------------------------------- */
#include "http_parser.h"

/* Defines --------------------------------------------- */
#define HTTP_PARSER_MAX_HEADERS 10U
#define HTTP_PARSER_MAX_ELEMENT_SIZE 500U

/* Type definitions ------------------------------------ */
typedef enum _lastHeaderElement {
    NONE = 0U,
    FIELD,
    VALUE
} lastHeaderElement_t;

typedef struct message {
    const char *name; // for debugging purposes
    const char *raw;
    enum http_parser_type type;
    int method;
    int status_code;
    char request_path[HTTP_PARSER_MAX_ELEMENT_SIZE];
    char request_uri[HTTP_PARSER_MAX_ELEMENT_SIZE];
    char fragment[HTTP_PARSER_MAX_ELEMENT_SIZE];
    char query_string[HTTP_PARSER_MAX_ELEMENT_SIZE];
    char body[HTTP_PARSER_MAX_ELEMENT_SIZE];
    int num_headers;
    lastHeaderElement_t last_header_element;
    char headers [HTTP_PARSER_MAX_HEADERS][2][HTTP_PARSER_MAX_ELEMENT_SIZE];
    int should_keep_alive;

    int message_begin_cb_called;
    int headers_complete_cb_called;
    int message_complete_cb_called;

    char url[HTTP_PARSER_MAX_ELEMENT_SIZE];
} httpMessage_t;

/* Forward declarations -------------------------------- */

/* http-parser callback initialization ----------------- */
int httpParserCallbackInit(http_parser_settings * const pSettings);

int httpParserCallbackMessageSetter(httpMessage_t * const pMsg);

/* http-parser callbacks ------------------------------- */
int requestPathCb(http_parser *pParser, const char *p, size_t pLen);

int requestURICb(http_parser *pParser, const char *p,size_t pLen);

int queryStringCb(http_parser *pParser, const char *p,size_t pLen);

int urlStringCb(http_parser *pParser, const char *p, size_t pLen);

int fragmentCb(http_parser *pParser, const char *p,size_t pLen);

int headerFieldCb(http_parser *pParser, const char *p,size_t pLen);

int headerValueCb(http_parser *pParser, const char *p,size_t pLen);

int bodyCb(http_parser *pParser, const char *p,size_t pLen);

int messageCompleteCb(http_parser *pParser);

int messageBeginCb(http_parser *pParser);

int headersCompleteCb(http_parser *pParser);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HTTP_PARSER_CALLBACKS_H */
