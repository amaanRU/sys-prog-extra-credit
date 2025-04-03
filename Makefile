CC = gcc
CFLAGS = -O3 -Wall -Werror -fPIC 
LDFLAGS = -shared -lm 

all: libkernel.so 

libkernel.so: kernel.c 
	$(CC) $(CFLAGS) $(LDFLAGS) -o libkernel.so kernel.c

clean:
	rm -f libkernel.so