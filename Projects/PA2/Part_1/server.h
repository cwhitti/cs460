#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

// added libraries //
#include <netdb.h>
#include <time.h>

/* Function prototypes */
void* handle_client(void* arg);
char* get_ip_address(const char *string);
void format_time(const char *string, char *outStr );
void copy_string( char *destStr, const char *srcStr );

/* Preprocessor directives */
#define SERVER_ADDR "time.nist.gov"

#define PORT 13              // port the server will listen on

#define FALSE 0
#define TRUE !FALSE

#define NUM_CONNECTIONS 5       // number of pending connections in the connection queue

#define ASTERISK '*'
#define NULL_CHAR '\0'
#define BUFFER_SIZE 1024
#define HUGE_STR_LEN 256
