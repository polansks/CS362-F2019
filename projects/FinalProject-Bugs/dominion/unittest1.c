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
    int k[10] = {baron, ambassador, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute, smithy
                };

    printf ("Starting unit Test for Bug 1\n");
    printf ("\n------------------------TESTING FOR CORRECT TRASHING-----------------\n");
	int numPlayer = 2;
	int seed = 23;
    memset(&G, 23, sizeof(struct gameState));
    initializeGame(numPlayer, k, seed, &G);
    int p = 0;
    G.coins = 0;
    G.playedCardCount = 0;	
    G.deckCount[1] = 1;
    G.handCount[p] = 5;
    G.hand[0][0] = mine;
    G.hand[0][1] = estate;
    G.hand[0][2] = copper;
    G.hand[0][3] = copper;
    G.hand[0][4] = copper;
    int choice1 = 2;
    int bonus = -1;
    cardEffect(mine, choice1, silver, -1, &G, 0, &bonus);
    assert(G.playedCardCount == 1 ); 
    return 0;
}
