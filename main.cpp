#include <iostream>
#include <array>
#include <algorithm>
#include <string>
#include <numeric>

constexpr char DIGIT_DIFF = '0';
constexpr char ALPHA_DIFF = ('a' - 10);

constexpr int convert(char input)
{
    return std::isdigit(input) ? input - DIGIT_DIFF : input - ALPHA_DIFF;
}

constexpr char convert(int input)
{
    return static_cast<char>(input < 10 ? input + DIGIT_DIFF : input + ALPHA_DIFF);
}

constexpr char playerNum(char player)
{
    return player == 'x' ? '1' : '2';
}

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
            char test = convert(input);
            if (board[--input] == test)
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
        constexpr size_t EXTENT = WIDTH - 1;

        for (size_t pos = 0; pos < AREA; ++pos)
        {
            retStr += board[pos];
            retStr += pos % WIDTH < EXTENT ? '|' : '\n';
            if (pos % WIDTH == EXTENT && pos / HEIGHT < EXTENT)
            {
                retStr += '-';

                for (size_t counter = 0; counter < EXTENT; ++counter)
                {
                    retStr += "--";
                }

                retStr += '\n';
            }
        }

        return retStr;
    }

private:
    static_assert(WIDTH >= 3 && WIDTH <= 5, "This Tic-Tac-Toe Game only supports compilation with widths of 3, 4, or 5");
    // I use digits instead of '!' for filler locations to make it clear and easy for players to know which number
    // positions correlate with a player's possible choices.
    template <int NUM>
    constexpr static std::array<char, NUM> BOARD_INIT = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    template <>
    constexpr static std::array<char, 16> BOARD_INIT<16> = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    template <>
    constexpr static std::array<char, 25> BOARD_INIT<25> = {'1', '2', '3', '4' ,'5', '6', '7', '8', '9', 'a',
                                                            'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
                                                            'l', 'm', 'n', 'p', 'q'};

    std::array<char, AREA> board = BOARD_INIT<AREA>;
    bool winner = false;

    template <int NUM> constexpr static size_t WIN_NUM = 8;
    template <> constexpr static size_t WIN_NUM<16> = 10;
    template <> constexpr static size_t WIN_NUM<25> = 12;

    template <int NUM>
    constexpr static std::array<std::array<int, 3>, WIN_NUM<NUM>> WIN_OPTS{{
        {{ 0, 1, 2 }}, {{ 3, 4, 5 }}, {{ 6, 7, 8 }}, {{ 0, 3, 6 }},
        {{ 1, 4, 7 }}, {{ 2, 5, 8 }}, {{ 0, 4, 8 }}, {{ 2, 4, 6 }}
    }};

    template <>
    constexpr static std::array<std::array<int, 4>, WIN_NUM<16>> WIN_OPTS<16>{{
        {{ 0, 1, 2, 3 }}, {{ 4, 5, 6, 7 }}, {{ 8, 9, 10, 11 }}, {{ 12, 13, 14, 15 }}, {{ 0, 4, 8, 12 }},
        {{ 1, 5, 9, 13 }}, {{ 2, 6, 10, 14 }}, {{ 3, 7, 11, 15 }}, {{ 0, 5, 10, 15 }}, {{ 3, 6, 9, 12 }}
    }};

    template <>
    constexpr static std::array<std::array<int, 5>, WIN_NUM<25>> WIN_OPTS<25>{{
        {{ 0, 1, 2, 3, 4}}, {{ 5, 6, 7, 8, 9 }}, {{ 10, 11, 12, 13, 14 }}, {{ 15, 16, 17, 18, 19 }}, {{ 20, 21, 22, 23, 24 }},
        {{ 0, 5, 10, 15, 20 }}, {{ 1, 6, 11, 16, 21 }}, {{ 2, 7, 12, 17, 22 }}, {{ 3, 8, 13, 18, 23 }}, {{ 4, 9, 14, 19, 24 }},
        {{ 0, 6, 12, 18, 24 }}, {{ 4, 8, 12, 16, 20 }}
    }};

    constexpr static std::array<std::array<int, WIDTH>, WIN_NUM<AREA>> winningOpts = WIN_OPTS<AREA>;

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

char getInput(char player)
{
    char input;
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
    char player = 'z';

    std::cout << "== TIC TAC TOE ==\n" << ttt.displayBoard();

    while (!ttt.gameOver())
    {
        player = player == 'x' ? 'o' : 'x';
        char input = getInput(player);

        while (!ttt.placeInputOnBoard(convert(input), player))
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
