#ifndef _HANDLERS_H_
#define _HANDLERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strophe.h>

int version_handler(xmpp_conn_t * const conn, xmpp_stanza_t * const stanza, void * const userdata);
int message_handler(xmpp_conn_t * const conn, xmpp_stanza_t * const stanza, void * const userdata);
void conn_handler(xmpp_conn_t * const conn, const xmpp_conn_event_t status, const int error, xmpp_stream_error_t * const stream_error, void * const userdata);
 



#endif
