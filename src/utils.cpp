/*
 * =====================================================================================
 *
 *       Filename:  utils.cpp
 *
 *    Description:  utilities
 *
 *        Version:  1.0
 *        Created:  04/02/2014 09:53:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Simone Vellei (sve), henomis@gmail.com
 *
 * =====================================================================================
 */


#include "utils.h"

int Daemonize()
{
    /*  Our process ID and Session ID */
    pid_t pid, sid;

    /*  Fork off the parent process */
    pid = fork();
    if (pid < 0) {
        return(EXIT_FAILURE);
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
        return(EXIT_FAILURE);
    }



    /*  Change the current working directory */
    if ((chdir("/")) < 0) {
        /*  Log the failure */
        return(EXIT_FAILURE);
    }

    /*  Close out the standard file descriptors */
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    FILE *fp = fopen(PID_FILE, "w+");
    if (fp != NULL) {
        fprintf(fp, "%d", getpid());
        fclose(fp);
    } else {
        return(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}



void parse(std::ifstream & cfgfile, std::map<std::string, std::string> &options)
{
    std::string id, eq, val;

    while(cfgfile >> id >> eq >> val)
    {
      if (id[0] == '#') continue;  // skip comments
      if (eq != "=") throw std::runtime_error("Parse error");

      options[id] = val;
    }
}
