//File: TicTacToe.cpp
//Name: Aarav Pahuja
//Date: 12/10/2025
//Description: This program is a version of the game tictactoe.
//Usage: This program will render games between a player and computer, record wins, losses and draws, and
//       return them from a dated text log. It supports hard and easy modes, player chooses X or O, and
//       the first player is chosen by coin flip.
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class GameBoard
{
public:
    vector<vector<string>> board;
    GameBoard() : board{ {{" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}} } {}
    void WelcomeMessage();
    void DrawGameBoard();
    string GetUserName();
    string GetUserSymbol();
    int FirstPlayer();
    void PlayerMove();
    void ComputerMove();
    void GameEngine();
    bool CheckWin(string symbol);
    bool CheckDraw();
    void DisplayLog();
    void WriteLog();

    void hardComputerMove();
    void SelectedMode();

private:
    string UserName;
    bool chosen = false;
    string Player = "";
    string PlayerSymbol = "";
    string ComputerSymbol = "";
    string HeadsOrTails = "";
    bool PlayerTurn = false;
    int row = -1;
    int column = -1;
    bool GameFinished = false;
    string LogOut = "";
    vector<string> Log;
    string UserWin = "";

    string Mode = "";
};

void GameBoard::WelcomeMessage()
{
    cout << "+---Welcome to Group One's Tick Tack Toe Game!---+\n\n";
    bool DisplayDone = false;
    while (DisplayDone == false)
    {
        cout << "Display games history.(type \"y\" for yes, or \"n\" for no.)\n";
        string input = "";
        cin >> input;
        if (input == "y")
        {
            DisplayLog();
            break;
        }
        else if (input == "n")
        {
            break;
        }
        else
        {
            cout << "Invalid selection:\n";
        }
    }

    bool ModeDone = false; //Select Hard or Easy mode.
    while (ModeDone == false)
    {
        cout << "Select difficulty.(type \"h\" for hard, or \"e\" for easy.)\n";
        string input = "";
        cin >> input;
        if (input == "h")
        {
            Mode = "hard";
            break;
        }
        else if (input == "e")
        {
            Mode = "easy";
            break;
        }
        else
        {
            cout << "Invalid selection:\n";
        }
    }
}

void GameBoard::DrawGameBoard()
{
    cout << "+---+---+---+" << endl;
    for (int i = 0; i < 3; i++)
    {
        cout << "| " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " |" << endl;
        cout << "+---+---+---+" << endl;
    }
    cout << endl;
}

string GameBoard::GetUserName()
{
    cout << "Enter your name: " << endl;
    cin >> UserName;
    cout << "Hello, " << UserName << " welcome to the game!" << endl << endl;
    return UserName;
}

string GameBoard::GetUserSymbol()
{
    cout << "Choose player: X or O?" << endl;

    while (chosen != true)
    {
        cin >> Player;
        if (Player == "X" || Player == "x")
        {
            PlayerSymbol = "X";
            ComputerSymbol = "O";
            chosen = true;
            cout << "You have chosen " << PlayerSymbol << "." << endl << endl;
        }
        else if (Player == "O" || Player == "o")
        {
            PlayerSymbol = "O";
            ComputerSymbol = "X";
            chosen = true;
            cout << "You have chosen " << PlayerSymbol << "." << endl << endl;
        }
        else
        {
            cout << "Invalid choice, please try again. (valid inputs: X, x, O, or o)" << endl;
        }
    }
    return PlayerSymbol;
}

int GameBoard::FirstPlayer()
{
    srand(time(0));
    cout << "Coin flip to choose who goes first. Heads or Tails?" << endl;
    cin >> HeadsOrTails;

    int coinFlip = rand() % 2;
    string result = (coinFlip == 0) ? "Heads" : "Tails";
    cout << "Result: " << result << endl;

    if ((HeadsOrTails == "Heads" || HeadsOrTails == "heads") && result == "Heads")
    {
        PlayerTurn = true;
    }
    else if ((HeadsOrTails == "Tails" || HeadsOrTails == "tails") && result == "Tails")
    {
        PlayerTurn = true;
    }
    else
    {
        PlayerTurn = false;
    }

    if (PlayerTurn == true)
    {
        cout << "Your move first.\n\n";
    }
    else
    {
        cout << "Computer move first.\n\n";
    }

    return PlayerTurn;
}

void GameBoard::PlayerMove()
{
    bool validMove = false;

    while (!validMove)
    {
        cout << UserName << "'s Move (" << PlayerSymbol << ")" << endl;
        cout << "Where would you like to place your marker? row/column (0 0 for the top left position)\n";
        cin >> row >> column;

        if (row >= 0 && row < 3 && column >= 0 && column < 3)
        {
            if (board[row][column] == " ")
            {
                board[row][column] = PlayerSymbol;
                validMove = true;
            }
            else
            {
                cout << "That position is already taken. Try again.\n";
            }
        }
        else
        {
            cout << "Invalid position. Please enter row and column between 0 and 2.\n";
        }
    }
}

void GameBoard::ComputerMove()
{
    cout << "Computer's Move (" << ComputerSymbol << ")" << endl;

    bool moved = false;
    while (!moved)
    {
        int r = rand() % 3;
        int c = rand() % 3;

        if (board[r][c] == " ")
        {
            board[r][c] = ComputerSymbol;
            cout << "Computer placed at position: " << r << " " << c << endl;
            moved = true;
        }
    }
}

bool GameBoard::CheckWin(string symbol)
{
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol)
        {
            return true;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol)
        {
            return true;
        }
    }

    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol)
    {
        return true;
    }

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol)
    {
        return true;
    }

    return false;
}

