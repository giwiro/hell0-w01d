CC = gcc
DEPS = logger.h common.h

SRV_OBJ = server.o logger.o
CLI_OBJ = client.o logger.o

all: server client

server: $(SRV_OBJ)
	$(CC) $^ -o $@

client: $(CLI_OBJ)
	$(CC) $^ -o $@

%.o: %.c $(DEPS)
	$(CC) $< -c -o $@

.PHONY: clean

clean:
	rm -f $(SRV_OBJ) $(CLI_OBJ) server client

