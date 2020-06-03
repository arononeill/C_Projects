#include <stdio.h>
#include <time.h>
#include "date.h"

// Function to retrieve the date to be logged
char* getDate(char * buffer)
{
	time_t rawtime;
	struct tm *timeinfo;

	time (&rawtime);

	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d-%m-%Y---%I:%M:%S%p", timeinfo);

	return buffer;
}