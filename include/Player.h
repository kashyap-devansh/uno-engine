#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "Card.h"
#include "Deck.h"

class Game;

class Player {
private :
    int number;
    std::string name;
    std::vector<Card*> hand;

public :
    Player();
    Player(int number, std::string name);

    void setCards(Deck& deck);
    void setNumber(const int number);
    void setName(const std::string name);

    int getHandSize();
    int getNumber() const;
    std::string getName() const;

    void addHandCard(Deck& deck);

    void drawCard(Card* card);
    bool playCard(int index, Game& game);

    Card* getCard(int index) const;

    bool hasPlayableCard(Card* topCard) const;
    bool isHandEmpty() const;

    void displayHand() const; 

    ~Player();
};

#endif