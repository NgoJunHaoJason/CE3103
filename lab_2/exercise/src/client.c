#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void error(char* error_message)
{
    perror(error_message);
    exit(0);
}

int main(int argc, char* argv[])
{
    int socket_file_descriptor, port, connect_status, read_write_status;
    int socket_option = 1;

    struct sockaddr_in server_address;
    struct hostent* server;

    char buffer[256];

    if (argc < 3)
        error("usage client [hostname] [port]\n");
    
    port = atoi(argv[2]);

    socket_file_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socket_file_descriptor < 0)
        error("ERROR opening socket");
    
    server = gethostbyname(argv[1]);
    if(server == NULL)
        error("ERROR: no such host");

    // start with clean address structure
    memset((char*) &server_address, 0, sizeof(server_address));

    server_address.sin_family = AF_INET; // internet socket
    bcopy(
        (char*) server->h_addr,
        (char*) &server_address.sin_addr.s_addr,
        server->h_length
    );

    server_address.sin_port = htons(port);

    connect_status = connect(
        socket_file_descriptor,
        (const struct sockaddr*) &server_address,
        sizeof(server_address)
    );

    if(connect_status < 0)
        error("ERROR connecting");
    
    printf("Please enter a number: ");
    fgets(buffer, 255, stdin);

    read_write_status = write(socket_file_descriptor, buffer, strlen(buffer));
    if(read_write_status < 0)
        error("ERROR writing to socket");

    read_write_status = read(socket_file_descriptor, buffer, 255);
    if(read_write_status < 0)
        error("ERROR reading from socket");

    printf("%s\n", buffer);

    setsockopt(socket_file_descriptor, SOL_SOCKET, SO_REUSEADDR, &socket_option, sizeof(socket_option));
    close(socket_file_descriptor);

    return 0;
}
