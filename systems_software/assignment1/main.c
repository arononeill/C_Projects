#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <syslog.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <mqueue.h>
#include <errno.h>
#include <string.h>

#include "transfer.h"
#include "backup.h"
#include "date.h"
#include "folderLocking.h"
#include "folderAudit.h"

#include "client.h"
// #include "singleton.h"

#define MAX_BUF 1024
 
int main()
{
    time_t now;
    struct tm newyear;
    double seconds;
    time(&now);  
    // gets current time
    newyear = *localtime(&now);
    // Setting these varaibles to 0, will set the copy the intranet site to the live site.
    newyear.tm_hour = 0; 
    newyear.tm_min = 0; 
    newyear.tm_sec = 0;

    
    // Puts an audit watch on the server
    char * watchFile = "auditctl -w /var/www/html -p rwxa";
    
    if(system(watchFile) < 0)
    {
      messageQueue("Could not start auditing");
      openlog("Assignment1", LOG_PID | LOG_CONS, LOG_USER);
      syslog(LOG_INFO, "Could not start auditing: %s", strerror(errno));
      closelog();
    }
    else
    {
        messageQueue("Started auditing");
    }
    

    // Implementation for Singleton Pattern if desired (Only one instance running)

    // Create a child process      
    int pid = fork();
 
    if (pid > 0) {
        // if PID > 0 :: this is the parent
        // this process performs printf and finishes

        sleep(10);  // uncomment to wait 10 seconds before process ends
        exit(EXIT_SUCCESS);
    } else if (pid == 0) {
       // Step 1: Create the orphan process
       printf("\nProcess running ...\n");
       
       // Step 2: Elevate the orphan process to session leader, to loose controlling TTY
       // This command runs the process in a new session
       if (setsid() < 0) { exit(EXIT_FAILURE); }

       // We could fork here again , just to guarantee that the process is not a session leader
       int pid = fork();
       if (pid > 0) {
          exit(EXIT_SUCCESS);
       } else {
       
          // Step 3: call umask() to set the file mode creation mask to 0
          // This will allow the daemon to read and write files 
          // with the permissions/access required 
          umask(0);

          // Step 4: Change the current working dir to root.
          // This will eliminate any issues of running on a mounted drive, 
          // that potentially could be removed etc..
          if (chdir("/") < 0 ) { exit(EXIT_FAILURE); }

          // Step 5: Close all open file descriptors
          /* Close all open file descriptors */
          int x;
          for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--)
          {
             close (x);
          } 

          // singleton();
         
          while(1) 
          {
                sleep(1);
                
                int fd;
                char * fifoFile = "/tmp/fifoFile";
                char buf[MAX_BUF] = "";
                fd = open (fifoFile, O_RDONLY);

                read (fd, buf, MAX_BUF);

                // If buffer contains '1' call backup()
                if(strcmp(buf, "1") == 0)
                {
                    lockFolder("1111");
                    backup();
                    lockFolder("0777"); 
                }

                close(fd);

                fd = open (fifoFile, O_RDONLY);

                // If buffer contains '2' call updateLiveWebsite() 
                if(strcmp(buf, "2") == 0)
                {
                    lockFolder("1111");
                    updateLiveWebsite();
                    lockFolder("0777");
                }
                close(fd);
                

                time(&now);
                seconds = difftime(now,mktime(&newyear));

                // If current time is the pre-defined 12pm call backup() first, then updateLiveWebsite()
                if (seconds == 0) 
                {
                    lockFolder("1111");
                    backup();
                    updateLiveWebsite();
                    lockFolder("0777");
                }

                folderAudit();
                
          }
       }
    }
 
    return 0;
}
