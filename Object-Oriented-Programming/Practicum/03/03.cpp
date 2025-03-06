#include <iostream>
#include <cstring>

using namespace std;

const double EPSILON = 0.0001;

const int MAX_TITLE_LENGTH = 64;
const int MAX_GAMES_COUNT = 32;

class Game
{
    char title[MAX_TITLE_LENGTH + 1];
    double price;
    bool isAvailable;

    bool isValidTitle(const char *title) const
    {
        return (strlen(title) > MAX_TITLE_LENGTH);
    }

    bool isValidPrice(double price) const
    {
        return price < 0;
    }

public:
    Game()
    {
        price = 0.0;
        isAvailable = false;
    }

    Game(const char *title, double price, bool isAvailable)
    {
        setTitle(title);
        setPrice(price);
        setIsAvailable(isAvailable);
    }

    void setTitle(const char *newTitle)
    {
        if (isValidTitle(newTitle))
        {
            cout << "Title should be max " << MAX_TITLE_LENGTH << " characters!\n";
            return;
        }

        strcpy(this->title, newTitle);
    }

    void setPrice(int newPrice)
    {
        if (!isValidPrice(newPrice))
        {
            cout << "Price should be >= 0 lv!\n";

            return;
        }

        this->price = newPrice;
    }

    void setIsAvailable(bool newIsAvailable)
    {
        this->isAvailable = newIsAvailable;
    }

    const char *getTitle() const
    {
        return title;
    }

    double getPrice() const
    {
        return price;
    }

    bool isAvailable() const
    {
        return isAvailable;
    }

    bool isFree() const
    {
        return price < EPSILON;
    }

    void print() const
    {
        cout << "Game " << title << " costs " << price << "lv and " << (isAvailable ? "is" : "is not") << "available!\n";
    }
};

class GamePlatform
{
    Game games[MAX_GAMES_COUNT];

    int gamesCount;
    int firstAvailableGameSlot;

public:
    GamePlatform(int gamesCount)
    {
        this->gamesCount = gamesCount;
    }

    bool addGame(const Game &newGame)
    {
        if (firstAvailableGameSlot == gamesCount)
        {
            return false;
        }

        games[firstAvailableGameSlot] = newGame;

        return true;
    }

    void printGame(int index) const
    {
        if (index >= firstAvailableGameSlot)
        {
            cout << "There is no such game!\n";
            return;
        }

        games[index].print();
    }

    void printAllGames() const
    {
        for (int i = 0; i < firstAvailableGameSlot; ++i)
        {
            games[i].print();
        }
    }

    void printMostExpensiveGame() const
    {
        if (firstAvailableGameSlot == 0)
        {
            cout << "There are no games!\n";
            return;
        }

        int maxPriceGameIndex = 0;

        for (int i = 1; i < firstAvailableGameSlot; ++i)
        {
            if (games[i].getPrice() > games[maxPriceGameIndex].getPrice())
            {
                maxPriceGameIndex = i;
            }
        }

        games[maxPriceGameIndex].print();
    }

    void printCheapestGame() const
    {
        if (firstAvailableGameSlot == 0)
        {
            cout << "There are no games!\n";
            return;
        }

        int minPriceGameIndex = 0;

        for (int i = 1; i < firstAvailableGameSlot; ++i)
        {
            if (games[i].getPrice() < games[minPriceGameIndex].getPrice())
            {
                minPriceGameIndex = i;
            }
        }

        games[minPriceGameIndex].print();
    }

    void printAllFreeGames() const
    {
        bool foundFreeGame = false;

        for (int i = 0; i < firstAvailableGameSlot; ++i)
        {
            if (games[i].isFree())
            {
                games[i].print();
                foundFreeGame = true;
            }
        }

        if (!foundFreeGame)
        {
            cout << "There are no free games!\n";
        }
    }

    void removeGame(int toBeRemovedIndex)
    {
        if (toBeRemovedIndex >= firstAvailableGameSlot)
        {
            cout << "There is no such game!\n";
            return;
        }

        for (int i = toBeRemovedIndex; i < firstAvailableGameSlot; ++i)
        {
            games[i] = games[i + 1];
        }

        --firstAvailableGameSlot;
    }
};