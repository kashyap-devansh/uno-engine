````markdown
<div align="center">
  <h1>Project - UNO</h1>
  <p><b>A custom-built, object-oriented C++ engine simulating the classic UNO card game ruleset.</b></p>
  
  [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
  [![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
  [![Platform](https://img.shields.io/badge/platform-win%20%7C%20mac%20%7C%20linux-lightgrey.svg)]()
</div>

<br />

Project - UNO is a lightweight, strictly typed card game simulation engine written entirely in C++. It was designed to practically explore Object-Oriented Programming (OOP) architectures, polymorphic execution, state management, and event-driven rule processing within a terminal environment.

Unlike simple procedural scripts, this project implements a highly formalized component architecture. It isolates game state, rule enforcement, and entity data into discrete, extensible classes, serving as an exploration of game loop mechanics and memory-safe container management in C++.

---

## Quick Example

The engine handles turn progression, effects, and validation natively. Here is a conceptual visualization of the local execution flow:

```cpp
// Initialize Deck and Game state
Deck mainDeck;
std::vector<Player> players(2);
std::vector<Player*> playerPtrs = { &players[0], &players[1] };
Game unoEngine(2, &mainDeck, playerPtrs);

// Engine dictates turn logic and polymorphic card effects
unoEngine.displayTopCard();
int turn = unoEngine.getCurrentPlayer();

// If player plays a Reverse Card:
Card* playedCard = players[turn].getCard(0);
if (playedCard->isPlayable(unoEngine.getTopCard())) {
    players[turn].playCard(0, unoEngine); // Polymorphic dispatch (reverses direction)
    unoEngine.advanceTurn();
}
```

---

## Architecture & Execution Pipeline

The UNO engine utilizes a strict Object-Oriented pipeline emphasizing encapsulated state modification and polymorphic rule resolution.

### 1. Polymorphic Rule Execution (The Card System)
Instead of relying on massive, brittle `switch` statements to determine what a card does, the engine utilizes inheritance. The base class `Card` defines a virtual `applyEffect(Game&)` and `isPlayable()`. Derived classes (`SkipCard`, `ReverseCard`, `WildDrawFourCard`) override these methods to directly manipulate the `Game` state upon play, ensuring O(1) rule resolution and absolute decoupling.

### 2. State & Event Dispatcher (The Game Engine)
The `Game` class acts as the central state machine and dispatcher. It tracks the `currentPlayer`, turn `direction` (forward/backward), and the `topCard`. It safely exposes mutators like `reverseDirection()` and `drawCard()` which action cards hook into during their `applyEffect()` routines.

### 3. Memory & Entity Management
Entities such as the `Deck` and `Player` hands utilize `std::vector` for memory-safe, dynamically resizing contiguous arrays.
- **Deck Allocation:** Instantiates all 108 predefined standard UNO cards natively.
- **Player State:** Encapsulated cleanly; players push and pop pointers to `Card` objects without re-allocating heavy structures during runtime.
- **Ownership Model:** `Deck` owns cards on initialization. Once drawn, ownership transfers to the `Player`. Played cards are tracked in a discard pile owned by `Game`. Each destructor only deletes what it owns — no double-free issues.

---

## Project Structure

```text
Project - UNO/
├── Card.h / Card.cpp           # Base class and Derived Action/Wild cards
├── Deck.h / Deck.cpp           # Card pool and shuffling algorithms
├── Game.h / Game.cpp           # Central state machine and turn dispatcher
├── Player.h / Player.cpp       # Player state, hand management, and actions
├── functions.h / functions.cpp # Helper utilities and generic routines
├── main.cpp                    # Entry point and primary game loop
├── LICENSE                     # MIT License configuration
└── README.md                   # Project documentation
```

---

## Build & Run Instructions

The UNO engine has zero external dependencies, compiling cleanly across major platforms utilizing standard C++ compilers (GCC, Clang, or MSVC).

### GCC Compilation
Compile the engine utilizing standard C++17 flags:

```bash
g++ *.cpp -o uno -Wall -std=c++17
```

### Execution
Invoke the compiled binary to start the simulation environment.

```bash
# Unix / macOS / Linux
./uno

# Windows
uno.exe
```

---

## Game Mechanics Reference

The engine inherently enforces strict standard UNO rules.

### Supported Card Types
| Card Class | Behavior Detail | Inheritance Base |
| :--- | :--- | :--- |
| `NumberCard` | Validates against matching color or number. | `Card` |
| `SkipCard` | Calls `game.skipNextPlayer()`. | `Card` |
| `ReverseCard` | Calls `game.reverseDirection()`. | `Card` |
| `DrawTwoCard` | Forces next player to draw 2; skips turn. | `Card` |
| `WildCard` | Can be played on anything; prompts color change. | `Card` |
| `WildDrawFourCard` | Changes color; forces next player to draw 4. | `Card` |

### Engine Enforcement
- **Validation:** Cards are checked via `isPlayable(topCard)` before a move is accepted.
- **Draw Enforcement:** If a `Player` calls `hasPlayableCard(topCard)` and it returns false, the engine mandates a deck draw.
- **Win Condition:** Determined when `Player::isHandEmpty()` evaluates to true.

---

## Design Decisions

- **Why polymorphic cards instead of Enums?** Utilizing `virtual void applyEffect()` delegates logic to the specific card instance. This prevents the `Game` loop from needing to know *how* a card works, strictly adhering to the Open-Closed Principle (OCP)—adding a new custom card type requires zero changes to the `Game` class.
- **Why pass pointers instead of values?** Card objects are instantiated once in the `Deck`. Moving `Card*` pointers between the `Deck`, `Player` hands, and `topCard` minimizes memory overhead and prevents expensive object slicing or deep copying.
- **Why decouple the Game state from the players?** `Player` only manages hand sizing and indexing (`playCard`). Determining whose turn is next or what color is active strictly belongs to the `Game` dispatcher, ensuring single-responsibility structures.

---

## Current Limitations

The overarching engine operates correctly, but is scoped within intentional limits:
- **No GUI:** Operates strictly via a terminal text-based interface.
- **No Network Stack:** Restricted to local pass-and-play execution; no socket networking currently implemented.
- **No Bot AI:** Requires human input for all players; no Minimax or heuristic-based automated opponents.
- **No UNO Call Mechanic:** The UNO call rule is documented but not yet implemented in the engine.

---

## Roadmap

As a C++ engine architecture exploration, future iterations will target:
- **Heuristic AI Opponents:** Implementing a rudimentary decision tree for offline single-player execution.
- **Networked Multiplayer Protocol:** Utilizing basic raw TCP/UDP sockets to synchronize `Game` states across remote instances.
- **GUI Integration:** Detaching the `main.cpp` terminal loop and binding the engine back-end to a graphical context (e.g., SFML or ImGui).
- **Smart Pointers Implementation:** Refactoring raw `Card*` pointers to `std::shared_ptr` or `std::unique_ptr` for modernized deterministic memory safety.

---

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

<div align="center">
  <i>Developed to practically explore object-oriented design and game loop architectures in C++.</i>
</div>
````