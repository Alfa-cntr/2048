#ifndef BOARD_H
#define BOARD_H
#include <vector>

using namespace std;
class Board
{
public:
    Board(int, int, char); //size,maxvalue,direction
    int getSize();
    int getMaxValue();
    vector<vector<int>> getGrid();
    void initialBoard(int,vector<vector<int>> &,int);
    void printBoard(int,vector<vector<int>> &);
    void makeMove(int,vector<vector<int>> &,char);
    vector<char> validMoves(int,vector<vector<int>>&);
    bool checkWin(int,vector<vector<int>>&);
    bool checkLoss(int,vector<vector<int>> &,int nM);
    vector<pair<int,int>> getEmptyTiles(int,vector<vector<int>> &);
    void addTile(int,vector<vector<int>> &,int);

private:
    int SIZE;
    vector<vector<int>> grid;
    int maxValue;
    char direction;
};

#endif // BOARD_H
