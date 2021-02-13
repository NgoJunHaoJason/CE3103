bin-folder = bin
executable = $(bin-folder)/pthread2
source = src/pthread2.c

CC = gcc
LDFLAGS = -lpthread

all: $(executable)

$(executable): $(source)
	$(CC) -o $(executable) $(source) $(LDFLAGS)

clean:
	rm -f $(bin-folder)/*