//
//
//

/*
    
*/

#include "http_handler.h"
#include "utils.h"
#include <regex.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

char *decode_url(const char* url)
{
    int taille = strlen(url);
    char *decode = (char *)malloc((taille + 1) * sizeof(char));
    int j = 0;

    for (int i = 0; i < taille; i++) 
    {
        if (url[i] == '%')
        {
            if (isxdigit(url[i + 1]) && isxdigit(url[i + 2]))
            {
                char hex[3];
                hex[0] = url[i + 1];
                hex[1] = url[i + 2];
                hex[2] = '\0';
                int num = (int)strtol(hex, NULL, 16);
                decode[j++] = (char)num;
                i += 2;
            } 
            else 
                decode[j++] = url[i];
        } 
        else if (url[i] == '+') 
            decode[j++] = ' ';
        else 
            decode[j++] = url[i];
    }

    decode[j] = '\0';
    return decode;
}

void create_http_response(const char* file,const char* file_extension, char* response ,size_t *response_lenght)
{
    const char *mime = mime_type(file_extension);
    char *http_header = (char *)malloc(BUFFER_SIZE * sizeof(char));
    snprintf(http_header, BUFFER_SIZE,
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: %s\r\n"
             "\r\n",
             mime);
    
    time_t curtime;
    char formattedTime[50];
    curtime = time (NULL);
    strftime(formattedTime, sizeof(formattedTime), "%Y-%m-%d %H:%M:%S", localtime(&curtime));
    char chemin[] = TEMPLATE_PATH;
    strcat(chemin,file);
    int fd = open(chemin, O_RDONLY);

    if (fd == -1) {
        snprintf(response, BUFFER_SIZE,
                 "HTTP/1.1 404 Not Found\r\n"
                 "Content-Type: text/plain\r\n"
                 "\r\n"
                 "404 Not Found");
        *response_lenght = strlen(response);
        purple_output();
        printf("%s : response -> ",formattedTime);
        red_output();
        printf(ERROR_404);
        return;
    }

    struct stat file_stat;
    fstat(fd, &file_stat);
    off_t file_size = file_stat.st_size;

    *response_lenght = 0;
    memcpy(response, http_header, strlen(http_header));
    *response_lenght += strlen(http_header);

    ssize_t bytes;
    while ((bytes = read(fd, response + *response_lenght, BUFFER_SIZE - *response_lenght)) > 0) 
    {
        *response_lenght += bytes;
    }
    free(http_header);
    close(fd);
}

