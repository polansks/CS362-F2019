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

unittestresults: unittest1 unittest2 unittest3 unittest4 unittest5 unittest7 unittest8 unittest9 unittest10
	@echo "Running unit tests..."
	@echo "Unit Test 1" > unittestresults.out
	@./unittest1 >> unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "discardCard" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "\nUnit Test 2" >> unittestresults.out
	@./unittest2 >> unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "discardCard" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "\nUnit Test 3" >> unittestresults.out
	@./unittest3 >>  unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "cardEffect" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "\nUnit Test 4" >> unittestresults.out
	@./unittest4 >>  unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "cardEffect" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "Unit Test 5" > unittestresults.out
	@./unittest5 >> unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "scoreFor" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "\nUnit Test 7" >> unittestresults.out
	@./unittest7 >> unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "cardEffect" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "\nUnit Test 8" >> unittestresults.out
	@./unittest8 >>  unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "playCard" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "\nUnit Test 9" >> unittestresults.out
	@./unittest9 >>  unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "cardEffect" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo -e "\nUnit Test 10" >> unittestresults.out
	@./unittest10 >>  unittestresults.out
	@echo -e "\nCoverage Results:" >> unittestresults.out
	@gcov dominion.c -b -f | grep -h "scoreFor" -A 2 >> unittestresults.out
	@rm dominion.gcda
	@echo "Unit tests complete"

unittest1: dominion.o rngs.o unittest1.c
	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)

unittest2: dominion.o rngs.o unittest2.c
	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)

unittest3: dominion.o rngs.o unittest3.c
	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)

unittest4: dominion.o rngs.o unittest4.c
	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)

unittest5: dominion.o rngs.o unittest5.c
	gcc -o unittest5 unittest5.c -g dominion.o rngs.o $(CFLAGS)

unittest7: dominion.o rngs.o unittest7.c
	gcc -o unittest7 unittest7.c -g dominion.o rngs.o $(CFLAGS)

unittest8: dominion.o rngs.o unittest8.c
	gcc -o unittest8 unittest8.c -g dominion.o rngs.o $(CFLAGS)

unittest9: dominion.o rngs.o unittest9.c
	gcc -o unittest9 unittest9.c -g dominion.o rngs.o $(CFLAGS)

unittest10: dominion.o rngs.o unittest10.c
	gcc -o unittest10 unittest10.c -g dominion.o rngs.o $(CFLAGS)
