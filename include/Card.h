#ifndef CARD_H
#define CARD_H

#include <string>

enum class Color { RED, YELLOW, GREEN, BLUE, WILD};

class Game;

class Card {
protected :
    Color color;
    std::string name;

public :
    Card(Color color, std::string name);
    virtual ~Card() {}

    Color getColor() const;
    std::string getName() const;

    void setColor(Color newColor);

    virtual bool isPlayable(Card* topCard) const;
    virtual void applyEffect(Game& game);
    virtual void display() const = 0;
};

class NumberCard : public Card {
private :
    int number;

public :
    NumberCard(Color color, int number);

    bool isPlayable(Card* topCard) const override;
    void display() const override;
};

class SkipCard : public Card {
public :
    SkipCard(Color color);

    void applyEffect(Game& game) override;
    void display() const override;
};

class ReverseCard : public Card {
public :
    ReverseCard(Color color);

    void applyEffect(Game& game) override;
    void display() const override;
};

class DrawTwoCard : public Card {
public :    
    DrawTwoCard(Color color);

    void applyEffect(Game& game) override;
    void display() const override;
};

class WildCard : public Card {
public :
    WildCard();

    void applyEffect(Game& game) override;
    void display() const override;
};

class WildDrawFourCard : public Card {
public :
    WildDrawFourCard();

    void applyEffect(Game& game) override;
    void display() const override;
};

std::string colorToString(Color color);

#endif