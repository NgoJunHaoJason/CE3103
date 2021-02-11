objects = hello-main.o hello-funct1.o hello-funct2.o
debug-objects = hello-main-d.o hello-funct1-d.o hello-funct2-d.o
CC = gcc

# -c: compile but not link, -g: debug, -Wall: all warnings
CFLAGS = -c -Wall
DEBUG = -g

all: helloworld

helloworld: $(objects)
	$(CC) -o helloworld $(objects)

hello-main.o: hello-main.c
	$(CC) $(CFLAGS) hello-main.c

hello-funct1.o: hello-funct1.c
	$(CC) $(CFLAGS) hello-funct1.c

hello-funct2.o: hello-funct2.c
	$(CC) $(CFLAGS) hello-funct2.c

debug: helloworld-d

helloworld-d: $(debug-objects)
	$(CC) -o helloworld-d $(debug-objects)

hello-main-d.o: hello-main.c
	$(CC) $(CFLAGS) $(DEBUG) -o hello-main-d.o hello-main.c

hello-funct1-d.o: hello-funct1.c
	$(CC) $(CFLAGS) $(DEBUG) -o hello-funct1-d.o hello-funct1.c

hello-funct2-d.o: hello-funct2.c
	$(CC) $(CFLAGS) $(DEBUG) -o hello-funct2-d.o hello-funct2.c
clean:
	rm -f $(objects) $(debug-objects) helloworld helloworld-d
