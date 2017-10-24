all: shell

CFLAGS = -g -O2

shell: shell.o myToc.o
	cc -o shell shell.o myToc.o
clean:
	rm -f  *.o 
demo: shell
	./shell
