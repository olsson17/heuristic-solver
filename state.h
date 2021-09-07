//a class to store the game state
#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <vector>
#include<cmath>
#include<bits/stdc++.h>
using namespace std;

    const int BOARDSIZE = 3;
    const int NUMBER_OF_BLOCKS = 6;

class State
{
    private:

        int grid[BOARDSIZE][BOARDSIZE];
    public:
        State();
        void pushDown();
        void printBoard();
        int removeBlockFrom(int column);
        bool insertBlockTo(int column, int value);
        bool moveBlock(int source, int destination);
        bool checkGoal(int,int,int);
        void getBlockPosition(int, int&, int&);
        bool isEmptyPos(int row, int column);
        bool isPosFull(int row, int column);
        bool goalPositionReady(int row, int column);
        bool isBlockTop(int block);
        bool removeBlockOnTopBlock(int Block, int x);
        bool removeBlockOnTopGoal(int row, int column, int x);
        bool addBlockUnderGoal(int row,int column,int destination);

        bool operator==(State s) 
        {
            for (int i = 0; i < BOARDSIZE; i++)
                for (int j = 0; j < BOARDSIZE; j++)
                    if (s.grid[i][j] != grid[i][j])
                        return false;
            return true;
        }
};

State::State()
{

    vector<int> oneToEight;// = { 0,1,2,3,4,5,6,7,8 };
    for(int i=0; i < BOARDSIZE*BOARDSIZE; i++ )
    {
        oneToEight.push_back(i);
    }
    srand((unsigned) time(0));
    int fList[BOARDSIZE*BOARDSIZE] = { };
    for (int i = 1; i < NUMBER_OF_BLOCKS+1; i++)
    {
        int randomNum = rand() % oneToEight.size();
        fList[oneToEight.at(randomNum)] = i;
        oneToEight.erase(oneToEight.begin() + randomNum);
    }
    for (int i = 0, x=0; i < BOARDSIZE; i++)
        for (int j = 0; j < BOARDSIZE; x++, j++)
            grid[i][j] = fList[x];

    pushDown();

}

void State::printBoard()
{
    cout << endl;
    for (int i = 0; i < BOARDSIZE; i++)
    {
        for (int j = 0; j < BOARDSIZE; j++)
        {
            if(grid[BOARDSIZE - i - 1][j]>0)
                cout << " | " << grid[BOARDSIZE - i - 1][j];
            else
            {
                cout << " |  ";
            }
        }
        cout <<" |" <<endl;
    }
    cout<<"  --- --- ---\n";
}

void State::pushDown()
{
    queue<int> p;
    for(int x =0; x<BOARDSIZE; x++)
    {
        for( int y = 0; y<BOARDSIZE; y++)
        {
            if(grid[y][x] !=0)
            {
                p.push(grid[y][x]);
            }
        }
        for(int z=0; z<BOARDSIZE; z++)
        {
            if(!p.empty())
            {
                grid[z][x]=p.front();
                p.pop();
            }
            else
                grid[z][x]=0;

        }
    }
}

int State::removeBlockFrom(int column){

    for(int x =0;x<= BOARDSIZE;x++){
        int value = grid[BOARDSIZE-x-1][column];
        if (value !=0){
            grid[BOARDSIZE-x-1][column]=0;
            return value;
        }
    }
    return -1;
}

bool State::insertBlockTo(int column, int value){
    for (int x = 0; x<BOARDSIZE; x++){

        int block = grid[x][column];
        if(block == 0){
            grid[x][column] = value;
            return true;
        }
    }
    return false;
}

bool State::moveBlock(int source, int destination)
{
    //cout <<endl<<"moveBlock:"<<"("<<source<<", "<<destination<<")"<<endl;

    if (source==destination){
        return false;
    }
    int value = removeBlockFrom(source);

    if (value == -1){
        return false;
    }

    return insertBlockTo(destination, value);
}

bool State::checkGoal(int row, int column, int block)
{
    if(grid[row][column]== block)
        return true;
    else
        return false;
}
bool State::isEmptyPos(int row, int column)
{
    return(grid[row][column]==0);
}

bool State::isPosFull(int row, int column)
{
    return(grid[row][column]!=0);
}

bool State::isBlockTop(int block)
{
    for(int x = 0; x<BOARDSIZE; x++)
    {
        if(block==grid[BOARDSIZE-1][x])
            return true;
    }
    return false;
}

bool State::goalPositionReady(int row, int column)
{
    if(row>0)
    {
        if(isEmptyPos(row, column) && isPosFull(row-1, column))
            return true;
    }
    else if(isEmptyPos(row, column))
    {
        return true;
    }
    return false;
}

void State::getBlockPosition(int block, int& row, int& column)
{
      for (int i = 0, x=0; i < BOARDSIZE; i++)
        for (int j = 0; j < BOARDSIZE; x++, j++)
            if(grid[i][j] ==block)
            {
                row=i;
                column=j;
                return;
            }
}


bool State::removeBlockOnTopBlock(int Block, int x)
{
    int row, column;
    if(!isBlockTop(Block))
    {
        getBlockPosition(Block, row, column);
    if(x==column)
        return true;
    }
    return false;
}

bool State::removeBlockOnTopGoal(int row, int column, int x)
{
    if(!goalPositionReady(row,column))
    {
        if(x==column)
           return true;
    }
    return false;
}
bool State::addBlockUnderGoal(int row,int column,int destination)
{
    if(!goalPositionReady(row,column))
    {
        if(isEmptyPos(row-1, column))
            return true;
    }
    return false;
}
#endif // STATE_H_INCLUDED
