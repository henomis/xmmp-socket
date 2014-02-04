#include "socket.h"

int tcp_client(char *host, char *port)
{

    int ret;
    int sfd;
    char* buf = "abcde";

    ret = sfd = create_inet_stream_socket(host,port,LIBSOCKET_IPv6,0);

    if ( ret < 0 )
    {
        perror(0);
        return(1);
    }

    ret = write(sfd,buf,5);

    if ( ret < 0 )
    {
        perror(0);
        return(1);
    }

    ret = destroy_inet_socket(sfd);

    if ( ret < 0 )
    {
        perror(0);
        return(1);
    }

    return 0;

}

int tcp_server(char *port)
{
    int cfd, sfd, ret;
    char* buf = (char*)calloc(16,1);

    ret = sfd = create_inet_server_socket("::",port,LIBSOCKET_TCP,LIBSOCKET_IPv6,0);

    if ( ret < 0 )
    {
        perror(0);
        return(1);
    }

    ret = cfd = accept_inet_stream_socket(sfd,0,0,0,0,0,0);

    if ( ret < 0 )
    {
        perror(0);
        return(1);
    }

    ret = read(cfd,buf,15);

    if ( ret < 0 )
    {
        perror(0);
        return(1);
    }

    printf("%s\n",buf);

    ret = destroy_inet_socket(sfd);

    if ( ret < 0 )
    {
        perror(0);
        return(1);
    }

}
