#include "Game.h"

Game::Game(int players, Deck* deck, const std::vector<Player*>& playersList) : playerCount(players), currentPlayer(0), direction(1), topCard(nullptr), deck(deck), players(playersList) {}

std::vector<Card*> discardPile;

void Game::setTopCard(Card* card) { 
    if(topCard) {
        discardPile.push_back(topCard);
    }

    topCard = card; 
}

void Game::displayTopCard() const { topCard->display(); }

Card* Game::getTopCard() const { return topCard; }

int Game::getNextPlayer() const {
    int next = currentPlayer + direction;

    if(next < 0) next = playerCount - 1;
    else if(next >= playerCount) next = 0;

    return next;
}

void Game::advanceTurn() { currentPlayer = getNextPlayer(); }

void Game::skipNextPlayer() {
    advanceTurn();
    advanceTurn();
}

void Game::reverseDirection() {
    direction *= -1;
}

void Game::drawCard(int playerIndex, int count) {
    if(!deck) {
        std::cout << "Error : Deck not initialized!\n";
        return;
    }

    if(playerIndex < 0 || playerIndex >= players.size()) {
        std::cout << "Error : Invalid player index!\n";
        return;
    }

    for(int i = 0; i < count; i++) {
        Card* card = deck->drawRandomCard();
        
        if(!card) {
            std::cout << "Error : Deck is empty!\n";
            return;
        }

        players[playerIndex]->drawCard(card);
    }
}

void Game::chooseColor() {
    if(!topCard) {
        std::cerr << "Error : No top card set!\n";
        return;
    }

    int choice = 0;

    std::cout << "Player " << currentPlayer << ", choose a color : \n";
    std::cout << "1 - RED\n2 - YELLOW\n3 - GREEN\n4 - BLUE\nChoice : ";
    std::cin >> choice;

    Color chosen; 

    switch(choice) {
        case 1 : chosen = Color::RED; break;
        case 2 : chosen = Color::YELLOW; break;
        case 3 : chosen = Color::GREEN; break;
        case 4 : chosen = Color::BLUE; break;
        default : {
            std::cout << "Invalid choice, defaulting to Color RED\n"; 
            chosen = Color::RED;
        }
    }

    topCard->setColor(chosen);
}

int Game::getCurrentPlayer() const { return currentPlayer; }

Game::~Game() {
    for(Card* card : discardPile) delete card;

    if(topCard) delete topCard;
}