CC = gcc
CFLAGS = -g -std=c11 -pedantic -Wall -Wextra -lm -c -O2
LDFLAGS = -lm -Wall -Werror -pedantic

.PHONY: clean

all: primes primes-i steg-decode

run: primes primes-i
	ulimit -s 100000 && ./primes && ./primes-i

primes: primes.o eratosthenes.o error.o
	$(CC) $^ -o $@ $(LDFLAGS)

primes-i: primes-i.o eratosthenes-i.o error.o
	$(CC) $^ -o $@ $(LDFLAGS)

steg-decode: steg-decode.o ppm.o eratosthenes.o error.o
	$(CC) $^ -o $@ $(LDFLAGS)

primes.o: primes.c bitset.h
	$(CC) $(CFLAGS) primes.c

primes-i.o: primes.c bitset.h
	$(CC) $(CFLAGS) primes.c -o primes-i.o -DUSE_INLINE

eratosthenes.o: eratosthenes.c bitset.h
	$(CC) $(CFLAGS) eratosthenes.c

eratosthenes-i.o: eratosthenes.o bitset.h
	$(CC) $(CFLAGS) eratosthenes.c -o eratosthenes-i.o -DUSE_INLINE

error.o: error.c error.h
	$(CC) $(CFLAGS) error.c

ppm.o: ppm.h ppm.c
	$(CC) $(CFLAGS) ppm.c

steg-decode.o: steg-decode.c bitset.h
	$(CC) $(CFLAGS) steg-decode.c

clean:
	rm primes primes-i steg-decode *.o

