#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>


#include "transfer.h"
#include "client.h"


 
void updateLiveWebsite()
{

	char * path = "rsync -r /var/www/html/intranet/ /var/www/html/live";



	if (system(path) < 0)
	{
		openlog("Assignment1", LOG_PID|LOG_CONS, LOG_USER);
		syslog(LOG_INFO, "Could not transfer");
		closelog();
	}

	else
	{
		openlog("Assignment1", LOG_PID|LOG_CONS, LOG_USER);
		syslog(LOG_INFO, "Transfered");
		closelog();
		messageQueue("Transfer Completed");
	}


}
