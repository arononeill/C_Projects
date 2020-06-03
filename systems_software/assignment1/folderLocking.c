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
#include "client.h"
#include "folderLocking.h"

void lockFolder(char type[])
{
	int counter;

	if(strcmp(type, "1111") == 0)
	{
		counter = 0;
	}

	else
	{
		counter = 1;
	}

	char path[100] = "/var/www/html";
	struct stat st;
	stat (path, &st);

	int i = strtol(type, 0, 8);

	if(chmod(path, i) < 0)
	{
		if(counter == 0)
		{
			messageQueue("Files not Locked");
		}

		else
		{
			messageQueue("Files not Unlocked!");
		}
		
		openlog("Audit log", LOG_PID | LOG_CONS, LOG_USER);
    	syslog(LOG_INFO, "Could not lock files");
    	closelog();
	}


	if(counter == 0)
	{
		messageQueue("Files Locked");
	}

	else
	{
		messageQueue("Files Unlocked!");
	}
}
