//
//
//

/*
    
*/

#include "utils.h"
#include <string.h>

void green_output()
{
    printf("\033[0;32m");
}

void red_output()
{
    printf("\033[0;31m");
}

void blue_output()
{
    printf("\033[0;34m");
}

void purple_output()
{
    printf("\033[0;35m");
}

void white_output()
{
    printf("\033[0;37m");
}

char * file_extension(const char* file)
{
    char* extension = strrchr(file, '.');
    if (extension != NULL) 
    {
        return extension + 1;
    }
    return "";
}

const char *mime_type(const char* file_extension)
{
    if (strcasecmp(file_extension, "html") == 0 || strcasecmp(file_extension, "htm") == 0) 
    {
        return "text/html";
    } 
    else if (strcasecmp(file_extension, "txt") == 0) 
    {
        return "text/plain";
    } 
    else if (strcasecmp(file_extension, "jpg") == 0 || strcasecmp(file_extension, "jpeg") == 0) 
    {
        return "image/jpeg";
    } 
    else if (strcasecmp(file_extension, "png") == 0) 
    {
        return "image/png";
    } 
    return "application/octet-stream";
}