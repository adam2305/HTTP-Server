//
//
//

/*
    
*/

#ifndef http_handler_h
#define http_handler_h

#include <stddef.h>

#define BUFFER_SIZE 100000000

#define ERROR_404 "ERROR : 404 not found\n"

#define TEMPLATE_PATH "../templates/"

char *decode_url(const char* url);
void create_http_response(const char* file,const char* file_extension, char* response ,size_t *response_lenght);

#endif
