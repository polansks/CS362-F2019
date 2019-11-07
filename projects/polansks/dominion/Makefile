CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

unittest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o -g $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c dominion.o rngs.o -g $(CFLAGS)

unittest3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c dominion.o rngs.o -g $(CFLAGS)

unittest4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c dominion.o rngs.o -g $(CFLAGS)

unittest5: dominion.o unittest5.c
	gcc -o unittest5 unittest5.c dominion.o rngs.o -g $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5

cleanunittests:
	rm unittest[1-9]
	rm unittest[1-9].gcno

all: playdom player 

clean: cleanunittests
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
