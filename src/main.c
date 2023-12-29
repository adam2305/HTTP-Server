//
//
//

/*
    
*/

#include "server.h"
#include <stdio.h>
#include <stdio.h>
#include <signal.h>

#define DOMAIN AF_INET
#define SERVICE SOCK_STREAM
#define PROTOCOL 0
#define INTERFACE INADDR_ANY
#define PORT 8080
#define BACKLOG 10


int main()
{   
    struct Server server = server_init(DOMAIN,SOCK_STREAM,0,INADDR_ANY,8080,10);
    accept_new_client(&server);
    close(server.socket);
    return 0;
}
