#include <stdio.h>
#include <time.h>
#include <string.h>
#include <mqueue.h>
#include <stdlib.h>

#include "client.h"

void messageQueue(char  message[])
{
	mqd_t mq;

	mq = mq_open("/MyQueue", O_WRONLY);

	mq_send(mq, message, 1024, 0);

	mq_close(mq);
}
