<!-- PROJECT LOGO -->
<br />
<p align="center">
  <h2 align="center">Urr</h3>

  <p align="center">
    Artificial intelligence to play the Royal Game of Ur
    <br />
</p>



<!-- TABLE OF CONTENTS -->
<details open="open">
  <summary><h2 style="display: inline-block">Table of Contents</h2></summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
    </li>
    <li>
      <a href="#about-the-project">Rules</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#usage">Usage</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgements">Acknowledgements</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

<img src="./assets/image1.jpg" width="800" height="450"/>

This project implements artificial intelligence that uses a negamax algorithm to play the <a html="https://en.wikipedia.org/wiki/Royal_Game_of_Ur">Royal Game of Ur</a>. Because of the random element of the game, the algorithm has to calculate a weighted average score for each move and roll instead of travering the game tree directly. In addition, move reordering and alpha-beta pruning are used to speed up the algorithm. The project also contains a small CLI app to test the AI player against other types of players.



## Rules

<img src="./assets/image2.jpg" width="750" height="400"/>

Ur is a turn-based race game played between two players. Each players starts with seven pieces, the objective being to get all seven pieces to the end of the above board before their opponent.

During each turn, a player rolls four binary dice giving a roll between 0 and 4. They may advance one of their pieces forward or move a piece onto the board by the value of the roll. They may not move a piece if its destination is blocked by another piece belonging to the same player. Also, the player may move a piece off the other end of the board, making it finished (the piece cannot be moved if the roll value is greater than the exact amount needed to finish). If a player has no moves, their turn is skipped. Otherwise, the player must make a move.

The first four and last two tiles shown above are safe zones for either player's pieces. However, the middle eight tiles are part of a competition zone shared by both players. In this zone, a player can capture another player's pieces if they land on the same tile, sending it back off the board.

There are also five rosette tiles (marked as flowers on the above board). If a player lands on one of these tiles, they get to move again, skipping their opponent's turn. The rosette tile in the competition zone has the special property that pieces on it are invulnerable and cannot be captured by the opponent.

In order to better represent this board programmatically, it has been modified into the functionally equivalent board below. The first four tiles and last two tiles represent the safe zone, and the rest is the competition zone.

<img src="./assets/image3.PNG" width="600" height="200"/>

<!-- GETTING STARTED -->
## Getting Started

To get a local copy up and running follow these simple steps.

### Prerequisites

You must have CMake 3.16 or higher installed to build this project. You must also have Doxygen and required packages to build the documentation as shown below.

### Installation

1. Clone the repo and move into it
   ```sh
   git clone https://github.com/BattleMage0231/Urr.git
   cd Urr
   ```
1. To build the executable to Urr/bin
   ```sh
   cmake . && make
   ```
3. To build the documentation
   ```sh
   cmake . docs && doxygen Doxyfile.out
   ```


<!-- USAGE EXAMPLES -->
## Usage

Simulate one game between two AI players:
```sh
urr -p AI -p AI
```

Simulate ten games between an AI player and a random player, where the AI player is always white:
```sh
urr -p AI -p RANDOM -g 10
```

Simulate a game between a human player and an AI player, where the colors are random:
```sh
urr -p HUMAN -p AI -r
```

See the full list of command line arguments:
```sh
urr -h
```



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE` for more information.



<!-- CONTACT -->
## Contact

Leyang Zou - leyang.zou@student.tdsb.on.ca

Project Link: [https://github.com/BattleMage0231/Urr](https://github.com/BattleMage0231/Urr)



<!-- ACKNOWLEDGEMENTS -->
## Acknowledgements

* [GitHub README template](https://github.com/othneildrew/Best-README-Template)
* [The Royal Game of Ur with expectiminimax AI](https://github.com/kirklange/rgu)
* [Tom Scott vs Irving Finkel: The Royal Game of Ur](https://www.youtube.com/watch?v=WZskjLq040I)

