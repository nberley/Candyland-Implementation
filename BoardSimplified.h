#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <string>
#include <iostream>
#include "PlayerSimplified.h" 
#include "Card.h"

#define RED "\033[;41m"               /* Red */
#define GREEN "\033[;42m"             /* Green */
#define BLUE "\033[;44m"              /* Blue */
#define MAGENTA "\033[;45m"           /* Magenta */
#define CYAN "\033[;46m"              /* Cyan */
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0)*/
#define RESET "\033[0m"

using namespace std;

// Struct to store information about a candy
struct Candy
{
    std::string name;
    std::string description;
    std::string effectType;
    int effectValue;
    std::string candyType;
    int price;
};

struct Tile
{
    string color;
    string tile_type;
};

struct CandyStore
{
    std::vector<Candy> candies; // All candies in the game
    int position;
};

class Board {

private:
    const static int _BOARD_SIZE = 83;
    Tile _tiles[_BOARD_SIZE];
    const static int _MAX_CANDY_STORE = 3;
    int _candy_store_position[_MAX_CANDY_STORE];
    int _candy_store_count;
    int _player_position;

public:
    Tile tiles[_BOARD_SIZE];

    Board()
    {
        resetBoard();
    }

    void resetBoard()
    {
        const int COLOR_COUNT = 3;
        const string COLORS[COLOR_COUNT] = {MAGENTA, GREEN, BLUE};
        Tile new_tile;
        string current_color;
        for (int i = 0; i < _BOARD_SIZE - 1; i++)
        {
            current_color = COLORS[i % COLOR_COUNT];
            new_tile = {current_color, "regular tile"};
            _tiles[i] = new_tile;
        }
        new_tile = {ORANGE, "regular tile"};
        _tiles[_BOARD_SIZE - 1] = new_tile;

        _candy_store_count = 0;
        for (int i = 0; i < _MAX_CANDY_STORE; i++)
        {
            _candy_store_position[i] = -1;
        }

        _player_position = 0;
    }

    void displayTile(int position)
    {
        if (position < 0 || position >= _BOARD_SIZE)
        {
            return;
        }
        Tile target = _tiles[position];
        cout << target.color << " ";
        if (position == _player_position)
        {
            cout << "X";
        }
        else
        {
            cout << " ";
        }
        cout << " " << RESET;
    }

    void displayBoard()
    {
        // First horizontal segment
        for (int i = 0; i <= 23; i++)
        {
            displayTile(i);
        }
        cout << endl;
        // First vertical segment
        for (int i = 24; i <= 28; i++)
        {
            for (int j = 0; j < 23; j++)
            {
                cout << "   ";
            }
            displayTile(i);
            cout << endl;
        }
        // Second horizontal segment
        for (int i = 52; i > 28; i--)
        {
            displayTile(i);
        }
        cout << endl;
        // Second vertical segment
        for (int i = 53; i <= 57; i++)
        {
            displayTile(i);
            for (int j = 0; j < 23; j++)
            {
                cout << "   ";
            }
            cout << endl;
        }
        // Third horizontal segment
        for (int i = 58; i < _BOARD_SIZE; i++)
        {
            displayTile(i);
        }
        cout << ORANGE << "Castle" << RESET << endl;
    }

    int getBoardSize() const
    {
        return _BOARD_SIZE;
    }

    string getTileColor(int index)
    {
        return _tiles[index].color;
    }

    // Getter for _player_position
    int getPlayerPosition() const
    {
        return _player_position;
    }

    // Setter for _player_position
    void setPlayerPosition(int position)
    {
        _player_position = position;
    }

    void addCandyStores(std::vector<Candy> &candies)
    {
        vector<int> magentaPositions, greenPositions, bluePositions;
        // Create a vector to hold all candy stores
        std::vector<CandyStore> candyStores;

        // Create four candy stores, each with three candies
        for (int i = 0; i < 4; i++)
        {
            CandyStore store;

            // Add three candies to the store
            for (int j = 0; j < 3; j++)
            {
                store.candies.push_back(candies[rand() % candies.size()]);
            }

            // Set the position of the candy store
            store.position = i; // replace i with the actual position

            // Add the store to the candyStores vector
            candyStores.push_back(store);
        }

        // Set the positions of the candy stores
        candyStores.at(0).position = -1;
        candyStores.at(1).position = rand() % getBoardSize();
        candyStores.at(2).position = rand() % getBoardSize();
        candyStores.at(3).position = rand() % getBoardSize();
    }

    void movePlayer(Player &currentPlayer, const Card &card)
    {
        int targetMatches = (card.card_type == "Double") ? 2 : 1;
        int matchingTilesFound = 0;

        for (int i = currentPlayer.getPosition() + 1; i < _BOARD_SIZE; ++i)
        {
            if (_tiles[i].color == card.color)
            {
                matchingTilesFound++;
                if (matchingTilesFound == targetMatches)
                {
                    currentPlayer.setPosition(i);
                    _player_position = i;
                    currentPlayer.setStamina(currentPlayer.getStamina() - 1);
                    break;
                }
            }
        }

        displayBoard();
    }
};

#endif