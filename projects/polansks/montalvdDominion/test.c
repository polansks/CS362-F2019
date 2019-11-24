#include "dominion.h"
#include "rngs.h"
#include <stdio.h>

void initializeBlankDeck(struct gameState *s);
void test1();
void test2();
void test3();
void test4();

int main(int argc, char** argv)
{
	//test1();
	//test2();
	//test3();
	test4();

	return 0;
}

void initializeBlankDeck(struct gameState *s)
{
	for (int i = 0; i < s->numPlayers; i++)
	{
		for (int j = 0; j < MAX_DECK; j++)
		{
			s->deck[i][j] = -1;
			s->discard[i][j] = -1;
		}

		for (int j = 0; j < MAX_HAND; j++)
		{
			s->hand[i][j] = -1;
		}

		s->deckCount[i] = 0;
		s->discardCount[i] = 0;
		s->handCount[i] = 0;
	}

	s->whoseTurn = 0;
}

void test1()
{
	struct gameState g;
	g.numPlayers = 1;

	initializeBlankDeck(&g);

	g.handCount[0] = 4;
	g.discardCount[0] = 1;
	g.deckCount[0] = 4;

	g.hand[0][0] = village;
	g.hand[0][1] = village;
	g.hand[0][2] = village;
	g.hand[0][3] = village;

	g.discard[0][0] = village;

	g.deck[0][0] = village;
	g.deck[0][1] = estate;
	g.deck[0][2] = estate;
	g.deck[0][3] = estate;

	int score = scoreFor(0, &g);

	printf("calculated score: %d\n", score);
}

void test2()
{
	struct gameState g;
	g.numPlayers = 1;

	initializeBlankDeck(&g);

	g.handCount[0] = 3;

	g.hand[0][0] = feast;
	g.hand[0][1] = gold;
	g.hand[0][1] = gold;

	g.supplyCount[estate]   = 1;   // cost = 2
	g.supplyCount[province] = 1;   // cost = 8

	int returnValue = cardEffect(feast, province, 0, 0, &g, 0, NULL);

	for (int i = 0; i < g.discardCount[0]; i++)
	{
		printf("card[%d]: %d\n", i, g.discard[0][i]);
	}

}

void test3()
{
	struct gameState *g = malloc(sizeof(struct gameState));
	g->numPlayers = 2;

	initializeBlankDeck(g);

	g->whoseTurn = 0;

	g->handCount[0] = 1;
	g->hand[0][0] = tribute;

	g->deckCount[1] = 3;
	g->discardCount[1] = 0;
	g->deck[1][0] = gold;
	g->deck[1][1] = copper;
	g->deck[1][2] = silver;

	updateCoins(0, g, 0);
	int coinsBefore = g->coins;

	int returnValue = cardEffect(tribute, 0, 0, 0, g, 0, NULL);

	int coinsAfter = g->coins;

	printf("coins before: %d, coins after: %d\n", coinsBefore, coinsAfter);
}

void test4()
{
	struct gameState g;
	g.numPlayers = 2;

	initializeBlankDeck(&g);

	g.whoseTurn = 0;

	g.handCount[0] = 2;
	g.hand[0][0] = copper;
	g.hand[0][1] = minion;

	updateCoins(0, &g, 0);
	int coinsBefore = g.coins;

	playCard(1, 1, 0, 0, &g);

	int coinsAfter = g.coins;

	printf("coins before: %d, coins after: %d\n", coinsBefore, coinsAfter);
}