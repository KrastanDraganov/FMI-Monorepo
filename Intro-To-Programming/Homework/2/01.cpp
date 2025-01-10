#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int PLAYERS = 2;

const int ALL_CARD_RANKS = 13;
const int ALL_CARD_SUITS = 4;

const int DECK_SIZE = ALL_CARD_RANKS * ALL_CARD_SUITS;

const int CARDS_COUNT_IN_WAR = 3;

const char *cardRankToTypeMap[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

const int MAX_COMMAND_LENGTH = 1024;

const char START_GAME_COMMAND[] = "start";
const char PLAY_GAME_COMMAND[] = "play";
const char QUIT_GAME_COMMAND[] = "quit";

int myStrcmp(const char *s1, const char *s2)
{
    if (!s1 || !s2)
    {
        return 0;
    }

    while (*s1 && *s2 && (*s1 == *s2))
    {
        ++s1;
        ++s2;
    }

    return (*s1 - *s2);
}

bool isMyQueueEmpty(int queueFront, int queueRear)
{
    return queueFront == queueRear;
}

int myQueueSize(int queueFront, int queueRear, int maxQueueSize)
{
    return (queueRear - queueFront + maxQueueSize) % maxQueueSize;
}

void myQueuePush(int myQueue[], int newElement, int &queueRear, int maxQueueSize)
{
    myQueue[queueRear] = newElement;
    queueRear = (queueRear + 1) % maxQueueSize;
}

int myQueuePop(const int myQueue[], int &queueFront, int maxQueueSize)
{
    int frontElement = myQueue[queueFront];

    queueFront = (queueFront + 1) % maxQueueSize;

    return frontElement;
}

void printGameCommands(bool isStartCommandEnabled)
{
    cout << "Available commands:\n\n";

    if (isStartCommandEnabled)
    {
        cout << START_GAME_COMMAND << " - starts the game, if it is not already started\n";
    }

    cout << PLAY_GAME_COMMAND << " - the next turn in the game is made\n";
    cout << QUIT_GAME_COMMAND << " - game ends prematurely\n\n";
}

void insertRankInAllSuits(int deck[], int currentRank, int &currentPositionInDeck)
{
    for (int i = 0; i < ALL_CARD_SUITS; ++i)
    {
        deck[currentPositionInDeck] = currentRank;
        ++currentPositionInDeck;
    }
}

void initializeDeck(int deck[])
{
    int currentPositionInDeck = 0;

    for (int rank = 0; rank < ALL_CARD_RANKS; ++rank)
    {
        insertRankInAllSuits(deck, rank, currentPositionInDeck);
    }
}

void shiftArray(int deck[], int targetPosition)
{
    int currentRank = deck[targetPosition];

    for (int i = targetPosition; i < DECK_SIZE - 1; ++i)
    {
        deck[i] = deck[i + 1];
    }

    deck[DECK_SIZE - 1] = currentRank;
}

void shuffleDeck(int deck[])
{
    for (int i = 0; i < DECK_SIZE; ++i)
    {
        int leftCards = DECK_SIZE - i;

        int targetPosition = rand() % leftCards;

        shiftArray(deck, targetPosition);
    }
}

void dealCardsToPlayers(int deckWithAllCards[], int playersDecks[][DECK_SIZE], int queueRear[])
{
    for (int i = 0; i < DECK_SIZE; ++i)
    {
        int currentPlayer = (i % 2);
        int currentCard = deckWithAllCards[i];

        myQueuePush(playersDecks[currentPlayer], currentCard,
                    queueRear[currentPlayer], DECK_SIZE);
    }
}

void printPlayersDecksSizes(const int queueFront[], const int queueRear[])
{
    for (int i = 0; i < PLAYERS; ++i)
    {
        cout << "P" << i + 1 << ": Cards: " << myQueueSize(queueFront[i], queueRear[i], DECK_SIZE) << "   ";
    }

    cout << endl;
}

void printPlayersCurrentCards(int player1TopCard, int player2TopCard)
{
    cout << "P1: " << cardRankToTypeMap[player1TopCard] << "   P2: " << cardRankToTypeMap[player2TopCard] << endl;
}

bool hasEnoughCardsForWar(int deck[], int &queueFront, int queueRear)
{
    if (myQueueSize(queueFront, queueRear, DECK_SIZE) >= CARDS_COUNT_IN_WAR)
    {
        return true;
    }

    while (!isMyQueueEmpty(queueFront, queueRear))
    {
        myQueuePop(deck, queueFront, DECK_SIZE);
    }

    return false;
}

void handleWar(int playersDecks[][DECK_SIZE], int queueFront[], int queueRear[], int warReasonCard)
{
    cout << "\nThere is a war! Both players draw each 3 more cards!\n";

    for (int player = 0; player < PLAYERS; ++player)
    {
        if (!hasEnoughCardsForWar(playersDecks[player], queueFront[player], queueRear[player]))
        {
            cout << "\nP" << player + 1 << " doesn't have enought cards for war, so all card goes to the other player!\n\n";

            return;
        }
    }

    cout << "Drawns cards are:\n\n";

    int playersDrawnCards[CARDS_COUNT_IN_WAR][PLAYERS];

    for (int i = 0; i < CARDS_COUNT_IN_WAR; ++i)
    {
        playersDrawnCards[i][0] = myQueuePop(playersDecks[0], queueFront[0], DECK_SIZE);
        playersDrawnCards[i][1] = myQueuePop(playersDecks[1], queueFront[1], DECK_SIZE);

        printPlayersCurrentCards(playersDrawnCards[i][0], playersDrawnCards[i][1]);
    }

    int warWinner = -1;

    for (int i = CARDS_COUNT_IN_WAR - 1; i >= 0; --i)
    {
        if (playersDrawnCards[i][0] > playersDrawnCards[i][1])
        {
            warWinner = 0;
            break;
        }
        else if (playersDrawnCards[i][0] < playersDrawnCards[i][1])
        {
            warWinner = 1;
            break;
        }
    }

    if (warWinner == -1)
    {
        cout << "\nEven all the cards in the war are the same, so the winner will be decided after one game of rock, paper, scissors :)\n\n";

        warWinner = rand() % 2;
    }

    cout << "\nP" << warWinner + 1 << " wins the war!\n\n";

    myQueuePush(playersDecks[warWinner], warReasonCard, queueRear[warWinner], DECK_SIZE);
    myQueuePush(playersDecks[warWinner], warReasonCard, queueRear[warWinner], DECK_SIZE);

    for (int i = 0; i < CARDS_COUNT_IN_WAR; ++i)
    {
        myQueuePush(playersDecks[warWinner], playersDrawnCards[i][0], queueRear[warWinner], DECK_SIZE);
        myQueuePush(playersDecks[warWinner], playersDrawnCards[i][1], queueRear[warWinner], DECK_SIZE);
    }
}

void playGame(int playersDecks[][DECK_SIZE], int queueFront[],
              int queueRear[], bool &isGameStarted, bool &isGameFinished)
{
    if (!isGameStarted)
    {
        cout << "The game has not started yet! Please use command \"start\"!\n\n";

        return;
    }

    printPlayersDecksSizes(queueFront, queueRear);

    int player1TopCard = myQueuePop(playersDecks[0], queueFront[0], DECK_SIZE);
    int player2TopCard = myQueuePop(playersDecks[1], queueFront[1], DECK_SIZE);

    printPlayersCurrentCards(player1TopCard, player2TopCard);

    if (player1TopCard > player2TopCard)
    {
        myQueuePush(playersDecks[0], player1TopCard, queueRear[0], DECK_SIZE);
        myQueuePush(playersDecks[0], player2TopCard, queueRear[0], DECK_SIZE);
    }
    else if (player1TopCard < player2TopCard)
    {
        myQueuePush(playersDecks[1], player1TopCard, queueRear[1], DECK_SIZE);
        myQueuePush(playersDecks[1], player2TopCard, queueRear[1], DECK_SIZE);
    }
    else
    {
        handleWar(playersDecks, queueFront, queueRear, player1TopCard);
    }

    if (isMyQueueEmpty(queueFront[0], queueRear[0]))
    {
        cout << "P2 wins the game!\n";

        isGameFinished = true;
    }
    else if (isMyQueueEmpty(queueFront[1], queueRear[1]))
    {
        cout << "P1 wins the game!\n";

        isGameFinished = true;
    }
    else
    {
        printPlayersDecksSizes(queueFront, queueRear);
    }

    cout << endl;
}

void startGame(int deckWithAllCards[], int playersDecks[][DECK_SIZE], int queueFront[],
               int queueRear[], bool &isGameStarted, bool &isGameFinished)
{
    if (isGameStarted)
    {
        cout << "The game is already started!\n\n";
        printGameCommands(false);

        return;
    }

    shuffleDeck(deckWithAllCards);

    dealCardsToPlayers(deckWithAllCards, playersDecks, queueRear);

    isGameStarted = true;

    playGame(playersDecks, queueFront, queueRear, isGameStarted, isGameFinished);
}

void quitGame(bool &isGameFinished)
{
    cout << "Game is ended prematurely, nobody wins!\n";
    isGameFinished = true;
}

int main()
{
    srand(time(nullptr));

    cout << "You are playing cards game \"War\"!\n\n";
    printGameCommands(true);

    int deckWillAllCards[DECK_SIZE];
    initializeDeck(deckWillAllCards);

    int playersDecks[PLAYERS][DECK_SIZE] = {0};
    int queueFront[PLAYERS] = {0}, queueRear[PLAYERS] = {0};

    bool isGameStarted = false;
    bool isGameFinished = false;

    char command[MAX_COMMAND_LENGTH + 1];

    do
    {
        cout << "Enter your next command: ";
        cin >> command;

        system("clear");

        if (myStrcmp(command, START_GAME_COMMAND) == 0)
        {
            startGame(deckWillAllCards, playersDecks, queueFront,
                      queueRear, isGameStarted, isGameFinished);
        }
        else if (myStrcmp(command, PLAY_GAME_COMMAND) == 0)
        {
            playGame(playersDecks, queueFront, queueRear,
                     isGameStarted, isGameFinished);
        }
        else if (myStrcmp(command, QUIT_GAME_COMMAND) == 0)
        {
            quitGame(isGameFinished);
        }
        else
        {
            printGameCommands(!isGameStarted);
        }

    } while (!isGameFinished);

    return 0;
}