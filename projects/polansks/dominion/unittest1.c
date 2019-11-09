#include <stdio.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <string.h>


/* This program will unit test the playAmbassador function that was created */
/* when refactoring in Assignment 2                                         */

/************ Card Text *****************************************************/
/* Reveal a card from your hand. Return up to 2 copies of it from your hand */
/* to the Supply. Then each other player gains a copy of it.                */
/****************************************************************************/

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void initializeGameState(struct gameState *g);
void assertFailed(char *file, int line);

int main()
{
	printf("--------Testing playAmbassador function---------\n\n");
	
	struct gameState gameBase, gameBefore, gameAfter;

	int handPos;
	int choice1; /* This is the card being revealed. It must be in the player's hand. */
	int choice2; /* This is the number of copies of card that was revealed that is being put back in the supply. Must be 0, 1 or 2 */
	int returnValue;
	int currentPlayer, otherPlayer;

	initializeGameState(&gameBase);

	currentPlayer = 1; otherPlayer = 0;
	handPos = 0;
	gameBase.hand[currentPlayer][handPos] = ambassador; /* set the card being played to be an ambassador */
	gameBase.whoseTurn = currentPlayer; // also set whose turn to be player 2

	printf("Testing invalid choice2 value of -1\n");
	{
		choice1 = 1; /* Whatever the second card in the hand is, reveal that one */
		choice2 = -1; /* invalid value */
		
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		returnValue = playAmbassador(choice1, choice2, &gameAfter, handPos);

		/* Use asserts to check that the function has worked properly */
		/* In this case, the function should return -1 and no values in the game
		   state should change because invalid options were chosen */
		ASSERT(returnValue == -1);
		
		ASSERT(memcmp(&gameBefore, &gameAfter, sizeof(struct gameState)) == 0); /* the game state shouldn't have changed because we tried to play the card in an invalid way */
	}

	printf("Testing invalid choice2 value of 3\n");
	{
		choice1 = 1; /* Whatever the second card in the hand is, reveal that one */
		choice2 = -3; /* invalid value */
		
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		returnValue = playAmbassador(choice1, choice2, &gameAfter, handPos);

		/* Use asserts to check that the function has worked properly */
		/* In this case, the function should return -1 and no values in the game
		   state should change because invalid options were chosen */
		ASSERT(returnValue == -1);
		
		ASSERT(memcmp(&gameBefore, &gameAfter, sizeof(struct gameState)) == 0); /* the game state shouldn't have changed because we tried to play the card in an invalid way */
	}

	printf("Testing valid option for choice1 and choice2\n");
	{
		choice1 = handPos + 1; /* Whatever the first card in the hand is, reveal that one */
		choice2 = 1;
		
		memcpy(&gameBefore, &gameBase, sizeof(struct gameState));

		gameBefore.hand[currentPlayer][choice1 + 1] = gameBefore.hand[currentPlayer][choice1]; /* make sure there is another card in the hand that matches the one we're revealing */
		
		memcpy(&gameAfter, &gameBefore, sizeof(struct gameState));

		returnValue = playAmbassador(choice1, choice2, &gameAfter, handPos);

		/* Use asserts to check that the function has worked properly */
		ASSERT(returnValue == 0);
		ASSERT(gameBefore.handCount[currentPlayer] - 1 - choice2 == gameAfter.handCount[currentPlayer]);
		ASSERT(gameBefore.handCount[otherPlayer] + 1 == gameAfter.handCount[otherPlayer]);
	}

	return 0;
}


void initializeGameState(struct gameState *g)
{
	int numPlayers = 3;
	int kingdomCards[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
	int randomSeed = 5;

	initializeGame(numPlayers, kingdomCards, randomSeed, g);

	return;
}

void assertFailed(char *file, int line)
{
	printf("assertion failed on line %d in file %s\n", line, file);
}