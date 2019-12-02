#include "dominion.h"
#include "rngs.h"
#include "dominion_helpers.h"
#include <stdio.h>

#define ASSERT(expr) \
	if (!(expr)) assertFailed(__FILE__, __LINE__); else printf("check passed\n");

void assertFailed(char *file, int line);

int main(int argc, char** argv)
{
	struct gameState state;

	state.numPlayers = 1;
	state.handCount[0] = 0;
	state.discardCount[0] = 0;
	state.deckCount[0] = 1;
	state.deck[0][0] = estate;

	ASSERT(scoreFor(0, &state) == 1);

	return 0;
}

void assertFailed(char *file, int line)
{
	printf("assertion failed on line %d in file %s\n", line, file);
}