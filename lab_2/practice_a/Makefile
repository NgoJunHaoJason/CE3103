executable = bin/pthread1
source = src/pthread1.c
CC = gcc
LDFLAGS = -lpthread

all: $(executable)

$(executable): $(source)
	$(CC) -o $(executable) $(source) $(LDFLAGS)

clean:
	rm -f $(executable)
