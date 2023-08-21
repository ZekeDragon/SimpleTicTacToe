#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <numeric>

class TicTacToeBoard
{
public:
    constexpr static size_t WIDTH = 3;
    constexpr static size_t HEIGHT = WIDTH;
    constexpr static size_t AREA = WIDTH * HEIGHT;

    bool catsGame()
    {
        return !hasWinner() && std::none_of(board.begin(), board.end(), [](char c)
                                            {
                                                return std::isdigit(c);
                                            });
    }

    bool gameOver()
    {
        return hasWinner() || catsGame();
    }

    bool hasWinner()
    {
        return winner;
    }

    bool placeInputOnBoard(int input, char player)
    {
        if (input > 0 && input <= AREA)
        {
            if (std::isdigit(board[--input]))
            {
                board[input] = player;
                checkWinner(player);
                return true;
            }
        }

        return false;
    }

    std::string displayBoard()
    {
        std::string retStr;

        for (size_t pos = 0; pos < AREA; ++pos)
        {
            retStr += board[pos];
            retStr += (pos % WIDTH) < 2 ? '|' : '\n';
            if (pos % WIDTH == 2 && pos / HEIGHT < 2)
            {
                retStr += "-----\n";
            }
        }

        return retStr;
    }

private:
    // I use digits instead of '!' for filler locations to make it clear and easy for players to know which number
    // positions correlate with a player's possible choices.
    std::array<char, AREA> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    bool winner = false;

    constexpr static std::array<std::array<int, WIDTH>, 8> winningOpts{{
        {{ 0, 1, 2 }}, {{ 3, 4, 5 }}, {{ 6, 7, 8 }}, {{ 0, 3, 6 }},
        {{ 1, 4, 7 }}, {{ 2, 5, 8 }}, {{ 0, 4, 8 }}, {{ 2, 4, 6 }}
    }};

    void checkWinner(char player)
    {
        auto testPred = [&](int loc)
        {
            return board[loc] == player;
        };

        auto it = std::find_if(winningOpts.begin(), winningOpts.end(), [&](auto &arr)
                               {
                                   return std::all_of(arr.begin(), arr.end(), testPred);
                               });

        if (it != winningOpts.end())
        {
            winner = true;

            for (int pos : *it)
            {
                board[pos] = std::toupper(board[pos]);
            }
        }
    }
};

constexpr char playerNum(char player)
{
    return player == 'x' ? '1' : '2';
}

int getInput(char player)
{
    int input;
    std::cout << "Player " << playerNum(player) << " move: ";

    // The right thing to do here would be to sanitize user input, as the user could put in something that is not an
    // integer or could even be the entire text of War & Peace. For this implementation, I am keeping it simple
    // because user input sanitization is an entire subject on its own that would need to be taught and this isn't
    // meant to teach that.
    std::cin >> input;
    return input;
}

int main()
{
    TicTacToeBoard ttt;
    char player = 'q';

    std::cout << "== TIC TAC TOE ==\n" << ttt.displayBoard();

    while (!ttt.gameOver())
    {
        player = player == 'x' ? 'o' : 'x';
        int input = getInput(player);

        while (!ttt.placeInputOnBoard(input, player))
        {
            std::cout << "Invalid input: " << input << "\n";
            input = getInput(player);
        }

        std::cout << ttt.displayBoard();
    }

    if (ttt.hasWinner())
    {
        std::cout << "Player " << playerNum(player) << " WINS!\n";
    }
    else
    {
        std::cout << "The game is a cat's game. No winner!\n";
    }
    
    return 0;
}
