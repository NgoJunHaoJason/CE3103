#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

volatile sig_atomic_t g_stop; // global

void error(char* error_message)
{
    perror(error_message);
}

void handle_signal(int signal_number)
{
    g_stop = 1;
}

void listen_socket(int socket_file_descriptor, int new_socket_file_descriptor, int queue_length, struct sockaddr_in client_address)
{
    int client_length, read_write_status;

    char incoming_buffer[256];
    char outgoing_buffer[256];
    int number;

    listen(socket_file_descriptor, queue_length);

    client_length = sizeof(client_address);

    new_socket_file_descriptor = accept(
        socket_file_descriptor,
        (struct sockaddr*) &client_address,
        &client_length
    );
    if(new_socket_file_descriptor < 0)
        error("ERROR on accept");
    
    printf("accepted connection from socket %d\n", new_socket_file_descriptor);
    fflush(stdout);
    
    read_write_status = read(new_socket_file_descriptor, incoming_buffer, 255);
    if(read_write_status < 0)
        error("ERROR reading from socket");
    
    // printf("Message received: %s\n", incoming_buffer);
    number = atoi(incoming_buffer);
    printf("Number received: %d\n", number);
    fflush(stdout);

    number *= 5;
    sprintf(outgoing_buffer, "%d", number);

    read_write_status = write(new_socket_file_descriptor, outgoing_buffer, 21);
    if(read_write_status < 0)
        error("ERROR writing back to socket");
    
    printf("Wrote back to socket: %d\n", number);
    fflush(stdout);
}

int main(int argc, char* argv[])
{
    int socket_file_descriptor, new_socket_file_descriptor, port, client_length, bind_status, read_write_status;
    int socket_option = 1;

    int queue_length = 2;

    char incoming_buffer[256];
    char outgoing_buffer[256];
    int number;

    struct sockaddr_in server_address, client_address;

    if(argc < 2)
        error("ERROR: no port provided\n");

    port = atoi(argv[1]);

    printf("using port %d\n", port);
    fflush(stdout);

    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor < 0)
        error("ERROR opening socket");
    
    printf("opened socket %d\n", socket_file_descriptor);
    fflush(stdout);

    memset((char*) &server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(port);

    bind_status = bind(
        socket_file_descriptor,
        (const struct sockaddr*) &server_address,
        sizeof(server_address)
    );
    if(bind_status < 0)
        error("ERROR binding to socket");
    
    printf("bound to socket\n");
    fflush(stdout);

    signal(SIGINT, handle_signal);
    
    while(!g_stop)
    {
        listen(socket_file_descriptor, queue_length);

        client_length = sizeof(client_address);

        new_socket_file_descriptor = accept(
            socket_file_descriptor,
            (struct sockaddr*) &client_address,
            &client_length
        );
        if(new_socket_file_descriptor < 0)
            error("ERROR on accept");
        
        printf("accepted connection from socket %d\n", new_socket_file_descriptor);
        fflush(stdout);
        
        read_write_status = read(new_socket_file_descriptor, incoming_buffer, 255);
        if(read_write_status < 0)
            error("ERROR reading from socket");
        
        // printf("Message received: %s\n", incoming_buffer);
        number = atoi(incoming_buffer);
        printf("Number received: %d\n", number);
        fflush(stdout);

        number *= 5;
        sprintf(outgoing_buffer, "%d", number);

        read_write_status = write(new_socket_file_descriptor, outgoing_buffer, 21);
        if(read_write_status < 0)
            error("ERROR writing back to socket");
        
        printf("Wrote back to socket: %d\n", number);
        fflush(stdout);
    }

    setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &socket_option, sizeof(socket_option));
    close(socket_file_descriptor);

    setsockopt(new_socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &socket_option, sizeof(socket_option));
    close(new_socket_file_descriptor);
    
    return 0;
}
