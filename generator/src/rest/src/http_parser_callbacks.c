/**
 * @brief http-parser callbacks & types implementation
 * 
 * @file http_parser_callbacks.c
 */

/* Includes -------------------------------------------- */
#include "http_parser.h"
#include "http_parser_callbacks.h"

/* C system */
#include <stdio.h>
#include <string.h>

/* Defines --------------------------------------------- */

/* Type definitions ------------------------------------ */

/* Static variables ------------------------------------ */
static httpMessage_t *sMsg = NULL;

/* http-parser callback initialization ----------------- */
int httpParserCallbackInit(http_parser_settings * const pSettings) {
    /* Check if the settings arg is NULL */
    if(NULL == pSettings) {
        fprintf(stderr, "[ERROR] <httpParserCallbackInit> HTTP Parser settings arg is NULL\n");
        return 1;
    }

    /* Set the callbacks */
    pSettings->on_message_begin     = messageBeginCb;
    pSettings->on_header_field      = headerFieldCb;
    pSettings->on_header_value      = headerValueCb;
#if 0 /* This section is deprecated */
    pSettings->on_path              = requestPathCb;
    pSettings->on_uri               = requestURICb;
    pSettings->on_fragment          = fragmentCb;
    pSettings->on_query_string      = queryStringCb;
#endif /* 0 : Deprecated section */
    pSettings->on_body              = bodyCb;
    pSettings->on_headers_complete  = headersCompleteCb;
    pSettings->on_message_complete  = messageCompleteCb;

    pSettings->on_url               = urlStringCb;
    pSettings->on_status = NULL;
    pSettings->on_chunk_header = NULL;
    pSettings->on_chunk_complete = NULL;

    return 0;
}

int httpParserCallbackMessageSetter(httpMessage_t * const pMsg) {
    /* Check if the message is NULL */
    if(NULL == pMsg) {
        fprintf(stderr, "[ERROR] <requestPathCb> HTTP message arg is NULL\n");
        return 1;
    }

    sMsg = pMsg;

    return 0;
}

/* http-parser callbacks ------------------------------- */
int requestPathCb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <requestPathCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <requestPathCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    strncat(sMsg->request_path, p, pLen);

    return 0;
}

int requestURICb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <requestURICb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <requestURICb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    strncat(sMsg->request_uri, p, pLen);

    return 0;
}

int queryStringCb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <queryStringCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <queryStringCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    strncat(sMsg->query_string, p, pLen);

    return 0;
}

int urlStringCb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <urlStringCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <urlStringCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    strncat(sMsg->url, p, pLen);

    return 0;
}

int fragmentCb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <fragmentCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <fragmentCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    strncat(sMsg->fragment, p, pLen);

    return 0;
}

int headerFieldCb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <headerFieldCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <headerFieldCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    httpMessage_t *m = sMsg;

    if (m->last_header_element != FIELD)
        m->num_headers++;

    strncat(m->headers[m->num_headers-1][0], p, pLen);

    m->last_header_element = FIELD;

    return 0;
}

int headerValueCb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <headerValueCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <headerValueCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    httpMessage_t *m = sMsg;

    strncat(m->headers[m->num_headers - 1U][1U], p, pLen);

    m->last_header_element = VALUE;

    return 0;
}

int bodyCb(http_parser *pParser, const char *p, size_t pLen) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <bodyCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <bodyCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);
    printf("        *p = %s", p);

    strncat(sMsg->body, p, pLen);

    // printf("body_cb: '%s'\n", requests[num_messages].body);

    return 0;
}

int messageCompleteCb(http_parser *pParser) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <messageCompleteCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <messageCompleteCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);

    sMsg->method = pParser->method;
    sMsg->status_code = pParser->status_code;

    sMsg->message_complete_cb_called = 1;

    return 0;
}

int messageBeginCb(http_parser *pParser) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <messageBeginCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <messageBeginCb> HTTP message static var is NULL\n");
        return 1;
    }

    sMsg->message_begin_cb_called = 1;

    return 0;
}

int headersCompleteCb(http_parser *pParser) {
    /* Check if the parser is NULL */
    if(NULL == pParser) {
        fprintf(stderr, "[ERROR] <headersCompleteCb> HTTP Parser arg is NULL\n");
        return 1;
    }

    /* Check if the message ptr is NULL */
    if(NULL == sMsg) {
        fprintf(stderr, "[ERROR] <headersCompleteCb> HTTP message static var is NULL\n");
        return 1;
    }

    printf("[DEBUG] Called %s\n", __func__);

    sMsg->headers_complete_cb_called = 1;

    return 0;
}
