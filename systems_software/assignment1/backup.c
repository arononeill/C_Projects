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
#include <setjmp.h>


#include "date.h"
#include "backup.h"
#include "client.h"


void backup()
{

	char * dateBuffer[80];
    char * date = getDate(dateBuffer);



    char * path = "cp -R /var/www/html/intranet /var/www/html/Backup/";


    int bufferSize = strlen(path) + strlen(date) + 1;
    char * buffer = (char *) malloc (bufferSize);

    strcpy(buffer, path);
    strcat(buffer, date);

    if (system(buffer) < 0)
    {
    	messageQueue("Unable to backup");
    	openlog("Assignment1", LOG_PID|LOG_CONS, LOG_USER);
        syslog(LOG_INFO, "Unable to Backup");
        closelog();
  	}

    else
    {
        openlog("Assignment1", LOG_PID|LOG_CONS, LOG_USER);
        syslog(LOG_INFO, "Backed up");
        closelog();
        messageQueue("Backup Complete");
    }

	free(buffer);


}
