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
    vector<vector<int>> PerfectSnake(Size,vector<int>(Size));
    int Tile = min_value;

    for (int i = 0; i < Size; ++i) {
        if (i % 2 == 0) {
            // Left to right
            for (int j = 0; j < Size; ++j) {
                PerfectSnake[i][j] = Tile;
                Tile *= 2;
            }
        } else {
            // Right to left
            for (int j = Size - 1; j >= 0; --j) {
                PerfectSnake[i][j] = Tile;
                Tile *= 2;
            }
        }
    }

    return PerfectSnake;
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
int ExpectimaxClass::expectiminimax(vector<vector<int>> curBoard, int depth, bool isPlayerTurn, int numMoves)
{
    int bestscore=0;
    int score = 0;
    Board tempBoard(Size, max_value, 'T');
    if (depth==0||tempBoard.checkLoss(Size,curBoard,numMoves)==true)
    {
        return evaluate_board(curBoard);
    }

    if (isPlayerTurn==true)
    {
        bestscore = INT_MAX;
        for (int dir=0; dir<4; dir++)
        {
            char DirChar;
            switch(dir)
            {
                case 0: DirChar = 'U'; break;
                case 1: DirChar = 'D'; break;
                case 2: DirChar = 'L'; break;
                case 3: DirChar = 'R'; break;
            }
            vector<vector<int>> newBoard= move_board(curBoard,DirChar);
            if (newBoard!=curBoard)
            {
                score = expectiminimax(newBoard,depth-1,false,numMoves);
                bestscore= max(bestscore,score);
            }
        }
        return bestscore;
    }
    else
    {
        vector<pair<int,int>> emptyTiles;
        for (int i =0; i<Size; i++)
        {
            for (int j=0; j<Size; j++)
            {
                if (curBoard[i][j]==0)
                {
                    emptyTiles.push_back({i,j});
                }
            }
        }
        if (emptyTiles.empty()) return evaluate_board(curBoard);

        int totalScore=0;
        for(auto[i,j] : emptyTiles)
        {
            curBoard[i][j]=max_value/2;
            totalScore +=expectiminimax(curBoard, depth-1, true,numMoves);

            curBoard[i][j]=max_value;
            totalScore +=9*expectiminimax(curBoard, depth-1, true,numMoves);

            curBoard[i][j]=0;
        }

        return totalScore/(10*emptyTiles.size());
    }
}

//Function to choose best move
char ExpectimaxClass::get_best_move(const vector<vector<int>>& board, int depth, int numMoves)
{
    int bestScore = INT_MIN;
    char bestMove = 'L';
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
                bestMove = DirChar;
            }
        }
    }
    return bestMove;
}

//Function to make a move
    vector<vector<int>> ExpectimaxClass::move_board(vector<vector<int>> grid, char Direction)
    {
        Board tempBoard(Size, max_value, Direction);
        tempBoard.makeMove(Size,grid,Direction);
        return grid;
    }


