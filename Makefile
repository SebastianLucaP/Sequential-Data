FLAGS = -g -lm -Wall
build: tema1.c
	gcc -o tema1 tema1.c $(FLAGS)
clean:
	rm -rf tema1
	rm -f *.out
