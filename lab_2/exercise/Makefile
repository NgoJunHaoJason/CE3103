bin-folder = bin
src-folder = src

client-executable = $(bin-folder)/client
client-source = $(src-folder)/client.c

server-executable = $(bin-folder)/server
server-source = $(src-folder)/server.c

CC = gcc
LDFLAGS = -lpthread

all: $(client-executable) $(server-executable)

$(client-executable): $(client-source)
	$(CC) -o $(client-executable) $(client-source) $(LDFLAGS)

$(server-executable): $(server-source)
	$(CC) -o $(server-executable) $(server-source) $(LDFLAGS)

clean:
	rm -f $(bin-folder)/*