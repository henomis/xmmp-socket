/*
 * =====================================================================================
 *
 *       Filename:  xmpp.cpp
 *
 *    Description:  xmpp session manager
 *
 *        Version:  1.0
 *        Created:  04/02/2014 09:59:16
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Simone Vellei (sve), henomis@gmail.com
 *
 * =====================================================================================
 */

#include "xmpp.h"

int do_xmpp(char *jid, char *pass)
{

    xmpp_ctx_t *ctx;
    xmpp_conn_t *conn;
    xmpp_log_t *log;

    /* init library */
    xmpp_initialize();

    /* create a context */
    log = xmpp_get_default_logger(XMPP_LEVEL_DEBUG);	/* pass NULL instead to silence output */
    ctx = xmpp_ctx_new(NULL, log);

    /* create a connection */
    conn = xmpp_conn_new(ctx);

    /* setup authentication information */
    xmpp_conn_set_jid(conn, jid);
    xmpp_conn_set_pass(conn, pass);

    /* initiate connection */
    xmpp_connect_client(conn, NULL, 0, conn_handler, ctx);


    /* enter the event loop -
       our connect handler will trigger an exit */
    xmpp_run(ctx);

    /* release our connection and context */
    xmpp_conn_release(conn);
    xmpp_ctx_free(ctx);

    /* final shutdown of the library */
    xmpp_shutdown();	/*  The Big Loop */
    return 0;
}
