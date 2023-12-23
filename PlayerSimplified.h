#ifndef PLAYERSIMPLIFIED_H
#define PLAYERSIMPLIFIED_H

#include <vector>
#include <string>
#include "Card.h"

#define RED "\033[;41m"               /* Red */
#define GREEN "\033[;42m"             /* Green */
#define BLUE "\033[;44m"              /* Blue */
#define MAGENTA "\033[;45m"           /* Magenta */
#define CYAN "\033[;46m"              /* Cyan */
#define ORANGE "\033[48;2;230;115;0m" /* Orange (230,115,0)*/
#define RESET "\033[0m"


class Board;

class Player {
private:
    std::string playerName;
    std::string characterName;
    int stamina;
    int gold;
    std::vector<std::string> candies;
    int position;
    //const int _MAX_CANDY_AMOUNT = 9;

public:
    Player() : stamina(0), gold(0), position(0) {}

    // Getter and setter for playerName
    std::string getPlayerName() const { return playerName; }
    void setPlayerName(const std::string& name) { playerName = name; }

    // Getter and setter for characterName
    std::string getCharacterName() const { return characterName; }
    void setCharacterName(const std::string& name) { characterName = name; }

    // Getter and setter for stamina
    int getStamina() const { return stamina; }
    void setStamina(int stam) { stamina = stam; }

    // Getter and setter for gold
    int getGold() const { return gold; }
    void setGold(int g) { gold = g; }

    // Getter and setter for candies
    std::vector<std::string> getCandies() const { return candies; }
    void addCandy(const std::string& candy) { candies.push_back(candy); }

    // Getter and setter for position
    int getPosition() const { return position; }
    void setPosition(int pos) { position = pos; }

    void showStats() const
    {
        std::cout << "Player Name: " << getPlayerName() << std::endl;
        std::cout << "Character Name: " << getCharacterName() << std::endl;
        std::cout << "Gold: " << getGold() << std::endl;
        std::cout << "Stamina: " << getStamina() << std::endl;
        std::cout << "Candies: ";
        
        std::vector<std::string> candies = this->getCandies();
        for (int i = 0; i < candies.size(); i++) {
            std::cout << candies[i];
            if (i != candies.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }

    Card drawCard()
    {
        Card card;
        srand(time(0));
        int chosen_card = 1 + (rand() % 100);
        if (chosen_card >= 1 && chosen_card <= 25)
        {
            card.color = MAGENTA;
            card.card_type = "Single";
        }
        else if (chosen_card >= 26 && chosen_card <= 50)
        {
            card.color = BLUE;
            card.card_type = "Single";
        }
        else if (chosen_card >= 51 && chosen_card <= 75)
        {
            card.color = GREEN;
            card.card_type = "Single";
        }
        else if (chosen_card >= 76 && chosen_card <= 90)
        {
            card.color = MAGENTA;
            card.card_type = "Double";
        }
        else if (chosen_card >= 91 && chosen_card <= 95)
        {
            card.color = BLUE;
            card.card_type = "Double";
        }
        else if (chosen_card >= 96 && chosen_card <= 100)
        {
            card.color = GREEN;
            card.card_type = "Double";
        }
        return card;
    }
};

#endif