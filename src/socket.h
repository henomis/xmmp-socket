#ifndef SOCKET_H
#define SOCKET_H

#ifdef __cplusplus
extern "C" {
#endif
#include <libsocket/libinetsocket.h>
#ifdef __cplusplus
}
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int tcp_client(char *host, char *port);
int tcp_server(char *port);

#endif // SOCKET_H
