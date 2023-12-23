#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include "PlayerSimplified.h"
#include "BoardSimplified.h"

// Function to load candies from the Candies.txt file
std::vector<Candy> loadCandies()
{
    std::vector<Candy> candies;
    std::ifstream file("candies.txt");
    std::string line;

    while (std::getline(file, line))
    {
        Candy candy;
        std::string delimiter = "|";
        size_t start = 0;
        size_t pos = 0;

        // Extract candy name
        pos = line.find(delimiter, start);
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << "\n";
            continue;
        }
        candy.name = line.substr(start, pos - start);
        start = pos + delimiter.length();

        // Extract candy description
        pos = line.find(delimiter, start);
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << "\n";
            continue;
        }
        candy.description = line.substr(start, pos - start);
        start = pos + delimiter.length();

        // Extract candy effectType
        pos = line.find(delimiter, start);
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << "\n";
            continue;
        }
        candy.effectType = line.substr(start, pos - start);
        start = pos + delimiter.length();

        // Extract candy effectValue
        pos = line.find(delimiter, start);
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << "\n";
            continue;
        }
        try {
            candy.effectValue = std::stoi(line.substr(start, pos - start));
        } catch (std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << line.substr(start, pos - start) << " cannot be converted to int.\n";
            continue;
        } catch (std::out_of_range& e) {
            std::cerr << "Out of range error: " << line.substr(start, pos - start) << " is too large for int.\n";
            continue;
        }
        start = pos + delimiter.length();

        // Extract candy candyType
        pos = line.find(delimiter, start);
        if (pos == std::string::npos) {
            std::cerr << "Invalid line format: " << line << "\n";
            continue;
        }
        candy.candyType = line.substr(start, pos - start);
        start = pos + delimiter.length();

        // Extract candy price
        try {
            candy.price = std::stoi(line.substr(start));
        } catch (std::invalid_argument& e) {
            std::cerr << "Invalid argument: " << line.substr(start) << " cannot be converted to int.\n";
            continue;
        } catch (std::out_of_range& e) {
            std::cerr << "Out of range error: " << line.substr(start) << " is too large for int.\n";
            continue;
        }

        // Add the candy to the vector
        candies.push_back(candy);
    }

    return candies;
}

// Function to load characters from the Characters.txt file
std::vector<std::vector<std::string>> loadCharacters()
{
    std::vector<std::vector<std::string>> characters;
    std::ifstream file("characters.txt");
    std::string line;

    std::string header;
    std::getline(file, header);

    while (std::getline(file, line))
    {
        std::vector<std::string> character;
        std::istringstream ss(line);
        std::string attribute;
        while (std::getline(ss, attribute, '|'))
        {
            character.push_back(attribute);
        }
        characters.push_back(character);
    }

    file.close();

    return characters;
}

// Function to display the character selection menu and get the selected character
std::string selectCharacter(const std::vector<std::vector<std::string>> &characters, Player &player)
{
    std::cout << "Character Selection Menu:\n";
    for (int i = 0; i < characters.size(); i++)
    {
        std::cout << i + 1 << ". "
        << "Name: " << characters[i][0]
        << ", Stamina: " << characters[i][1]
        << ", Gold: " << characters[i][2]
        << ", Candies: " << characters[i][3] << "\n";
    }

    int choice;
    std::cout << "Enter the number corresponding to your character: ";
    std::cin >> choice;

    // Validate the user's choice
    while (choice < 1 || choice > characters.size())
    {
        std::cout << "Invalid choice. Please enter a number between 1 and " << characters.size() << ": ";
        std::cin >> choice;
    }

    // Assign the chosen character's attributes to the player
    player.setCharacterName(characters[choice - 1][0]);
    player.setStamina(std::stoi(characters[choice - 1][1]));
    player.setGold(std::stoi(characters[choice - 1][2]));

    // Add the chosen character's candies to the player's candy inventory
    std::istringstream candyStream(characters[choice - 1][3]);
    std::string candy;
    while (std::getline(candyStream, candy, ','))
    {
        player.addCandy(candy);
    }

    return characters[choice - 1][0];
}

