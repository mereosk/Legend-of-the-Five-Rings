# Legend-of-the-Five-Rings

## Overview

This project is a terminal-based game created in C++ called *Legend of the Five Rings*. The game is inspired by the traditional "Legend of the Five Rings" universe, and it involves various mechanics such as player choices, combat, and strategic decision-making. The game is designed to be played through the terminal, offering an immersive experience despite the text-based interface.

The game utilizes multiple C++ features, including object-oriented programming principles, classes, inheritance, polymorphism, and file handling. It allows players to interact with different characters, engage in quests, and navigate through various storylines, all while relying on a set of rules governed by the Five Rings.

## Compilation & Execution
To compile and run this standalone C++ module:
```sh
# Compile all source files
make all

# Alternative manual compilation (if Makefile is missing)
g++ main.cpp Card.cpp Personality.cpp Follower.cpp Item.cpp Holding.cpp DeckBuilder.cpp Player.cpp GameBoard.cpp TypeConverter.cpp GraveYard.cpp -o game

# Run the compiled executable
./game
```
---
## Card's Description
Initially, the `Card`, `GreenCard`, and `BlackCard` classes are defined as abstract since they are never directly instantiated. This takes advantage of the `virtual` keyword in object-oriented programming, allowing the use of:
```cpp
Superclass *name = derivedClass *name;
```
These abstract classes serve as general descriptions of different card categories. For instance, `BlackCard` is a parent class for `Personality` and `Holding`. The required functionalities were implemented along with appropriate accessors for use throughout the program.

The `StrongHold` class is a subclass of `Holding`, using its private variable `initialDefense` and mutators to determine the defense of the `Provinces`.

---
## DeckBuilder
The `DeckBuilder` was modified to fit the program's needs. Instead of a single `DeckBuilder` class, it was split into `GreenDeckBuilder` and `BlackDeckBuilder`, specializing in `FateDeck` and `DynastyDeck` respectively. 

Rather than dynamically creating `Personality` or `Holding` objects (e.g., `new Footsoldier("name");`), enumerations were introduced. These are used in constructors to assign proper values to new objects based on `#define` values from `DeckBuilder.h`.

---
## Lists vs Vectors
The program utilizes both `vectors` and `lists` from the STL. While `lists` are generally preferable due to frequent deletions that would cause memory reallocation in `vectors`, vectors were extensively used due to their advantages like fast search and random access. The general approach was:
- Use `lists` for large data structures.
- Use `vectors` for smaller ones, unless search operations are involved.

---
## Grave Yard
A `GraveYard` class was implemented, even though it was not explicitly required. Many card games have this feature. It contains two pointers to lists of pointers—one for `BlackCard` and another for `GreenCard`. When a card "dies," it is added to the corresponding list.

To mark `Personalities` as dead, the `TypeConverter` utility helps determine if a `BlackCard` is of type `Personality`.

---
## Bonus Functionality
The `Personality` class contains a private list of pointers to `GreenCard` objects, allowing attachment of both `Items` and `Followers`. This is achieved using virtual functions. The `equip()` function manages equipping cards, ensuring they meet required `honor` conditions.

Since the deck has a limit, a variable in `Personality` constructors ensures constraints are respected. The primary logic is implemented in `GreenCard`, as `Items` differ from `Followers` only by the additional `durability` stat.

---
## Player Overview
Each player has two decks: `fateDeck` (from `GreenDeckBuilder`) and `dynastyDeck` (from `BlackDeckBuilder`). When a player is initialized:
1. A `StrongHold` is created, setting the starting gold and honor.
2. Four provinces and an initial hand of three cards are established.
3. A `maxHand` constant is enforced to limit hand size.
4. Various helper functions, such as `discardFateCards()`, manage hand operations.
5. Each player has their own `GraveYard`.

Memory cleanup is ensured in the destructor.

---
## GameBoard
The `GameBoard` randomly determines the number of players (2 to 3) but is designed to handle more. Players enter their names, and game statistics such as gold, honor, and provinces are displayed.

A constant variable defines the number of battle rounds (set to 2). The game phases are implemented as functions within `GameBoard`.

---
## Equip Phase
The equip phase is handled by an infinite loop. A `bool` array tracks whether players can continue equipping. If all players set their flag to `false`, the phase ends.

Conditions checked:
- If a player has no army, no equipping is possible.
- If a `Personality`’s equip list is full.
- If the player lacks funds.

The buying process involves selecting a `Personality` and a `GreenCard`, followed by an algorithm that searches for available funds using `Holding` cards. It first tries single `Holding`, then pairs, then triplets, and as a last resort, sums elements sequentially.

The same logic applies to `update()`.

---
## Battle Phase
The battle phase begins by selecting an opponent. Each player has two rounds to attack an opponent’s province or pass. 

An `action phase` follows, structured similarly to `equip phase`, where each player can perform one action per turn. `attacker` and `defender` variables are used to track the active players. If a player has untapped army units, they can send `Personalities` to battle.

**Combat Mechanics:**
- Attack and defense points are summed.
- A calculation determines the outcome, with four possible results:
  1. Attacker wins, sending defender’s army to the `GraveYard`.
  2. Defender wins, sending attacker’s army to the `GraveYard`.
  3. A draw, where both armies are lost.
  4. No attack occurs.

The battle logic ensures fair engagement based on each player's strategy and available resources.

---
## Conclusion
This project simulates a simplified version of **Legend of the Five Rings** in C++, utilizing object-oriented principles such as inheritance, polymorphism, and encapsulation. It implements strategic elements such as deck-building, equipping units, and battle mechanics, while ensuring optimal memory management through STL containers.

