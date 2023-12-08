#include "ServerSocket.h"

#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <iosfwd>
#include <unistd.h>

using namespace pr;

ServerSocket::ServerSocket(int port)
{
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    int i;
    if (socketfd < 0)
        perror("socket");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(socketfd, (struct sockaddr *)&addr, sizeof addr) < 0)
    {
        perror("bind");
        std::cerr << "Failed to bind to address and port." << std::endl;
    }
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEPORT, &i, sizeof(i)) < 0)
    {
        perror("Set Socket Option");
    }

    if (listen(socketfd, 10) < 0)
    {
        perror("listen");
        std::cerr << "Failed to listen to address and port." << std::endl;
    }
}

Socket ServerSocket::accept()
{
    struct sockaddr_in exp;
    socklen_t sz = sizeof(exp);
    int sc = ::accept(socketfd, (struct sockaddr *)&exp, &sz);
    if (sc < 0)
    {
        perror("accept");
        std::cerr << "Failed to accept connection." << std::endl;
    }
    // std::cout<< "connection de " << &exp << std::endl;
    return Socket(sc);
}
