CC = gcc
DEPS = logger.h common.h

SRV_OBJ = server.o logger.o
CLI_OBJ=client.o logger.o

%.o: %.c $(DEPS)
	$(CC) $< -c -o $@

server: $(SRV_OBJ)
	$(CC) $^ -o $@

.PHONY: clean

clean:
	rm -f $(SRV_OBJ) server

