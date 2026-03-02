#include "Deck.h"
#include <ctime>

Deck::Deck() {
    for(Color color : {Color::RED, Color::BLUE, Color::GREEN, Color::YELLOW}) {
        deck.push_back(new NumberCard(color, 0));

        for(int i = 1; i <= 9; i++) {
            deck.push_back(new NumberCard(color, i));
            deck.push_back(new NumberCard(color, i));
        }
    }

    for(Color color : {Color::BLUE, Color::GREEN, Color::RED, Color::YELLOW}) {
        deck.push_back(new SkipCard(color));
        deck.push_back(new SkipCard(color));

        deck.push_back(new ReverseCard(color));
        deck.push_back(new ReverseCard(color));

        deck.push_back(new DrawTwoCard(color));
        deck.push_back(new DrawTwoCard(color));
    }

    for(int i = 0; i < 4; i++) {
        deck.push_back(new WildCard());
        deck.push_back(new WildDrawFourCard());
    }
}

Card* Deck::getCard(int index) const {
    if(index < 0 || index >= deck.size()) { return nullptr; }

    return deck[index];
}

Card* Deck::drawRandomCard() {
    if(deck.empty()) return nullptr;

    int index = rand() % deck.size();
    Card* card = deck[index];

    deck.erase(deck.begin() + index);
    return card;
}

int Deck::getDeckSize() { return deck.size(); }

Deck::~Deck() {
    for(Card* card : deck) {
        delete card;
    }
}