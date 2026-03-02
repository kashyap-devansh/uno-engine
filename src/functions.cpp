#include <iostream>
#include "functions.h"

void mainMenu() {
    bool stop = false;

    while(!stop) {
        char choice;
        bool validChoice = false;

        std::cout << "\n=============================\n";
        std::cout << "           UNO GAME          \n";
        std::cout << "=============================\n";
        std::cout << "1. Start New Game\n";
        std::cout << "2. Game Rules\n";
        std::cout << "3. Exit\n";
        std::cout << "-------------------------------\n";
        std::cout << "Enter your choice: ";

        while(!validChoice) {
            std::cin >> choice;
            if(choice == '1' || choice == '2' || choice == '3') validChoice = true;
        }

        switch(choice) {
            case '1' : startGame(); break;
            case '2' : displayRules(); break;
            case '3' : {
                std::cout << "Thanking for Playing the Game...\n";
                std::cout << "Existing the Game..\n";
                exit(0);
            }
            default : return;
        }
    }
}

void startGame() {
    int playerCount;
    std::cout << "Enter the Number of Player in the Game : ";
    std::cin >> playerCount;

    std::vector<Player> players(playerCount);

    Deck deck;

    setPlayers(playerCount, players, deck);

    std::vector<Player*> playerPtrs;
    for(auto& p : players) {
        playerPtrs.push_back(&p);
    }

    Game game(playerCount, &deck, playerPtrs);

    Card* topCard = drawTopCard(deck);
    game.setTopCard(topCard);

    bool winner = false;

    while(!winner) {
        int i = game.getCurrentPlayer();

        std::cout << "\n\nDisplaying Top Card : \n";
        game.displayTopCard();
        std::cout << std::endl;

        if(players[i].isHandEmpty()) {
            std::cout << players[i].getName() << " Wins!\n";
            return;
        }

        if(!players[i].hasPlayableCard(game.getTopCard())) {
            std::cout << "Player " << players[i].getName() << "\n";
            std::cout << "No Playable Card. Drawing one...\n";
            players[i].addHandCard(deck);

            if(!players[i].hasPlayableCard(game.getTopCard())) {
                std::cout << "Turn skipped.\n";
                game.advanceTurn();
                continue;
            }

            std::cout << "Playable card drawn! You may play.\n";
        }

        players[i].displayHand();

        bool validCard = false;
        int cardNumber = 0;

        while(!validCard) {
            std::cout << "Player " << players[i].getName() << "\n";
            std::cout << "Enter your Card Number : ";
            std::cin >> cardNumber;

            if(cardNumber < 1 || cardNumber > players[i].getHandSize()) continue;

            Card* selectedCard = players[i].getCard(cardNumber - 1);
            if(selectedCard && selectedCard->isPlayable(game.getTopCard())) {
                validCard = true;
            }
        }

        players[i].playCard((cardNumber - 1), game);
        topCard = game.getTopCard();

        game.advanceTurn();  
    }

    delete topCard;
}

void setPlayers(int count, std::vector<Player>& players, Deck& deck) {
    std::string playerName;
    std::cin.ignore();

    for(int i = 0; i < count; i++) {
        players[i].setNumber(i + 1);

        std::cout << "Enter the name of Player " << (i + 1) << ": ";
        std::getline(std::cin, playerName);

        players[i].setName(playerName);
        players[i].setCards(deck);
    }
}

Card* drawTopCard(Deck& deck) {
    Card* topCard = nullptr;

    while(true) {
        Card* drawn = deck.drawRandomCard();
        
        if(!drawn) { std::cout << "Deck is empty!\n"; exit(1); }

        if(dynamic_cast<NumberCard*>(drawn)) { 
            topCard = drawn;
            break;
        }

        delete drawn;
    }

    return topCard;
}

void displayRules() {
    std::cout << "=====================================\n";
    std::cout << "           UNO GAME RULES             \n";
    std::cout << "=====================================\n\n";

    std::cout << "1. Objective:\n";
    std::cout << "   Be the first player to get rid of all your cards.\n\n";

    std::cout << "2. Number of Players:\n";
    std::cout << "   2 to 10 players can play UNO.\n\n";

    std::cout << "3. Cards:\n";
    std::cout << "   - Number cards: 0 to 9\n";
    std::cout << "   - Action cards: Skip, Reverse, Draw Two\n";
    std::cout << "   - Wild cards: Wild, Wild Draw Four\n\n";

    std::cout << "4. Gameplay:\n";
    std::cout << "   - Each player starts with 7 cards.\n";
    std::cout << "   - Match a card by color, number, or symbol.\n";
    std::cout << "   - If you can't play a card, draw one from the deck.\n\n";

    std::cout << "5. Action Cards:\n";
    std::cout << "   - Skip: Next player loses a turn.\n";
    std::cout << "   - Reverse: Reverses the direction of play.\n";
    std::cout << "   - Draw Two: Next player draws 2 cards and skips turn.\n\n";

    std::cout << "6. Wild Cards:\n";
    std::cout << "   - Wild: Change the current color.\n";
    std::cout << "   - Wild Draw Four: Change color, next player draws 4 cards and skips turn.\n\n";

    std::cout << "7. UNO Call:\n";
    std::cout << "   - When you have only one card left, you must say \"UNO\".\n";
    std::cout << "   - Failure to do so results in drawing 2 penalty cards.\n\n";

    std::cout << "8. Winning:\n";
    std::cout << "   - The first player to have no cards left wins the game.\n\n";

    std::cout << "=====================================\n\n";
}