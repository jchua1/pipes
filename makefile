compile: client.c server.c pipe_networking.c
	gcc -o client client.c
	gcc -o server server.c
	gcc -o pipe_networking pipe_networking.c



