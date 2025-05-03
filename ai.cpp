// ai.cpp
#include "ai.h"
#include "board.h"
#include <iostream>
#include <algorithm>    // For max()
#include <limits>       // For numeric_limits
#include <cmath>

using namespace std;
ExpectimaxClass::ExpectimaxClass(int boardSize, int maxValue, int minValue)
    : Size(boardSize), max_value(maxValue), min_value(minValue)
    {
        SNAKE = generate_snake_pattern();
    }

//Perfect Snake generation
vector<vector<int>> ExpectimaxClass::generate_snake_pattern() const
{
    vector<vector<int>> weights(Size, vector<int>(Size));
    int weight = max_value;

    for (int i = 0; i < Size; ++i) {
        if (i % 2 == 0) {
            // Left to right
            for (int j = 0; j < Size; ++j) {
                weights[i][j] = weight;
                weight /= 2;
                if (weight < min_value) weight = min_value;
            }
        } else {
            // Right to left
            for (int j = Size - 1; j >= 0; --j) {
                weights[i][j] = weight;
                weight /= 2;
                if (weight < min_value) weight = min_value;
            }
        }
    }

    return weights;
}

//Evaluate boards heuristic score
int ExpectimaxClass::evaluate_board(const vector<vector<int>>& board) const
{
    int score=0;
    for (int i = 0; i < Size; ++i) {
        for (int j = 0; j < Size; ++j) {
            score += board[i][j] * SNAKE[i][j];
        }
    }
    return score;
}
//function to recursively give each board state a score.
int ExpectimaxClass::expectiminimax(vector<vector<int>> board, int depth, bool isPlayer, int numMoves)
{
    Board TempBoard(Size, max_value, 'U');
    if (depth==0||TempBoard.checkLoss(Size,board,numMoves)==true)
    {
        return evaluate_board(board);
    }
    if(isPlayer)
    {
        int bestScore = INT_MIN;
        for (int dir=0; dir<4; ++dir)
        {
            char DirChar;
            switch(dir)
            {
                case 0: DirChar = 'U'; break;
                case 1: DirChar = 'D'; break;
                case 2: DirChar = 'L'; break;
                case 3: DirChar = 'R'; break;
            }
            vector<vector<int>> newBoard= move_board(board,DirChar);
            if (newBoard!=board)
            {
                int score = expectiminimax(newBoard,depth-1,false,numMoves);
                bestScore= max(bestScore,score);
            }
        }
        return bestScore;
    } else
    {
        vector<pair<int,int>> emptyTiles;
        for (int i =0; i<Size; i++)
        {
            for (int j=0; j<Size; j++)
            {
                if (board[i][j]==0)
                {
                    emptyTiles.push_back({i,j});
                }
            }
        }
        if (emptyTiles.empty()) return evaluate_board(board);

        int totalScore=0;
        for(auto[i,j] : emptyTiles)
        {
            board[i][j]=max_value/2;
            totalScore +=expectiminimax(board, depth-1, true,numMoves);

            board[i][j]=max_value;
            totalScore +=9*expectiminimax(board, depth-1, true,numMoves);

            board[i][j]=0;
        }

        return totalScore/(10*emptyTiles.size());
    }
}

//Function to choose best move
char ExpectimaxClass::get_best_move(const vector<vector<int>>& board, int depth, int numMoves)
{
    int bestScore = INT_MIN;
    int bestMove = -1;
    char DirChar;

    for (int dir= 0; dir<4; ++dir)
    {
        switch(dir)
        {
            case 0: DirChar = 'U';  break;
            case 1: DirChar = 'D';  break;
            case 2: DirChar = 'L';  break;
            case 3: DirChar = 'R';  break;
        }
        vector<vector<int>> newBoard = move_board(board, DirChar);
        if(newBoard!=board)
        {
            int score = expectiminimax(newBoard,depth-1,false,numMoves);
            if (score>bestScore)
            {
                bestScore = score;
                bestMove = dir;
            }
        }
    }
    switch (bestMove)
    {
        case 0: return 'U';
        case 1: return 'D';
        case 2: return 'L';
        case 3: return 'R';
        default: return 'FAIL';
    }
}

//Function to make a move
    vector<vector<int>> ExpectimaxClass::move_board(vector<vector<int>> grid, char Direction)
    {
        Board tempBoard(Size, max_value, Direction);
        tempBoard.makeMove(Size,grid,Direction);
        return grid;
    }

