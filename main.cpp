#include <iostream>
#include <string>

class Player {
public:
    std::string name;
    char symbol;
    int wins;

    Player(std::string n, char s) {
        name = n;
        symbol = s;
        wins = 0;
    }
};

class TicTacToe {
private:
    char board[3][3];
    Player *player1;
    Player *player2;

public:
    TicTacToe() {
        player1 = new Player("Player 1", 'X');
        player2 = new Player("Computer", 'O');

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
            }
        }
    }

    void play() {
        std::cout << "Please enter your name: ";
        std::string player1_name;
        std::cin >> player1_name;
        player1->name = player1_name;
        Player *currentPlayer = player1;

        while (true) {
            std::cout << "Current board:" << std::endl;
            printBoard();

            if(currentPlayer == player1){
                std::cout << currentPlayer->name << ", please enter a number between 1 and 9 to set the location of your symbol: ";
                int location;
                std::cin >> location;

                if (location < 1 || location > 9) {
                    std::cout << "Invalid input. Please enter a number between 1 and 9." << std::endl;
                    continue;
                }

                int row = (location - 1) / 3;
                int col = (location - 1) % 3;

                if (board[row][col] == ' ') {
                    board[row][col] = currentPlayer->symbol;
                } else {
                    std::cout << "That space is already occupied. Please try again." << std::endl;
                    continue;
                }
            }else{
                //computer play
                int location;
                int player_row, player_col;
                bool found = false;

                // check if the computer can win in the next move
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if(board[i][j] == ' '){
                            board[i][j] = currentPlayer->symbol;
                            if (isWon(currentPlayer->symbol)) {
                                location = i*3 + j + 1;
                                found = true;
                                break;
                            }
                            board[i][j] = ' ';
                        }
                    }
                    if(found)
                        break;
                }
                // check if the player can win in the next move
                if(!found){
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            if(board[i][j] == ' '){
                                board[i][j] = player1->symbol;
                                if (isWon(player1->symbol)) {
                                    location = i*3 + j + 1;
                                    player_row = i;
                                    player_col = j;
                                    found = true;
                                    break;
                                }
                                board[i][j] = ' ';
                            }
                        }
                        if(found)
                            break;
                    }
                }
                // if neither can win in the next move, play in a random location
                if(!found){
                    do {
                        location = rand() % 9 + 1;
                        player_row = (location - 1) / 3;
                        player_col = (location - 1) % 3;
                    }while(board[player_row][player_col] != ' ');
                }
                board[player_row][player_col] = currentPlayer->symbol;
                std::cout << "Computer played: "<< location << std::endl;
            }

            if (isWon(currentPlayer->symbol)) {
                std::cout << "Congratulations, " << currentPlayer->name << "! You have won the game." << std::endl;
                currentPlayer->wins++;
                break;
            } else if (isDraw()) {
                std::cout << "The game is a draw." << std::endl;
                break;
            }

            currentPlayer = (currentPlayer == player1) ? player2 : player1;
        }

        std::cout << "Game over. Final board:" << std::endl;
        printBoard();
        std::cout << "Statistics:" << std::endl;
        std::cout << player1->name << ": " << player1->wins << " wins" << std::endl;
        std::cout << player2->name << ": " << player2->wins << " wins" << std::endl;
    }

    struct GameStatistics {
        int player1_wins;
        int player2_wins;
        int draws;
        int games_played;
    };
    GameStatistics stats;

    void menu(){
        int choice;
        do{
            std::cout << "Please select an option:" << std::endl;
            std::cout << "1. Start a new game" << std::endl;
            std::cout << "2. View game statistics" << std::endl;
            std::cout << "3. Exit" << std::endl;
            std::cin >> choice;
            switch(choice){
                case 1:
                    play();
                    stats.games_played++;
                    break;
                case 2:
                    // code to view game statistics
                    std::cout << "Statistics:" << std::endl;
                    std::cout << player1->name << ": " << player1->wins << " wins" << std::endl;
                    std::cout << player2->name << ": " << player2->wins << " wins" << std::endl;
                    std::cout << "Draws: " << stats.draws << std::endl;
                    std::cout << "Games played: " << stats.games_played << std::endl;
                    break;
                case 3:
                    std::cout << "Exiting the game..." << std::endl;
                    exit(0);
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
            }
        } while(choice != 3);
    }


private:
    void printBoard() {
        std::cout << "-------------" << std::endl;
        for (int i = 0; i < 3; i++) {
            std::cout << "| ";
            for (int j = 0; j < 3; j++) {
                if(board[i][j] == ' ')
                    std::cout << (i*3 + j + 1) << " | ";
                else
                    std::cout << board[i][j] << " | ";
            }
            std::cout << std::endl;
            std::cout << "-------------" << std::endl;
        }
    }


    bool isWon(char symbol) {
        // Check rows
        for (int i = 0; i < 3; i++) {
            if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
                return true;
            }
        }

        // Check columns
        for (int j = 0; j < 3; j++) {
            if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == symbol) {
                return true;
            }
        }

        // Check diagonals
        if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
            return true;
        }
        if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
            return true;
        }

        return false;
    }

    bool isDraw() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

int main() {
    TicTacToe game;
    game.menu();
    game.play();
    return 0;
}

