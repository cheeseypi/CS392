CC = gcc
CFLAGS = -Wall -Werror --pedantic

server_c = socket_server.c
client_c = socket_client.c
out_name_server = server
out_name_client = client

all: server client

server: $(server_c)
	$(CC) $(CFLAGS) -o $(out_name_server) $(server_c)

client: $(client_c)
	$(CC) $(CFLAGS) -o $(out_name_client) $(client_c)

clean-serv:
	-rm ./$(out_name_server)

clean-cli:
	-rm ./$(out_name_client)

clean: clean-serv clean-cli

fclean: clean

re: fclean all

test: all
	-./server 3000 & ./client localhost 3000
	make fclean

test-serv: server
	-./server 3000
	-make clean-serv

test-cli: client
	-./client localhost 3000
	-make clean-cli

.SILENT:
