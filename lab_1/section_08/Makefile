objects = hello-main.o hello-funct1.o
CC = gcc

# -c: compile but not link, -g: debug, -Wall: all warnings
CFLAGS = -c -g -Wall

all: helloworld

helloworld: $(objects)
	$(CC) -o helloworld $(objects)

hello-main.o: hello-main.c
	$(CC) $(CFLAGS) hello-main.c

hello-funct1.o: hello-funct1.c
	$(CC) $(CFLAGS) hello-funct1.c

clean:
	rm -f $(objects) helloworld
