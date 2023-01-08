all: hello2

hello2: hello2.o
	gcc -o hello2 hello2.o

hello2.o: hello2.c
	gcc -c hello2.c

clean:
	rm hello2.o hello2
