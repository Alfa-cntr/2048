//Board.cpp
#include "Board.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

Board::Board(int s,int mV,char d)
    :SIZE(s),grid(vector<vector<int>>(s,vector<int>(s,0))),maxValue(mV),direction(d)
{
    initialBoard(s,grid,mV);
}
int Board::getSize()
{
    return SIZE;
}
int Board::getMaxValue()
{
    return maxValue;
}

vector<vector<int>> Board::getGrid(){
return grid;
}
void Board::initialBoard(int s,vector<vector<int>> &grid, int mV)
{
    int x=time(0);
    srand(x);
    grid=vector<vector<int>>(s,vector<int>(s,0));//makes a grid according to the size entered by user
    int randomRow1,randomCol1,randomRow2,randomCol2;
    randomRow1=rand()%s;//declaring four random numbers in the range of the grid that will acts as the coordinates for the two initial tiles
    randomCol1=rand()%s;
    randomRow2=rand()%s;
    randomCol2=rand()%s;
    for(int i=0; i<s; i++)
    {
        for(int j=0; j<s; j++)
        {

            if(i==randomRow1&&j==randomCol1||i==randomRow2&&j==randomCol2)//if the coordinates match those chosen randomly then a tile with the maximum value is added
            {

                grid[i][j]=mV;
            }
            else //if not then all other tiles are set to zero
            {
                grid[i][j]=0;
            }
        }
    }
}
void Board::printBoard(int s,vector<vector<int>> &grid)
{
    for(int i=0; i<s; i++)
    {
        for(int j=0; j<s; j++)
        {
            if(grid[i][j]==0)//makes empty tiles be displayed as dashes
            {
                cout<<"-"<<"\t";
            }
            else//if not displays the actual value of the tile
            {
                cout<<grid[i][j]<<"\t";
            }
        }
        cout<<endl;
    }
}

void Board::makeMove(int s,vector<vector<int>> &grid,char d)
{
    int R,C;//variables used to represent row and column
    bool mergedOnce=false;//variable that assists with correct merging
    for(int i=0; i<s; i++)
    {

        for(int j=0; j<s-1; j++)
        {

            if(d=='L')
            {
                R=i;
                C=j+1;//when move is to the left loop starts from the second column since tiles in the first column cannot move
                if(grid[R][C]!=0 &&C!=0 && grid[R][C-1]==0)//if the current tile has a number and is not in the first column and the one to the left is empty
                {
                    grid[R][C-1]=grid[R][C];//then we make the tile to the left the current tile's number and set the current one to zero (tile moved to the left)
                    grid[R][C]=0;
                    j-=2;//the number that has been evaluated needs to be checked for possible movement again so the index for the column is shifted accordingly
                }
                else if(mergedOnce==true)//checks that once a tile has moved all the way that if the tile to its left has been merged already then no merging occurs
                {
                    mergedOnce=false;//the variable is reset to false for other possible merges in the board can take place
                }
                else if (C!=0 && grid[R][C]==grid[R][C-1]&& grid[R][C]!=0)// checks to see if tile at the left is equal to current tile(must not be a zero and must not be in the first column)
                {
                    grid[R][C-1]=(grid[R][C-1])/2;//tile to the left is halved and current tile is set to zero(tiles have merged)
                    grid[R][C]=0;
                    mergedOnce=true;//changes variable once merged
                }
            }
            else if(d=='R')
            {
                R=i;
                C=(s-1)-(j+1);//when move is to the right loop starts from the second last column since tiles in the last column cannot move
                if(grid[R][C]!=0&&C!=s-1&&grid[R][C+1]==0)//if the current tile has a number and is not in the last column and the one to the right is empty
                {
                    grid[R][C+1]=grid[R][C];//then we make the tile to the right the current tile's number and set the current one to zero (tile moved to the right)
                    grid[R][C]=0;
                    j-=2;//the number that has been evaluated needs to be checked for possible movement again so the index for the column is shifted accordingly
                }
                else if(mergedOnce==true)//checks that once a tile has moved all the way that if the tile to its right has been merged already then no merging occurs
                {
                    mergedOnce=false;//the variable is reset to false for other possible merges in the board can take place
                }
                else if (C!=s-1 && grid[R][C]==grid[R][C+1]&& grid[R][C]!=0)// checks to see if tile at the right is equal to current tile(must not be a zero and must not be in the last column)
                {
                    grid[R][C+1]=(grid[R][C+1])/2;//tile to the right is halved and current tile is set to zero(tiles have merged)
                    grid[R][C]=0;
                    mergedOnce =true;//changes variable once merged
                }


            }
            else if(d=='U')
            {
                C=i;
                R=j+1;//when move is up loop starts from the second row since tiles in the first row cannot move
                if(grid[R][C]!=0&&R!=0&&grid[R-1][C]==0)//if the current tile has a number and is not in the first row and the one above is empty
                {
                    grid[R-1][C]=grid[R][C];//then we make the tile above the current tile's number and set the current one to zero (tile moved up)
                    grid[R][C]=0;
                    j-=2;//the number that has been evaluated needs to be checked for possible movement again so the index for the row is shifted accordingly
                }
                else if(mergedOnce==true)//checks that once a tile has moved all the way that if the tile above it has been merged already then no merging occurs
                {
                    mergedOnce=false;//the variable is reset to false for other possible merges in the board can take place
                }
                else if (R!=0 && grid[R][C]==grid[R-1][C]&& grid[R][C]!=0 )// checks to see if tile above is equal to current tile(must not be a zero and must not be in the first row)
                {
                    grid[R-1][C]=(grid[R-1][C])/2;//tile above is halved and current tile is set to zero(tiles have merged)
                    grid[R][C]=0;
                    mergedOnce =true;//changes variable once merged

                }

            }
            else if(d=='D')
            {
                C=i;
                R=(s-1)-(j+1);//when move is down loop starts from the second last row since tiles in the last row cannot move
                if(grid[R][C]!=0&&R!=s-1&&grid[R+1][C]==0)//if the current tile has a number and is not in the last row and the one below is empty
                {
                    grid[R+1][C]=grid[R][C];//then we make the tile below the current tile's number and set the current one to zero (tile moved down)
                    grid[R][C]=0;
                    j-=2;//the number that has been evaluated needs to be checked for possible movement again so the index for the row is shifted accordingly
                }
                else if(mergedOnce==true)//checks that once a tile has moved all the way that if the tile below it has been merged already then no merging occurs
                {
                    mergedOnce=false; //the variable is reset to false for other possible merges in the board can take place
                }
                else if (R!=s-1 && grid[R][C]==grid[R+1][C]&& grid[R][C]!=0)// checks to see if tile below is equal to current tile(must not be a zero and must not be in the last row)
                {
                    grid[R+1][C]=(grid[R+1][C])/2;//tile below is halved and current tile is set to zero(tiles have merged)
                    grid[R][C]=0;
                    mergedOnce =true;//changes variable once merged
                }
            }
        }
    }
}

