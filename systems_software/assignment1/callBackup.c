#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "client.h"

int main(int argc, char *argv[]) 
{
	
	int fd;
	
	char * fifoFile = "/tmp/fifoFile";
	
	mkfifo(fifoFile, 0666);
	
	fd = open(fifoFile, O_WRONLY);
	write(fd, "1", sizeof("1"));
	close(fd);
	unlink(fifoFile);
	
	return 0;
}