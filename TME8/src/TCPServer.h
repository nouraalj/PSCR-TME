#ifndef SRC_TCPSERVER_H_
#define SRC_TCPSERVER_H_
#include <iostream>
#include <sys/socket.h>
#include <thread>
#include "ServerSocket.h"
#include "ConnectionHandler.h"
#define LIST 0;
#define UP 1;
#define DOWN 2;

namespace pr {

// un serveur TCP, la gestion des connections est déléguée
class TCPServer {
	ServerSocket * ss; // la socket d'attente si elle est instanciee
	ConnectionHandler * handler; // le gestionnaire de session passe a la constru
	// a completer
public :
	TCPServer(ConnectionHandler * handler): ss(nullptr),handler(handler) {
		
	}
	// Tente de creer une socket d'attente sur le port donné
	bool startServer (int port){
		char c;
		
		struct sockaddr_in s;
		s.sin_port = htons(port);
		s.sin_addr.s_addr = INADDR_ANY;
		s.sin_family = AF_INET;
		int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (bind(fd,(struct sockaddr *) &s, sizeof(s)) < 0){
			perror("bind");
			exit(1);
		}
		listen(fd, 3);
		while(1){
			int new_socket= accept(fd, (struct sockaddr*)&s, (socklen_t *)(sizeof(s)));
			ssize_t val = read(new_socket, &c,1);
			switch(val){
				case 0 : 
					std::cout << "LIST";
					
					break;
				case 1 :
					std::cout << "UP";
					break;
				case 2 :
					std::cout << "DOWN";
					break;
			}

			shutdown(new_socket, 2);
			shutdown(fd, 2);		
			
		}
	}

	// stoppe le serveur
	void stopServer (){
		
	}
};

} // ns pr

#endif /* SRC_TCPSERVER_H_ */
