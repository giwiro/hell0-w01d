CC=gcc
DEPS=common.h

SRV_OBJ = server.o common.o
CLI_OBJ=client.o common.o

%.o: %.c $(DEPS)
	$(CC) $< -c -o $@

server: $(SRV_OBJ)
	$(CC) $^ -o $@

.PHONY: clean

clean:
	rm -f $(SRV_OBJ) server