// Function to display the candy store and allow players to purchase candies
void visitCandyStore(const std::vector<Candy> &candies, Player &currentPlayer)
{
    std::cout << "Welcome to the Candy Store!\n";
    std::cout << "Here are the available candies:\n";
    for (const Candy &candy : candies)
    {
        std::cout << "Name: " << candy.name << "\n";
        std::cout << "Description: " << candy.description << "\n";
        std::cout << "Effect Type: " << candy.effectType << "\n";
        std::cout << "Effect Value: " << candy.effectValue << "\n";
        std::cout << "Candy Type: " << candy.candyType << "\n";
        std::cout << "Price: " << candy.price << "\n";
        std::cout << "------------------------\n";
    }

    // Ask the player which candy they want to buy
    string candy_choice;
    cout << "Enter the name of the candy you want to buy: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline
    std::getline(std::cin, candy_choice);

    // Find the candy in the list
    int candyIndex = -1;
    for (int i = 0; i < candies.size(); ++i)
    {
        if (candies[i].name == candy_choice)
        {
            candyIndex = i;
            break;
        }
    }

    // Check if the candy was found
    if (candyIndex == -1)
    {
        cout << "That candy is not available.\n";
        return;
    }

    // Check if the player has enough gold
    if (currentPlayer.getGold() >= candies[candyIndex].price)
    {
        // Update the player's attributes
        currentPlayer.setGold(currentPlayer.getGold() - candies[candyIndex].price);
        currentPlayer.addCandy(candies[candyIndex].name);
        cout << "You bought a " << candies[candyIndex].name << "!\n";
    }
    else
    {
        cout << "You don't have enough gold to buy this candy.\n";
    }

    std::cout << "Thank you for visiting the Candy Store!\n";
}

// Function to display the main menu and get the player's action choice
int showMainMenu()
{
    int choice;
    std::cout << "Main Menu:\n";
    std::cout << "1. Draw a card\n";
    std::cout << "2. Visit the candy store\n";
    std::cout << "3. Show stats\n";
    std::cout << "4. Quit the game\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;

    // Validate the user's choice
    while (choice < 1 || choice > 4 || std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Invalid choice. Please enter a number between 1 and 4: ";
        std::cin >> choice;
    }

    return choice;
}

// Function to start the game
void startGame()
{
    // Load candies and characters
    std::vector<Candy> candies = loadCandies();
    std::vector<std::vector<std::string>> characters = loadCharacters();
    Board board;

    // Get the number of players and their names
    int numPlayers;
    std::cout << "Enter the number of players: ";
    std::cin >> numPlayers;

    std::vector<Player> players;
    for (int i = 0; i < numPlayers; i++)
    {
        std::string name;
        std::cout << "Enter the name of player " << i + 1 << ": ";
        std::cin >> name;
        Player player;              // Create a new Player object
        player.setPlayerName(name); // Set the player's name
        players.push_back(player);  // Add the Player object to the vector
    }

    // Select characters for each player
    for (Player &player : players)
    {
        std::cout << player.getPlayerName() << ", select your character:\n";
        std::string selectedCharacter = selectCharacter(characters, player);
        player.setCharacterName(selectedCharacter); // Set the character's name
    }

    // Add candy stores to the board
    board.addCandyStores(candies);

    // Game loop
    bool gameOver = false;
    int currentPlayerIndex = 0;
    while (!gameOver)
    {
        Card cardDrawn;
        Player& currentPlayer = players[currentPlayerIndex];
        // Display the main menu and get the player's action choice
        int choice = showMainMenu();

        // Implement the game logic based on the player's choice
        switch (choice)
        {
        case 1:
            // Draw a card
            // Move the player to the next tile
            cardDrawn = currentPlayer.drawCard();
            cout << "You drew a " << cardDrawn.color << " " << cardDrawn.card_type << " card.\n";
            board.movePlayer(currentPlayer, cardDrawn);
            // move to the next player for the next turn
            currentPlayerIndex = (currentPlayerIndex + 1) % players.size();
            break;
        case 2:
            // Visit the candy store
            visitCandyStore(candies, currentPlayer);
            break;
        case 3:
            // Show player stats
            currentPlayer.showStats();
            break;
        case 4:
            // Quit the game
            gameOver = true;
            break;
        }
    }

    std::cout << "Game over. Thanks for playing!\n";
}

int main()
{
    Board board;
    board.displayBoard();
    startGame();

    return 0;
}