flags = -Wall -g
name = main
objects = tree.o matrix.o main.o

all: $(name)

$(name): $(objects)
	gcc -o $(name) $(objects) $(flags)

main.o: main.c
	gcc -c main.c $(flags)

matrix.o: matrix.c matrix.h
	gcc -c matrix.c matrix.h $(flags)

tree.o: tree.c tree.h
	gcc -c tree.c tree.h $(flags)

run:
	./main

clean:
	rm -f *~ *.o *gch

purge: clean
	rm -f $(name)