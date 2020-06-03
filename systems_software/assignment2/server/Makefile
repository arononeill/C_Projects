CC = gcc
objects = Server.o date.o manager.o
headers = date.h manager.h
files = Server.c date.c manager.c
name = myprog
CFLAGS = -pthread

myprog : $(objects)
	$(CC) ${CFLAGS} -o $(name) $(objects) -lm -lrt

Server.o : Server.c $(headers)
	$(CC) -c Server.c -lrt

manager.o : manager.c
	$(CC) -c manager.c

date.o : date.c
	$(CC) -c date.c

Clean:
	rm $(name) $(objects)