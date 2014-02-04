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


#include "utils.h"
#include "xmpp.h"
#include "socket.h"

#include <signal.h>

static int xmpp_pid = -1, net_pid = -1;

void kill_children(int sig)
{
    if(xmpp_pid != -1)
        kill(xmpp_pid, SIGKILL);
    if(net_pid != -1)
        kill(net_pid, SIGKILL);
}

int main(int argc, char **argv)
{

    if(Daemonize() != EXIT_SUCCESS)
        exit(EXIT_FAILURE);

    char *jid, *pass;


    signal(SIGTERM,kill_children);


    std::map<std::string, std::string> options;

    std::ifstream ifs ("/etc/xmpp-socket.conf", std::ifstream::in);
    parse(ifs,options);

	/*  Daemon-specific initialization goes here */    


    std::map<std::string, std::string>::const_iterator it = options.find("xmpp-user");
    if(it!=options.end())
        jid = strdup(options["xmpp-user"].c_str());
    else
        exit(EXIT_FAILURE);
    it = options.find("xmpp-pass");
    if(it!=options.end())
        pass = strdup(options["xmpp-pass"].c_str());
    else
        exit(EXIT_FAILURE);


    /* xmpp child */
    if((xmpp_pid = fork()) == 0){
        do_xmpp(jid,pass);
        exit(0);
    } else {
        // parent code here
    }


    /* net child */
    if((net_pid = fork()) == 0){
        /* if client */
        //tcp_client();
        /*else
         *tcp_server();
         */
        while(1) {
            sleep(1);
        }
        exit(0);
    } else {
        // parent code here
    }


    while(1) {
        sleep(60);
    }

    free(jid);
    free(pass);

	return (EXIT_SUCCESS);
}
