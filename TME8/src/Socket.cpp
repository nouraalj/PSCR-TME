
#include "Socket.h"
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <ostream>
#include <iostream>
#include <iosfwd>
#include <arpa/inet.h>

using namespace pr;

void Socket::connect(const std::string &host, int port)
{
    struct addrinfo *adr;
    struct in_addr ipv4;

    if (getaddrinfo(host.c_str(), nullptr, nullptr, &adr))
    {
        perror("DNS");
    }
    for (struct addrinfo *rp = adr; rp != nullptr; rp = rp->ai_next)
    {
        if (rp->ai_family == AF_INET && rp->ai_socktype == SOCK_STREAM)
        {
            ipv4 = ((struct sockaddr_in *)(rp->ai_addr))->sin_addr;
            break;
        }
    }
    freeaddrinfo(adr);
    connect(ipv4, port);
}

void Socket::connect(in_addr ipv4, int port)
{
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        perror("socket");

    struct sockaddr_in s;
    s.sin_addr = ipv4;
    s.sin_family = AF_INET;
    s.sin_port = htons(port);
    if (::connect(fd, (struct sockaddr *)&s, sizeof(s)) < 0)
    {
        fd = -1;
        perror("connect");
        std::cerr << "Failed to connect to " << inet_ntoa(s.sin_addr) << " : " << ntohs(s.sin_port) << std::endl;
    }
}

void Socket::close()
{
    if (fd != -1)
    {
        ::shutdown(fd, 2);
        ::close(fd);
        fd = -1;
    }
}

std::ostream &operator<<(std::ostream &os, struct sockaddr_in *addr)
{
    char host[1024];
    if (getnameinfo((struct sockaddr *)addr, sizeof(struct sockaddr_in), host, 1024, nullptr, 0, 0))
    {
        os << "host" << host << std::endl;
    }
    os << inet_ntoa(addr->sin_addr) << " : " << ntohs(addr->sin_port);
    return os;
}