bool GameBoard::CheckDraw()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] == " ")
                return false;
        }
    }
    return true;
}

void GameBoard::GameEngine()
{
    while (GameFinished != true)
    {
        cout << "Current gameboard:\n";
        DrawGameBoard();

        if (PlayerTurn == true)
        {
            PlayerMove();

            if (CheckWin(PlayerSymbol))
            {
                DrawGameBoard();
                UserWin = "yes";
                WriteLog();

                cout << "Congratulations " << UserName << "! You win!\n";
                GameFinished = true;
            }
        }
        else
        {
            SelectedMode();//runs ComputerMove(); or HardComputerMove(); depending on mode selected.
            //Included to smoothly impliment hard/easy mode select into existing code.

            if (CheckWin(ComputerSymbol))
            {
                DrawGameBoard();
                UserWin = "no";
                WriteLog();

                cout << "Computer wins! Better luck next time.\n";
                GameFinished = true;
            }
        }

        if (!GameFinished && CheckDraw())
        {
            DrawGameBoard();
            UserWin = "draw";
            WriteLog();

            cout << "It's a draw!\n";
            GameFinished = true;
        }

        PlayerTurn = !PlayerTurn;
    }
}

void GameBoard::SelectedMode()
{
    if (Mode == "easy")
    {
        ComputerMove();
    }

    else if (Mode == "hard")
    {
        hardComputerMove();
    }
}

void GameBoard::DisplayLog()
{
    ifstream ReadScore("GameLog.txt");
    if (!ReadScore) //Checks if the file exists before creating it, to prevent override.
    {
        ofstream Score("GameLog.txt");//creates file
        ReadScore.open("GameLog.txt");//opens file
    }

    while (getline(ReadScore, LogOut))//Reads GameLog.txt into Log array.
    {
        Log.push_back(LogOut);
    }

    cout << "Game Log:\n";
    for (int i = 0; i < Log.size(); i++) //Outputs each element in Log array, to display past games.
    {
        cout << Log[i] << endl;
    }
    ReadScore.close();
    cout << endl;
}

