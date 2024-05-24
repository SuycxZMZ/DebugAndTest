CC=gcc
CFLAGS=-g -pthread -D_GNU_SOURCE
LIBS=/usr/lib/liburing.a

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
EXECS=$(SRCS:.c=)

all: $(EXECS)

%: %.c
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f $(OBJS) $(EXECS)