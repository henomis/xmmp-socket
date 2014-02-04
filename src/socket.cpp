#include "socket.h"

#if 0
void tcp_client(char *host, int port) 
{
    try
    {
        //Create a client and connect it to localhost, port 1337
      TCPClient client(SocketAddress(port, host));

        //Create a packet
        Packet packet;
        //Put a random string
        packet << "Hello world";
        //Put a random number
        packet << 42;

        //Create an event and send it to the server
        client.send(Event("hello_msg", packet));

        //Create an event listener
        EventListener listener(client);

        //Create an event consumer
        EventConsumer consumer(listener);
        consumer.on_event().set_function(on_event);

        //Launch the two threads
        listener.run();
        consumer.run();

        //Wait 1000ms
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        //Join the listener and consumer threads
        listener.join();
        consumer.join();

        //Close connection (it's facultative, since the destructor of
        //client call disconnect).
        client.disconnect();
    }
    catch (Exception& e)
    {
        std::cout << "An exception occured: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
}

#endif
