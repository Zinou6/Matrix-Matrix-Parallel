all:	app-hw1

app-hw1:	main.o initMatrix.o displayMatrix.o ThreadCalcul.o calcul.o
	gcc main.o initMatrix.o displayMatrix.o ThreadCalcul.o calcul.o -o mmm -lm -lpthread

main.o:	main.c
	gcc -c main.c -o main.o 

initMatrix.o:	initMatrix.c
	gcc -c initMatrix.c -o initMatrix.o
	
displayMatrix.o:	displayMatrix.c
	gcc -c displayMatrix.c -o displayMatrix.o	

ThreadCalcul.o:	ThreadCalcul.c
	gcc -c ThreadCalcul.c -o ThreadCalcul.o
	
calcul.o: calcul.c
	gcc -c calcul.c -o calcul.o

clean:
	rm -fr app-hw1 *.o
