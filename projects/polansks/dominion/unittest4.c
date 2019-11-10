#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>


/* This program will unit test the playTribute function that was created     */
/* when refactoring in Assignment 2                                         */

/************ Card Text *****************************************************/
/* The player to your left reveals then discards the top 2 cards of his     */
/* deck. For each differently named card revealed, if it is an...           */
/* Action Card, +2 actions                                                  */
/* Treasure Card, +2 coins                                                  */
/* Victory Card, +2 cards                                                   */
/****************************************************************************/

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void initializeGameState(struct gameState *g);
void assertFailed(char *file, int line);

int main()
{
	printf("--------Testing playTribute function---------\n\n");

	struct gameState gameBase, gameBefore, gameAfter;

	int currentPlayer, nextPlayer;
	currentPlayer = 0;
	nextPlayer    = currentPlayer + 1;

	initializeGameState(&gameBase);

	gameBase.whoseTurn = currentPlayer;

	printf("Testing reveal 2 cards from deck: two action cards\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		/* for the next player, set the next two cards in the deck to be action cards */
		gameBefore.deck[nextPlayer][gameBefore.deckCount[nextPlayer] - 1] = feast;
		gameBefore.deck[nextPlayer][gameBefore.deckCount[nextPlayer] - 2] = mine;

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		playTribute(&gameAfter);

		ASSERT(gameAfter.deckCount[nextPlayer] = gameBefore.deckCount[nextPlayer] + 2);
		ASSERT(gameAfter.numActions = gameBefore.numActions + 4);
	}


	printf("Testing reveal 2 cards when only 1 card in deck and reshuffle needed\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		/* for the next player, copy their deck to the discard pile except for the first card in the deck */
		memcpy(gameBefore.discard[nextPlayer], gameBefore.deck[nextPlayer] + sizeof(int), sizeof(int) * (gameBefore.deckCount[nextPlayer] - 1));
		gameBefore.discardCount[nextPlayer] = gameBefore.deckCount[nextPlayer] - 1;
		gameBefore.deckCount[nextPlayer] = 1;

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		playTribute(&gameAfter);

		ASSERT(gameAfter.discardCount[nextPlayer] == 0); /* there should be no cards in the next player's discard pile because it was shuffled */
	}


	printf("Testing reveal 2 cards when no cards in deck and reshuffle needed\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		/* for the next player, copy their deck to the discard pile */
		memcpy(gameBefore.discard[nextPlayer], gameBefore.deck[nextPlayer] + sizeof(int), sizeof(int) * gameBefore.deckCount[nextPlayer]);
		gameBefore.discardCount[nextPlayer] = gameBefore.deckCount[nextPlayer];
		gameBefore.deckCount[nextPlayer] = 0;

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		playTribute(&gameAfter);

		ASSERT(gameAfter.discardCount[nextPlayer] == 0); /* there should be no cards in the next player's discard pile because it was shuffled */
	}

	printf("Testing reveal 2 cards but only 1 card left and it is in deck\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		gameBefore.discardCount[nextPlayer] = 0;
		gameBefore.deckCount[nextPlayer] = 1;
		gameBefore.deck[nextPlayer][0] = feast;

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		playTribute(&gameAfter);

		ASSERT(gameAfter.numActions = gameBefore.numActions + 2);
		ASSERT(gameAfter.coins = gameBefore.coins);
		ASSERT(gameAfter.handCount[currentPlayer] == gameBefore.handCount[currentPlayer]);
	}

	printf("Testing reveal 2 cards from deck: two victory cards\n");
	{
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		/* for the next player, set the next two cards in the deck to be action cards */
		gameBefore.deck[nextPlayer][gameBefore.deckCount[nextPlayer] - 1] = great_hall;
		gameBefore.deck[nextPlayer][gameBefore.deckCount[nextPlayer] - 2] = estate;

		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		playTribute(&gameAfter);

		ASSERT(gameAfter.deckCount[nextPlayer] = gameBefore.deckCount[nextPlayer] + 2);
		ASSERT(gameAfter.handCount[currentPlayer] == gameBefore.handCount[currentPlayer] + 4);
	}

	return 0;
}


void initializeGameState(struct gameState *g)
{
	int numPlayers = 2;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randomSeed = 5;

	initializeGame(numPlayers, kingdomCards, randomSeed, g);

	return;
}

void assertFailed(char *file, int line)
{
	printf("assertion failed on line %d in file %s\n", line, file);
}