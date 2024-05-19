all: common.c client.c server.c
	gcc -o client.out client.c
	gcc -o server.out server.c