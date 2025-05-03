//2891382 Pieter Naude
//xxxxxxx Maria Olsen

#include <iostream>
#include <fstream>
#include "Board.h"
#include "ai.h"
#include <vector>

//#include "MCTS.h"
//#include "MCTSNode.h"
using namespace std;

int main()
{
    int SIZE;   //Length of the board
    int maxValue;   //biggest tile that can spawn
    char direction;
    int numMoves=0;
    char commas;
    vector<vector<int>> grid; //2D vector to form a grid

    //variables used for Expectimax algorithm
    int EMAI_Depth = 5; //depth of how many moves ahead the algorithm must search
    char EMAI_Direction;    //best move determined by algorithm

    //variables used for Monte Carlo Tree Search algorithm


    ifstream inData;
    ofstream outData;
    inData.open("reverse_2048.txt");
    outData.open("output.txt");
    if(!inData.is_open())
    {
        cout<<"File cannot be found"<<endl;
    }

    while(inData>>maxValue>>commas>>SIZE)
    {
        numMoves=0;
        Board myBoard(SIZE,maxValue,direction);
        myBoard.initialBoard(SIZE,grid,maxValue);//sets grid to initial board using size and maxValue
        myBoard.printBoard(SIZE,grid);//prints the initial board

        //EXPECTIMAX IMPLEMENTATION
        ExpectimaxClass Expectimax(SIZE,maxValue);  //creates an instance of ExpectimaxClass in main.cpp
        auto SNAKE = Expectimax.generate_snake_pattern(); //Creates a perfect pattern of tiles.


        while((myBoard.checkLoss(SIZE,grid,numMoves)==false)&&myBoard.checkWin(SIZE, grid)==false)//loop to play the game as long as 1000 moves has not been reached
        {
            EMAI_Direction = Expectimax.get_best_move(grid,EMAI_Depth,numMoves); //calls the Expectimax algorithm
            myBoard.makeMove(SIZE,grid,EMAI_Direction);//calls function responsible for moving and merging tiles
            numMoves++;// increases the counter for moves made
            cout<<"Number of moves: "<<numMoves<<endl;//displays how many move user has made so far
            myBoard.addTile(SIZE,grid,maxValue);//calls the function to add a tile after a move has been completed
            myBoard.printBoard(SIZE,grid);//prints the board after move and adding of tile have taken place
        }
    }


    inData.close();
    outData.close();
    return 0;
}
