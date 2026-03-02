#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>

class Deck {
private :
    std::vector<Card* > deck;

public :
    Card* drawRandomCard();

    int getDeckSize();

    Deck();
    ~Deck();

    Card* getCard(int index) const;
};

#endif