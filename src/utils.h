/*
 * =====================================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:  utilities
 *
 *        Version:  1.0
 *        Created:  04/02/2014 09:54:21
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Simone Vellei (sve), henomis@gmail.com
 *
 * =====================================================================================
 */

#ifndef _UTILS_H_
#define _UTILS_H_


#include <string>
#include <iostream>
#include <stdexcept>
#include <map>
#include <sstream>
#include <fstream>
#include <limits>

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>




#define PID_FILE "/var/run/xmpp-socket.pid"

int Daemonize();
void parse(std::ifstream & cfgfile, std::map<std::string, std::string> &options);

#endif