vector<char> Board::validMoves(int s,vector<vector<int>> &grid)
{
    vector<char> validDirections;
    char possibleDirection[4]= {'L','D','R','U'};
    vector<pair<int,int>> emptyTiles=getEmptyTiles(s,grid);
    for(int i=0; i<4; i++)
    {
        int numberEqual=0;
        vector<vector<int>> movedGrid=grid;
        makeMove(s,movedGrid,possibleDirection[i]);
        for(int j=0; j<s; j++)
        {
            for(int k=0; k<s; k++)
            {
                if(grid[j][k]==movedGrid[j][k])
                {
                    numberEqual++;
                }

            }
        }
        if(numberEqual!=s*s)
        {
            validDirections.push_back(possibleDirection[i]);
        }

    }

    return validDirections;
}

vector<pair<int,int>> Board::getEmptyTiles(int s,vector<vector<int>> &grid)
{
    vector<pair<int,int>> emptyTiles;
    for(int i=0; i<s; i++)
    {
        for(int j=0; j<s; j++)
        {
            if(grid[i][j]==0)
            {
                emptyTiles.push_back(make_pair(i,j));
            }
        }
    }
    return emptyTiles;
}
bool Board::checkWin(int s,vector<vector<int>>& grid)
{
    bool won=false;
    for(int i=0; i<s; i++)
    {
        for(int j=0; j<s; j++)
        {
            if(grid[i][j]==2)
            {
                won=true;
            }
        }
    }
    return won;
}

bool Board::checkLoss(int s,vector<vector<int>>& grid,int nM)
{
    bool lost=false;
    vector<char> moves=validMoves(s,grid);
    if(nM==1000||moves.empty()==true){
        lost=true;
    }
    return lost;
}

void Board::addTile(int s,vector<vector<int>> &grid,int mV)
{
    int x=time(0);
    srand(x);
    int values[3]= {0}; //declares an array for 3 values for the three possible options for new tiles
    int chosenRandomValue=0;
    int chosenRandomPosition=0;
    int row,column;
    vector<pair<int,int>> emptyTiles=getEmptyTiles(s,grid);
    for (int i=0; i<3; i++)
    {
        //sets values of array according to the maximum value the user entered
        if(mV==512)
        {
            values[0]=256;
            values[1]=128;
            values[2]=64;
        }
        else if(mV==256)
        {
            values[0]=128;
            values[1]=64;
            values[2]=32;
        }
        else if(mV==128)
        {
            values[0]=64;
            values[1]=32;
            values[2]=16;
        }

    }
    chosenRandomValue=rand()%3;
    chosenRandomPosition=rand()%emptyTiles.size();
    row=emptyTiles[chosenRandomPosition].first;
    column=emptyTiles[chosenRandomPosition].second;
    grid[row][column]=values[chosenRandomValue];//chooses a random value from the array to set a random coordinate in grid to that value
}
