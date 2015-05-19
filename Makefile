make:
	gcc server.c -o server -ggdb -std=c11
	gcc client.c -o client
