//
//
//

/*
    
*/

#ifndef utils_h
#define utils_h

#include <stdio.h>

void green_output();
void red_output();
void blue_output();
void purple_output();
void white_output();
char * file_extension(const char* file);
const char *mime_type(const char* file_extension);

#endif