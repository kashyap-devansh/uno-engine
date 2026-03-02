#include "Player.h"
#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Player::Player() : number(-1), name("Unkown") {}

Player::Player(int number, std::string name) : number(number), name(name) {}

void Player::setNumber(const int number) { this->number = number; }

void Player::setName(const std::string name) { this->name = name; }

int Player::getHandSize() { return hand.size(); }

int Player::getNumber() const { return number; }

std::string Player::getName() const { return name; }

void Player::drawCard(Card* card) { hand.push_back(card); }

void Player::addHandCard(Deck& deck) {
    Card* card = deck.drawRandomCard();

    if(card) hand.push_back(card);
}

void Player::setCards(Deck& deck) {
    for(int i = 0; i < 7; i++) {
        Card* card = deck.drawRandomCard();

        if(card) hand.push_back(card);
    }
}

bool Player::playCard(int index, Game& game) {
    if(index < 0 || index >= hand.size()) return false;

    Card* card = hand[index];

    game.setTopCard(card);
    card->applyEffect(game);

    hand.erase(hand.begin() + index);
    return true;
}

Card* Player::getCard(int index) const { return hand[index]; }

bool Player::hasPlayableCard(Card* topCard) const {
    for(Card* card : hand) {
        if(card->isPlayable(topCard)) return true;
    }

    return false;
}

bool Player::isHandEmpty() const {
    return hand.empty();
}

void Player::displayHand() const {
    std::cout << "Player " << number << " Hand : \n";

    for(int i = 0; i < hand.size(); i++) {
        hand[i]->display();
    }
}

Player::~Player() {
    for(Card* card : hand) {
        delete card;
    }
}