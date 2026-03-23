<div align="center">
  <h1>🃏 UNO</h1>
  <p>
    <strong>A fully featured, terminal-based implementation of the classic UNO card game built entirely from scratch in C++.</strong>
  </p>
  <p>
    <img src="https://img.shields.io/badge/C++-17+-blue.svg?logo=c%2B%2B" alt="C++" />
    <img src="https://img.shields.io/badge/License-MIT-green.svg" alt="License" />
    <img src="https://img.shields.io/badge/Platform-Windows%20%7C%20macOS%20%7C%20Linux-lightgrey.svg" alt="Platform" />
    <img src="https://img.shields.io/badge/Status-Active-brightgreen.svg" alt="Status" />
    <img src="https://img.shields.io/badge/Dependencies-None-orange.svg" alt="Zero Dependencies" />
  </p>
</div>

---

## 📖 Overview

**UNO** is a complete, terminal-based implementation of the classic UNO card game, written entirely in C++. It supports 2–10 players in a shared-screen hot-seat format, faithfully reproducing all standard UNO rules — including action cards, wild cards, color selection, forced draws, skip and reverse mechanics, and automatic turn management.

### 🛠️ Built 100% From Scratch in C++

Every component of the game is a custom, hand-written C++ implementation with no third-party game or UI libraries involved:

- **Zero External Dependencies** — No game frameworks, no GUI toolkits, no external card libraries. Pure C++ and the standard library.
- **Polymorphic Card Hierarchy** — All seven card types (`NumberCard`, `SkipCard`, `ReverseCard`, `DrawTwoCard`, `WildCard`, `WildDrawFourCard`) inherit from a common `Card` base class. Each overrides `isPlayable()`, `applyEffect()`, and `display()` independently.
- **Object-Oriented Game Engine** — The `Game` class encapsulates all runtime state: turn order, direction, the active top card, the discard pile, and player references. All card effects interact with the game exclusively through the `Game` interface.
- **Live Deck with Random Draw** — The `Deck` builds the full 108-card standard UNO deck on construction and supports random-index card removal, accurately simulating a shuffled draw pile.
- **Discard Pile & Memory Management** — Played cards are tracked in a discard pile and properly cleaned up at game end. The ownership model ensures no card is double-freed between the player's hand, the top card slot, and the discard pile.
- **Terminal Card Rendering** — Each card renders itself as an ASCII art block in the terminal, with color label, card name, and value displayed in a consistent bordered frame.

---

## ⚙️ Architecture

The game is structured as a clean object-oriented pipeline. Each class owns a single, well-defined responsibility:

```
  main.cpp
     │
     ▼
  ┌──────────────┐
  │  functions   │  mainMenu(), startGame(), setPlayers(), displayRules()
  │  functions.cpp│  Top-level game flow and user interaction loop
  └──────┬───────┘
         │
         ▼
  ┌──────────────────┐
  │  Game            │  Runtime state machine — turn order, direction,
  │  Game.cpp        │  top card, discard pile, player references
  └──────┬───────────┘
         │
         ├──────────────────────────┬──────────────────────────┐
         ▼                          ▼                          ▼
  ┌─────────────────┐   ┌──────────────────────┐   ┌──────────────────┐
  │  Player         │   │  Deck                │   │  Card Hierarchy  │
  │  Player.cpp     │   │  Deck.cpp            │   │  Card.cpp        │
  │                 │   │                      │   │                  │
  │  Hand management│   │  108-card standard   │   │  Base Card +     │
  │  card play,     │   │  UNO deck; random    │   │  6 derived types;│
  │  draw, display  │   │  draw, card removal  │   │  polymorphic     │
  └─────────────────┘   └──────────────────────┘   │  effects &       │
                                                    │  playability     │
                                                    └──────────────────┘
```

---

## ✨ Features

### 🃏 Full Card Set — 108 Cards

The deck is constructed exactly to the UNO standard on every new game:

| Card Type | Count | Effect |
|---|---|---|
| Number (0–9, 4 colors) | 76 | Match by color or number |
| Skip (4 colors × 2) | 8 | Next player loses their turn |
| Reverse (4 colors × 2) | 8 | Reverses the direction of play |
| Draw Two (4 colors × 2) | 8 | Next player draws 2 cards and is skipped |
| Wild | 4 | Current player chooses the new active color |
| Wild Draw Four | 4 | Choose color; next player draws 4 and is skipped |

