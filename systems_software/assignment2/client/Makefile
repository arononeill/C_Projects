CC = gcc
objects = Client.o 
headers =  
files = Client.c
name = ClientProg

ClientProg : $(objects)
	$(CC) -o $(name) $(objects) -lm -lrt

Client.o: Client.c $(headers)
	$(CC) -c Client.c -lrt

Clean:
	rm $(name) $(objects)