void GameBoard::WriteLog()
{

    time_t Date; //returns local time. https://www.w3schools.com/c/c_date_time.php
    time(&Date);

    ofstream WriteToFile("GameLog.txt", ios::app); //Opens file in append mode, creates the file if it does not exist. https://www.tutorialspoint.com/how-to-append-text-to-a-text-file-in-cplusplus
    if (UserWin == "yes")
    {
        WriteToFile << ctime(&Date) << " " << UserName << " won the " << Mode << " mode game." << endl << endl; //Visualstudio throws a deprecation warning for this line do to its use of ctime, override or run in another compiler to run.
    }
    else if (UserWin == "draw")
    {
        WriteToFile << ctime(&Date) << " " << UserName << "'s " << Mode << " mode game ended in a draw." << endl << endl;
    }
    else
    {
        WriteToFile << ctime(&Date) << " " << UserName << " lost the " << Mode << " mode game." << endl << endl;
    }
    WriteToFile.close();
}

void GameBoard::hardComputerMove()
{
    cout << "Computer's Move (" << ComputerSymbol << ")" << endl;

    bool PlayerWinning;

    for (int r = 0; r < 3; r++) //Blocks player from winning.
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == " ")
            {
                board[r][c] = PlayerSymbol;
                PlayerWinning = CheckWin(PlayerSymbol);
                if (PlayerWinning == true)
                {
                    cout << "Computer placed at position: " << r << c << endl;
                    board[r][c] = ComputerSymbol;
                    return;
                }
                else
                {
                    board[r][c] = " "; //Undo if move not taken.
                }
            }
        }
    }

    for (int r = 0; r < 3; r++) //Computer trys to win.
    {
        for (int c = 0; c < 3; c++)
        {
            if (board[r][c] == " ")
            {
                board[r][c] = ComputerSymbol;
                PlayerWinning = CheckWin(ComputerSymbol);
                if (PlayerWinning == true)
                {
                    cout << "Computer placed at position: " << r << " " << c << endl;
                    board[r][c] = ComputerSymbol;
                    return;
                }
                else
                {
                    board[r][c] = " "; //Undo if move not taken.
                }
            }
        }
    }

    if (board[1][1] == " ") //Picks center spot first
    {
        cout << "Computer placed at position: " << 1 << " " << 1 << endl;
        board[1][1] = ComputerSymbol;
        return;
    }
    else if (board[1][1] != " ") //If center is taken, select an edge.
    {
        if (board[1][0] == " ")
        {
            cout << "Computer placed at position: " << 1 << " " << 0 << endl;
            board[1][0] = ComputerSymbol;
            return;
        }
        else if (board[0][1] == " ")
        {
            cout << "Computer placed at position: " << 0 << " " << 1 << endl;
            board[0][1] = ComputerSymbol;
            return;
        }
        else if (board[1][2] == " ")
        {
            cout << "Computer placed at position: " << 1 << " " << 2 << endl;
            board[1][2] = ComputerSymbol;
            return;
        }
        else if (board[2][1] == " ")
        {
            cout << "Computer placed at position: " << 2 << " " << 1 << endl;
            board[2][1] = ComputerSymbol;
            return;
        }
    }

    else if (board[1][0] != " " && board[0][1] != " " && board[1][2] != " " && board[2][1] != " ") // If center and edges taken, select a corner.
    {
        if (board[0][0] == " ")
        {
            cout << "Computer placed at position: " << 0 << " " << 0 << endl;
            board[0][0] = ComputerSymbol;
            return;
        }
        else if (board[0][2] == " ")
        {
            cout << "Computer placed at position: " << 0 << " " << 2 << endl;
            board[0][2] = ComputerSymbol;
            return;
        }
        else if (board[2][2] == " ")
        {
            cout << "Computer placed at position: " << 2 << " " << 2 << endl;
            board[2][2] = ComputerSymbol;
            return;
        }
        else if (board[2][0] == " ")
        {
            cout << "Computer placed at position: " << 2 << " " << 0 << endl;
            board[2][0] = ComputerSymbol;
            return;
        }
    }
}

int main()
{
    GameBoard game;
    game.WelcomeMessage();
    string UserName = game.GetUserName();
    string PlayerSymbol = game.GetUserSymbol();
    bool PlayerTurn = game.FirstPlayer();
    game.GameEngine();

    return 0;
}
