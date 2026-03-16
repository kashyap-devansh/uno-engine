#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Card.h"
#include "Player.h"
#include "Deck.h"

class Game {
private:
    int playerCount;
    int currentPlayer;
    int direction;
    Card* topCard;
    std::vector<Player*> players;
    Deck* deck;

public :
    Game(int players, Deck* deck, const std::vector<Player*>& playersList);

    void displayTopCard() const ;

    void setTopCard(Card* card);
    Card* getTopCard() const;

    int getNextPlayer() const;
    void advanceTurn();

    void skipNextPlayer();
    void reverseDirection();
    void drawCard(int playerIndex, int count);
    void chooseColor();

    int getCurrentPlayer() const;

    ~Game();
};

#endif