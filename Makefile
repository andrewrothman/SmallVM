CC = gcc
CFLAGS = -pedantic -Wall -ansi

all:
	mkdir -p programs/bin
	$(CC) $(CFLAGS) src/vm.c programs/helloworld.c -o programs/bin/helloworld
	$(CC) $(CFLAGS) src/vm.c programs/math.c -o programs/bin/math
	$(CC) $(CFLAGS) src/vm.c programs/loop.c -o programs/bin/loop

run:
	./programs/bin/helloworld
	./programs/bin/math
	./programs/bin/loop

clean:
	rm -rf programs/bin/