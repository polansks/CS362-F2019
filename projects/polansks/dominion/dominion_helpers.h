#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);
int playAmbassador(int choice1, int choice2, struct gameState *state, int handPos);
int playMine(int choice1, int choice2, struct gameState *state);
int playMinion(int choice1, int choice2, struct gameState *state, int handPos);
int playTribute(struct gameState *state);
int playBaron(int choice1, struct gameState *state)
#endif
