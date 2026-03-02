#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "Card.h"
#include "Deck.h"
#include "Game.h"
#include "Player.h"

void mainMenu();

void startGame();

Card* drawTopCard(Deck& deck);

void setPlayers(int count, std::vector<Player>& players, Deck& deck);

void displayRules();

#endif