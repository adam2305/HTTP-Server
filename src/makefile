    CPPFLAGS:=-std=c11 -W -Wall -pedantic -Werror
    CFLAGS:=-O2 -save-temps
     
    puts.o: CPPFLAGS+=-Wno-unused-parameter
     
    .PHONY: all
    all: puts
     
    .PHONY: clean
    clean:
    	$(RM) *.[adios] puts

main.o: main.c server.h
	gcc -c main.c -o ../program/main.o

server.o : server.c server.h utils.h http_handler.h
	gcc -c server.c

utils.o : utils.c utils.h
	gcc -c utils.c

http_handler.o: http_handler.c http_handler.h utils.h
	gcc -c http_handler.c

main: main.o server.o utils.o http_handler.o
	gcc main.o server.o utils.o http_handler.o -o ../program/http_server -w
