// This file includes all headers used by all the .c files
/* Essential Headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

/* Check man pages for inet and close */
#include <unistd.h>    // Added for close() "implicit declaration"
#include <arpa/inet.h> // Added for inet_addr "implicit declaration"

/* For macro ... va_list ..etc*/
#include <stdarg.h>

/* Local header files */
#include "colors.h"
#include "defs.h"
#include "server.h"
#include "client.h"


