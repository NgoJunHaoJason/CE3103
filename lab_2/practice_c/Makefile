bin-folder = bin
executable = $(bin-folder)/mutex
source = src/mutex.c

CC = gcc
LDFLAGS = -lpthread

all: $(executable)

$(executable): $(source)
	$(CC) -o $(executable) $(source) $(LDFLAGS)

clean:
	rm -f $(bin-folder)/*