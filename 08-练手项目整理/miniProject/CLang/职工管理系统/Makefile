app: infoio.o worker.o main.o
	gcc infoio.o worker.o main.o -o app

infoio.o: infoio.c
	gcc -c infoio.c

worker.o: worker.c
	gcc -c worker.c

main.o: main.c
	gcc -c main.c

clean:
	rm infoio.o worker.o main.o -rf

