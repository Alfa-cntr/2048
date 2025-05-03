// ExpectiMax header
#ifndef AI_H_INCLUDED
#define AI_H_INCLUDED

#include "board.h"      // Include the Board class
#include <utility>      // For pair functions
#include <vector>       // For creating vectors for th grid
using namespace std;

class ExpectimaxClass
{
public:
    ExpectimaxClass(int boardSize, int maxValue, int minValue = 2); // Constructor

    vector<vector<int>> generate_snake_pattern() const;     //function to make perfect snake pattern
    int evaluate_board(const vector<vector<int>>& board) const;     //function to see how closely a set board matches the perfect snake.
    int expectiminimax(vector<vector<int>> board, int depth, bool isPlayer,int numMoves);    //Basis of expectimax algorithm that simulates potential boards
    char get_best_move(const vector<vector<int>>& board, int depth, int numMoves);     //compares moves simulated by expectiminimax and returns best move
    vector<vector<int>> move_board(vector<vector<int>> grid, char Direction);      //function to simulate a move being made by player.

private:
    int Size;
    int max_value;
    int min_value;
    vector<vector<int>> SNAKE;
};

#endif // AI_H_INCLUDED

