#main: main.o

#	gcc main.o -o main

#main.o: main.c
#	gcc -c main.c

#clean:
#	rm -f*.o main



OBJS = main.o # number.o # List object files here
# DEPS = number.h
CFLAGS = -O2

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony: clean
clean:
	rm -f *.o

