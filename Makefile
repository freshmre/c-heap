CC=gcc
CFLAGS=-m64 -std=c99 -pedantic -Wall -Wshadow -Wpointer-arith -Wcast-qual \
        -Wstrict-prototypes -Wmissing-prototypes -Wextra -g
PROG=main
OBJS=main.o \
     heap.o
HEADERS=heap.h

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $<

clean:
	find . -maxdepth 1 \
	-type f \
	-not -name '*.*' \
	-not -name 'Makefile' -exec rm -i "{}" \;
	rm -i *.o