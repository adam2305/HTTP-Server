//
//
//

/*
    
*/

#include "server.h"
#include "utils.h"
#include "http_handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <regex.h>
#include <string.h>
#include <time.h>

int ip1;
int ip2;
int ip3;
int ip4;

struct Server server_init(int domain, int service, int protocol, u_long interface, int port, int backlog)
{
    struct Server server;

    server.domain = domain;
    server.port = port;
    server.protocol = protocol;
    server.service = service;
    server.backlog = backlog;
    server.interface = interface;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    green_output();
    printf("OK : Démarrage serveur sur http://127.0.0.1:8080/...\n");

    server.socket = socket(domain, service, protocol);
    if(server.socket == 0)
    {
        red_output();
        perror(ERROR_SOCKET);
        exit(EXIT_FAILURE);
    }
    else
    {
        green_output();
        printf("OK : connexion socket...\n");
    }
        
    if((bind(server.socket,(struct sockaddr *)&server.address,sizeof(server.address)))< 0)
    {
        red_output();
        perror(ERROR_BIND);
        exit(EXIT_FAILURE);
    }
    else
    {
        green_output();
        printf("OK : liason socket...\n");
    }
       
    if((listen(server.socket,server.backlog)))
    {
        red_output();
        perror(ERROR_LISTEN);
        exit(EXIT_FAILURE);
    }
    else
    {
        green_output();
        printf("OK : serveur en écoute...\n");
    }    

    return server;
}

void *handle_client(void *socket) {
    int client_fd = *((int *)socket);
    char *buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

    ssize_t bytes = recv(client_fd, buffer, BUFFER_SIZE, 0);
    if (bytes > 0) 
    {
        regex_t regex;
        regcomp(&regex, "^GET /([^ ]*) HTTP/1", REG_EXTENDED);
        regmatch_t matches[2];

        if (regexec(&regex, buffer, 2, matches, 0) == 0) 
        {
            buffer[matches[1].rm_eo] = '\0';
            const char *url_fichier = buffer + matches[1].rm_so;
            char *file = decode_url(url_fichier);
            
            time_t curtime;
            char formattedTime[50];
            blue_output();
            curtime = time (NULL);
            strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localtime(&curtime));
            printf("%s : %d.%d.%d.%d -> GET /%s\n",formattedTime,ip1,ip2,ip3,ip4,file);

            char file_ext[32];
            strcpy(file_ext, file_extension(file));

            char *response = (char *)malloc(BUFFER_SIZE * 2 * sizeof(char));
            size_t response_len;
            create_http_response(file, file_ext, response, &response_len);

            send(client_fd, response, response_len, 0);

            free(response);
            free(file);
        }
        regfree(&regex);
    }
    close(client_fd);
    free(socket);
    free(buffer);
    return NULL;
}

void accept_new_client(struct Server* server)
{   
    white_output();
    printf("===== Écoute connexions entrantes =====\n");
    while(1)
    {
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int *client_socket = malloc(sizeof(int));

        if((*client_socket = accept(server->socket, (struct sockaddr *)&client_addr, &client_addr_len)) < 0) 
        {   
            red_output();
            perror(ERROR_ACCEPT);
            continue;
        }

        ip1 = (int)(client_addr.sin_addr.s_addr&0xFF);
        ip2 = (int)((client_addr.sin_addr.s_addr&0xFF00)>>8);
        ip3 = (int)((client_addr.sin_addr.s_addr&0xFF0000)>>16);
        ip4 = (int)((client_addr.sin_addr.s_addr&0xFF000000)>>24);

        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client, (void *)client_socket);
        pthread_detach(thread_id);
    }
}

