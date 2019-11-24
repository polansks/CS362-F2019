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

int baronEffect(int choice1, struct gameState *state, int currentPlayer);
int minionEffect(int handPos, struct gameState *state, int currentPlayer, int choice2, int choice1);
int ambassadorEffect(struct gameState *state, int choice1, int choice2, int handPos, int currentPlayer);
int tributeEffect(struct gameState *state, int currentPlayer, int nextPlayer);
int mineEffect(struct gameState *state, int choice1, int choice2, int currentPlayer, int handPos);

int isTreasureCard(int card);
int isVictoryCard(int card);
#endif