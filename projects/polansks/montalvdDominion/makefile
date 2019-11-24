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

randomtestresults: randomtestcard1 randomtestcard2 randomtestcard3
	./randomtestcard1 -> randomtestresults.out
	echo "" >> randomtestresults.out
	gcov dominion.c -b -f | grep -h "baronEffect" -A 2 >> randomtestresults.out
	echo "" >> randomtestresults.out
	./randomtestcard2 >> randomtestresults.out
	echo "" >> randomtestresults.out
	gcov dominion.c -b -f | grep -h "minionEffect" -A 2 >> randomtestresults.out
	echo "" >> randomtestresults.out
	./randomtestcard3 >> randomtestresults.out
	echo "" >> randomtestresults.out
	gcov dominion.c -b -f | grep -h "tributeEffect" -A 2 >> randomtestresults.out
	echo "" >> randomtestresults.out

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -o randomtestcard1 randomtestcard1.c dominion.o rngs.o -g -O0 $(CFLAGS)

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -o randomtestcard2 randomtestcard2.c -g -O0 dominion.o rngs.o $(CFLAGS)

randomtestcard3: randomtestcard3.c dominion.o rngs.o
	gcc -o randomtestcard3 randomtestcard3.c -g -O0 dominion.o rngs.o $(CFLAGS)

unittest1: dominion.o unittest1.c
	gcc -o unittest1 unittest1.c dominion.o rngs.o -g -O0 $(CFLAGS)

unittest2: dominion.o unittest2.c
	gcc -o unittest2 unittest2.c dominion.o rngs.o -g -O0 $(CFLAGS)

unittest3: dominion.o unittest3.c
	gcc -o unittest3 unittest3.c dominion.o rngs.o -g -O0 $(CFLAGS)

unittest4: dominion.o unittest4.c
	gcc -o unittest4 unittest4.c dominion.o rngs.o -g -O0 $(CFLAGS)

unittest5: dominion.o unittest5.c
	gcc -o unittest5 unittest5.c dominion.o rngs.o -g -O0 $(CFLAGS)

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5
	./unittest1 -> unittestresults.out
	echo "" >> unittestresults.out
	gcov dominion.c -b -f | grep -h "ambassadorEffect" -A 2 >> unittestresults.out
	echo "" >> unittestresults.out
	./unittest2 >> unittestresults.out
	echo "" >> unittestresults.out
	gcov dominion.c -b -f | grep -h "mineEffect" -A 2 >> unittestresults.out
	echo "" >> unittestresults.out
	./unittest3 >> unittestresults.out
	echo "" >> unittestresults.out
	gcov dominion.c -b -f | grep -h "minionEffect" -A 2 >> unittestresults.out
	echo "" >> unittestresults.out
	./unittest4 >> unittestresults.out
	echo "" >> unittestresults.out
	gcov dominion.c -b -f | grep -h "tributeEffect" -A 2 >> unittestresults.out
	echo "" >> unittestresults.out
	./unittest5 >> unittestresults.out
	echo "" >> unittestresults.out
	gcov dominion.c -b -f | grep -h "baronEffect" -A 2 >> unittestresults.out
	echo "" >> unittestresults.out
	
all: playdom player 

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
