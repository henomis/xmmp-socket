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

    char *jid = NULL, *pass = NULL;
    bool is_server = false;
    char *socket_port = NULL;
    char *socket_host = NULL;


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

    it = options.find("socket-type");
    if(it!=options.end())
        is_server = (options["socket-type"].compare("server") == 0);
    else
        exit(EXIT_FAILURE);

    it = options.find("socket-port");
    if(it!=options.end())
        socket_port = strdup(options["socket-type"].c_str());
    else
        exit(EXIT_FAILURE);

    it = options.find("socket-host");
    if(it!=options.end())
        socket_host = strdup(options["socket-type"].c_str());



    /* xmpp child */
    if((xmpp_pid = fork()) == 0){
        do_xmpp(jid,pass);
        exit(0);
    } else {
        // parent code here
    }


    /* net child */
    if((net_pid = fork()) == 0){
        /* server */
        if(is_server)
            tcp_server(socket_port);
        else
            tcp_client(socket_host, socket_port);
        exit(0);
    } else {
        // parent code here
    }


    while(1) {
        sleep(60);
    }

    if(jid)
        free(jid);
    if(pass)
        free(pass);
    if(socket_host)
        free(socket_host);

	return (EXIT_SUCCESS);
}
