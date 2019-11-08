all:
	gcc -o testme testme.c -g -fpic -coverage -lm -std=c99
	./testme

clean:
	rm -f testme
	rm -f testme.gcda
	rm -f testme.gcno
	rm -rf testme.dSYM