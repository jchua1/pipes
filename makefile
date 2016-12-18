compile: client.c server.c pipe_networking.c
	gcc -o client client.c pipe_networking.c
	gcc -o server server.c pipe_networking.c



