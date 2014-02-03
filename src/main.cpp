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

	/*  The Big Loop */
	while (1) {
		/*  Do some task here ... */

		sleep(30);	/*  wait 30 seconds */
	}

	return (EXIT_SUCCESS);
}
