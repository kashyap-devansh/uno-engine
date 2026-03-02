#include <iostream>
#include <iomanip>
#include "Card.h"
#include "Game.h"

//-------------------- CARD DISPLAY HELPER --------------------

static void displayCard(const std::string& color, const std::string& line1, const std::string& line2 = "") {
    std::cout << "+-------+\n";
    std::cout << "| " << std::left << std::setw(5) << color << " |\n";
    std::cout << "| " << std::left << std::setw(5) << line1 << " |\n";
    std::cout << "| " << std::left << std::setw(5) << line2 << " |\n";
    std::cout << "+-------+\n";
}

//-------------------- BASE CARD CLASS --------------------

Card::Card(Color color, std::string name) : color(color), name(name) {}

Color Card::getColor() const { return color; }

std::string Card::getName() const { return name; }

bool Card::isPlayable(Card* topCard) const {
    if(!topCard) return true;

    return color == topCard->getColor() || name == topCard->getName() || color == Color::WILD;
}

void Card::applyEffect(Game& game) {}

void Card::setColor(Color newColor) { color = newColor; }

//-------------------- NUMBER CARD CLASS --------------------

NumberCard::NumberCard(Color color, int number) : Card(color, std::to_string(number)), number(number) {}

bool NumberCard::isPlayable(Card* topCard) const {
    if(!topCard) return true;

    if(color == topCard->getColor()) return true;

    NumberCard* topNumber = dynamic_cast<NumberCard*>(topCard);
    return topNumber && topNumber->number == number;
}

void NumberCard::display() const {
    displayCard(colorToString(color), std::to_string(number));
}

//-------------------- SKIP CARD CLASS --------------------

SkipCard::SkipCard(Color color) : Card(color, "SKIP") {}

void SkipCard::applyEffect(Game& game) {
    game.skipNextPlayer();
}

void SkipCard::display() const {
    displayCard(colorToString(color), "SKIP");
}

//-------------------- REVERSE CARD CLASS --------------------

ReverseCard::ReverseCard(Color color) : Card(color, "REVERSE") {}

void ReverseCard::applyEffect(Game& game) {
    game.reverseDirection();
}

void ReverseCard::display() const {
    displayCard(colorToString(color), "REVERSE");
}

//-------------------- DRAW TWO CARD CLASS --------------------

DrawTwoCard::DrawTwoCard(Color color) : Card(color, "+2") {}

void DrawTwoCard::applyEffect(Game& game) {
    game.drawCard(game.getNextPlayer(), 2);
    game.skipNextPlayer();
}

void DrawTwoCard::display() const {
    displayCard(colorToString(color), "DRAW", "+2");
}

//-------------------- WILD CARD CLASS --------------------

WildCard::WildCard() : Card(Color::WILD, "WILD") {}

void WildCard::applyEffect(Game& game) {
    game.chooseColor();
}

void WildCard::display() const {
    displayCard("WILD", "WILD");
}

//-------------------- WILD DRAW FOUR CARD CLASS --------------------

WildDrawFourCard::WildDrawFourCard() : Card(Color::WILD, "+4") {}

void WildDrawFourCard::applyEffect(Game& game) {
    game.drawCard(game.getNextPlayer(), 4);
    game.chooseColor();
    game.skipNextPlayer();
}

void WildDrawFourCard::display() const {
    displayCard("WILD", "DRAW", "+4");
}

//-------------------- COLOR TO STRING --------------------

std::string colorToString(Color color) {
    switch(color) {
        case Color::RED:    return "RED";
        case Color::BLUE:   return "BLUE";
        case Color::YELLOW: return "YELLOW";
        case Color::GREEN:  return "GREEN";
        case Color::WILD:   return "WILD";
    }
    return "";
}
