server: server.o ../utils/utils.o
	gcc -o server server.o ../utils/utils.o

server.o: server.c ../utils/utils.h
	gcc -c server.c

utils.o: ../utils/utils.h ../utils/utils.c
	gcc -c utils.c