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

all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe

unittestresults: unittest5 unittest7 unittest8
	@echo "Running unit tests..."
	@echo "Unit Test 5" > unittestresults.out
	@./unittest5 >> unittestresults.out
	@echo "Unit Test 7" >> unittestresults.out
	@./unittest7 >> unittestresults.out
	@echo "Unit Test 8" >> unittestresults.out
	@./unittest8 >>  unittestresults.out
	@echo "Unit tests complete"

unittest5: dominion.o rngs.o unittest5.c
	gcc -o unittest5 unittest5.c -g dominion.o rngs.o $(CFLAGS)

unittest7: dominion.o rngs.o unittest7.c
	gcc -o unittest7 unittest7.c -g dominion.o rngs.o $(CFLAGS)

unittest8: dominion.o rngs.o unittest8.c
	gcc -o unittest8 unittest8.c -g dominion.o rngs.o $(CFLAGS)