#include "socket.h"


int lion_userinput( lion_t *handle,
                    void *user_data, int status, int size, char *line)
{
    lion_t *new_handle = NULL;

    //      printf("userinput %p %d\n", handle, status);

    switch( status ) {

    case LION_CONNECTION_LOST:
        printf("Connection '%p' was lost.\n", handle);

        break;


    case LION_CONNECTION_CLOSED:
        printf("Connection '%p' was gracefully closed.\n", handle);


        break;

    case LION_CONNECTION_NEW:
        printf("Connection '%p' has a new connection...\n", handle);

        // Accept the port
        new_handle = lion_accept(handle, 0, 0, NULL, NULL, NULL);

        break;

    case LION_CONNECTION_CONNECTED:
        printf("Connection '%p' is connected. \n", handle);

        break;


    case LION_BUFFER_USED:
        // If user_data is set (ie, file->socket) we pause the file.
        //              if (user_data)
        //              lion_disable_read( user_data );
        break;

    case LION_BUFFER_EMPTY:
        // If user_data is set (ie, file->socket) we resume the file.
        if (user_data)
            lion_enable_read( (connection_t*)user_data );
        break;

    case LION_INPUT:
                      printf("[input] on %p -> '%s'\n", handle, line);

#if 0
        if (!strncasecmp("ls ", line, 3)) {
            char *flags, *ar;

            ar = &line[3];
            // grab the flags wanted
            flags = misc_digtoken(&ar, " -\r\n");

            if (flags) {

                dirlist_list(handle,
                             // Pass it handle so THIS userinput is called
                             ar, NULL,
                             dirlist_a2f(flags)|DIRLIST_USE_CRNL,
                             handle);
#if 0
                dirlist_list(handle,
                             // Pass it handle so THIS userinput is called
                             ar,
                             DIRLIST_SHORT|DIRLIST_PIPE,
                             handle);
                dirlist_list(handle,
                             // Pass it handle so THIS userinput is called
                             ar,
                             DIRLIST_SHORT|DIRLIST_PIPE,
                             handle);
#endif
                break;
            }

            lion_printf(handle, "parse error: see HELP\r\n");

        }

        if (!strncasecmp("help", line, 4)) {
            lion_printf(handle, "LION contrib/libdirlist tester\r\n");
            lion_printf(handle, "usage: ls -flags /directory/path/\r\n");
            lion_printf(handle, "     flags are: \r\n"
                        "    *-l long format\r\n"
                        "     -1 short format\r\n"
                        "     -X XML format\r\n"
                        "     -T print to temporary file, return name\r\n"
                        "    *-P print to pipe\r\n"
                        "     -N sort by name\r\n"
                        "     -t sort by date\r\n"
                        "     -s sort by size\r\n"
                        "     -C sort with case insensitive\r\n"
                        "     -r sort in reverse\r\n"
                        "     -R sort recursively\r\n"
                        "     -D sort directories before files\r\n"
                        "     -a display dot-entries\r\n\r\n");
        }

        if (!strncasecmp("quit", line, 4)) {

            lion_close(handle);
            break;

        }



        if (handle && user_data) { // reply from LS

            lion_printf(handle, "%s\n", line);

        }
#endif

        break;

    case LION_BINARY:
        break;
    }



    return 0;

}


int tcp_client(char *host, char *port)
{



}

int tcp_server(char *port)
{
    void *listen = NULL;


    static int master_switch = 0;
    static int server_port   = 57777;  // Set to 0 for any port.

    lion_init();
    lion_compress_level( 0 );

    listen = lion_listen(&server_port, 0, 0, NULL);

    if (!listen) {

        printf("Socket Failed...\n");
        master_switch = 1;

    }


    printf("Listening on port %d...\n", server_port);






    while( !master_switch ) {

        // If you are using rate calls, you should sleep for 1s or less.
        lion_poll(0, 1);     // This blocks. (by choice, FYI).
        //printf("main\n");
    }
    printf("\n");



    printf("Releasing Socket...\n");
    if (listen) {
        lion_disconnect((connection_t*)listen);
        listen = NULL;
    }
    printf("Socket Released.\n");


    lion_free();

    return 0;
}