### 🎮 Gameplay Mechanics
- **2–10 player** hot-seat multiplayer on a single terminal
- **Automatic turn management** — direction, skip, and advance logic all handled by the `Game` engine
- **Forced draw** — if a player has no playable card, one is drawn automatically; if still unplayable, the turn is passed
- **Color selection** — prompted interactively whenever a Wild or Wild Draw Four is played
- **Win detection** — the game ends immediately when any player empties their hand

### 🖥️ Terminal Card Display

Every card renders as a bordered ASCII art block:

```
+-------+
| RED   |
| DRAW  |
| +2    |
+-------+

+-------+
| WILD  |
| WILD  |
|       |
+-------+

+-------+
| BLUE  |
| 7     |
|       |
+-------+
```

### 📋 Built-in Rules Reference
A full in-game rules display is accessible from the main menu at any time, covering all card types, gameplay flow, and win conditions.

---

## 🏗️ Project Structure

```text
UNO/
├── include/
│   ├── Card.h          # Card base class + all 6 derived card type declarations
│   ├── Deck.h          # Deck class — 108-card construction and draw logic
│   ├── Game.h          # Game state engine — turn, direction, top card, discard pile
│   ├── Player.h        # Player class — hand management, card play, draw
│   └── functions.h     # Top-level game flow function declarations
│
├── src/
│   ├── Card.cpp        # Card base + NumberCard, SkipCard, ReverseCard,
│   │                   # DrawTwoCard, WildCard, WildDrawFourCard implementations
│   ├── Deck.cpp        # Full deck construction and random draw implementation
│   ├── Game.cpp        # Turn management, direction, color choice, discard pile
│   ├── Player.cpp      # Hand operations, playability check, card rendering
│   ├── functions.cpp   # mainMenu, startGame, setPlayers, displayRules
│   └── main.cpp        # Entry point — seeds RNG, launches main menu
│
└── README.md           # Project documentation
```

---

## 🚀 Getting Started

### Prerequisites
A C++17-compatible compiler: `g++` (GCC 8+) or `clang++`.

### Compilation

```bash
g++ -std=c++17 -Iinclude src/*.cpp -o uno
```

### Running the Game

```bash
# Unix / macOS / Linux
./uno

# Windows
.\uno
```

### Gameplay Walkthrough

```
=============================
           UNO GAME
=============================
1. Start New Game
2. Game Rules
3. Exit
-------------------------------
Enter your choice: 1

Enter the Number of Players: 3
Enter the name of Player 1: Alice
Enter the name of Player 2: Bob
Enter the name of Player 3: Carol

Displaying Top Card:
+-------+
| GREEN |
| 5     |
|       |
+-------+

Player 1 Hand:
+-------+    +-------+    +-------+
| GREEN |    | RED   |    | WILD  |
| 7     |    | SKIP  |    | WILD  |
|       |    |       |    |       |
+-------+    +-------+    +-------+
...

Player Alice
Enter your Card Number: 1
```

---

## 🧠 Design Decisions

**Why a polymorphic card hierarchy?**
Each card type has fundamentally different playability rules and game effects. Polymorphism through `isPlayable()` and `applyEffect()` virtual overrides keeps each card's behavior fully self-contained — adding a new card type requires no changes to the game loop.

**Why does `applyEffect()` take a `Game&` reference?**
Cards need to trigger actions on the game state (draw cards, skip players, reverse direction, choose a color). Passing the `Game` by reference gives each card full access to the engine interface without tight coupling or global state.

**Why random-index removal instead of a shuffle?**
Removing a card at a random index from the deck vector directly simulates drawing from a shuffled pile without requiring a separate shuffle pass — and ensures that every draw throughout the game remains unpredictable.

**Why a discard pile separate from the top card?**
The `topCard` pointer owns the currently active card for playability checks and color reads. When a new card is played, the old top card is moved to the discard pile vector, keeping ownership clear and ensuring all cards are freed exactly once at game end.

---

## ⚠️ Current Limitations

- No UNO call mechanic (penalty for failing to declare UNO on last card)
- No AI / computer-controlled players — hot-seat human players only
- No score tracking or multi-round sessions
- Deck is not reshuffled from the discard pile when exhausted
- No save / load functionality

---

## 🗺️ Roadmap

- **UNO Call System** — detect single-card hands and apply a 2-card penalty for missed declarations
- **AI Players** — rule-based computer opponents with configurable difficulty
- **Score Tracking** — point accumulation across multiple rounds using standard UNO scoring
- **Discard Pile Reshuffle** — automatically reshuffle the discard pile into the draw deck when it runs out
- **Color-coded Terminal Output** — ANSI escape codes to render each card in its actual color

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](LICENSE) file for details.