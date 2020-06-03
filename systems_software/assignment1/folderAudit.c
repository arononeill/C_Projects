#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#include "date.h"
#include "backup.h"
#include "folderAudit.h"
#include "client.h"

void folderAudit()
{
	char * dateBuffer[80];
    char * date = getDate(dateBuffer);
    char * file = ".txt";

    char * path = "ausearch -f /var/www/html/ > /var/www/html/accesslog/accesslog.txt";

    if(system (path) < 0)
    {
        messageQueue("Could not audit");
    	openlog("Assignment1", LOG_PID | LOG_CONS, LOG_USER);
    	syslog(LOG_INFO, "Could not audit: %s", strerror(errno));
    	closelog();
    }

}
