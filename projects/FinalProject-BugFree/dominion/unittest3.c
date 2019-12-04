#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

int cardEffect( int, int, int, int, struct gameState*, int, int*);
void assert(bool exp){
	if(exp)
	    printf("\nAssertion true\n\n");
	else
	    printf("\nAssertion false\n\n");
}

int main(){
    struct gameState G;
    int k[10] = {remodel, ambassador, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy
                };

    printf ("Starting unit Test for Bug 3\n");
    printf ("\n------------------------TESTING FOR CORRECT DISCARDING-----------------\n");
	int numPlayer = 2;
	int seed = 23;
	int r;
    memset(&G, 23, sizeof(struct gameState));
    r = initializeGame(numPlayer, k, seed, &G);
    int p = 0;
    G.coins = 0;
    G.playedCardCount = 0;	
    G.deckCount[1] = 1;
    G.handCount[p] = 5;
    G.hand[0][0] = remodel;
    G.hand[0][1] = estate;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    int choice1 = 2;
    int bonus = -1;
    cardEffect(remodel, choice1, copper, -1, &G, 0, &bonus);
    assert(G.playedCardCount == 2); 
    return 0;
}
