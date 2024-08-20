client: client.o ../utils/utils.o
	gcc -o client client.o ../utils/utils.o

client.o: client.c ../utils/utils.h
	gcc -c client.c

utils.o: ../utils/utils.h ../utils/utils.c
	gcc -c ../utils/utils.c