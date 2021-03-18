bin-folder = bin
src-folder = src

executable = $(bin-folder)/gpio
source = $(src-folder)/gpio.c

CC = gcc
LDFLAGS = -lpthread

all: $(executable)

$(executable): $(source)
	$(CC) -o $(executable) $(source) $(LDFLAGS)

clean:
	rm -f $(bin-folder)/*