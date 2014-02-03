/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  xmpp-socket main
 *
 *        Version:  1.0
 *        Created:  03/02/2014 17:03:35
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Simone Vellei (sve), henomis@gmail.com
 *
 * =====================================================================================
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>

#include "handlers.h"


int main(int argc, char **argv)
{

	/*  Our process ID and Session ID */
	pid_t pid, sid;

	/*  Fork off the parent process */
	pid = fork();
	if (pid < 0) {
		exit(EXIT_FAILURE);
	}
	/*  If we got a good PID, then
	 *             we can exit the parent process. */
	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	/*  Change the file mode mask */
	umask(0);

	/*  Open any logs here */

	/*  Create a new SID for the child process */
	sid = setsid();
	if (sid < 0) {
		/*  Log the failure */
		exit(EXIT_FAILURE);
	}



	/*  Change the current working directory */
	if ((chdir("/")) < 0) {
		/*  Log the failure */
		exit(EXIT_FAILURE);
	}

	/*  Close out the standard file descriptors */
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	FILE *fp = fopen("/var/run/xmpp-socket.pid", "w+");
	if (fp != NULL) {
		fprintf(fp, "%d", getpid());
		fclose(fp);
	}

	/*  Daemon-specific initialization goes here */
	xmpp_ctx_t *ctx;
	xmpp_conn_t *conn;
	xmpp_log_t *log;
	char *jid, *pass;


	jid = conf_get_xmpp_user();
	pass = conf_get_xmpp_pass();

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


	/* start server or client */
		


	/* enter the event loop - 
	   our connect handler will trigger an exit */
	xmpp_run(ctx);

	/* release our connection and context */
	xmpp_conn_release(conn);
	xmpp_ctx_free(ctx);

	/* final shutdown of the library */
	xmpp_shutdown();	/*  The Big Loop */

	return (EXIT_SUCCESS);
}
