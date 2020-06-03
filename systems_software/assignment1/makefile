CC = gcc
objects = main.o backup.o date.o transfer.o folderLocking.o folderAudit.o client.o
headers = backup.h date.h transfer.h folderLocking.h folderAudit.h client.h
files = main.c backup.c date.c transfer.c folderLocking.c folderAudit.c client.c
name = myprog

myprog : $(objects)
	$(CC) -o $(name) $(objects) -lm -lrt

main.o : main.c $(headers) -lrt
	$(CC) -c main.c

backup.o : backup.c
	$(CC) -c backup.c

date.o : date.c
	$(CC) -c date.c

transfer.o : transfer.c
	$(CC) -c transfer.c

folderLocking.o : folderLocking.c
	$(CC) -c folderLocking.c

folderAudit.o : folderAudit.c
	$(CC) -c folderAudit.c

client.o : client.c
	$(CC) -c client.c -lrt

clean:
	rm $(name) $(objects)
