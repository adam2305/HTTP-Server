//
//
//

/*
    
*/

#ifndef server_h
#define server_h

#include <sys/socket.h>
#include <netinet/in.h>

#define ERROR_SOCKET "ERROR : échec de la connexion socket...\n"
#define ERROR_BIND "ERROR : échec de la liason socket...\n"
#define ERROR_LISTEN "ERROR : échec écoute serveur...\n"
#define ERROR_ACCEPT "ERROR : échec requête...\n"

struct Server
{
    int domain;
    int port;
    int protocol;
    int backlog;
    u_long interface;
    int service;
    int socket;

    struct sockaddr_in address;

};

struct Server server_init(int domain, int port, int protocol, u_long interface, int service, int backlog);
void accept_new_client(struct Server* server);
void *handle_client(void *socket);

#endif 