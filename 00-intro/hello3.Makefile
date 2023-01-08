all: hello3

hello2: hello3.o
	gcc -o $@ $<

hello2.o: hello3.c
	gcc -c $<

clean:
	rm hello3.o hello3
