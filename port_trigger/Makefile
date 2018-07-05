#Make file for port trigger test tools.

OBJS = client server
all: $(OBJS)
 
client: client.c utils.o
	gcc -o client.o -c client.c
	gcc -o client client.o utils.o


server:	server.o utils.o
	gcc -o server.o -c server.c
	gcc -o server server.o utils.o
	echo "done"

utils.o: utils.h utils.c
	gcc -o utils.o -c utils.c

clean:
	rm *.o -f
	rm $(OBJS) -f
