#include <iostream>
#include  <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;


std::ifstream settings("maze.txt");
//int WIDTH;
//int HEIGHT;
//int wincolor;

//settings>>WIDTH;
//settings>>HEIGHT;


const int WIDTH =10;
const int  HEIGHT=10;



//function prototypes
void printMaze(char maze[][WIDTH],int curx,int cury);
bool validMove(char maze[][WIDTH],bool visited[][WIDTH],
                int newX,int newY );
bool move(char maze[][WIDTH],bool visited[][WIDTH],
                int &curX,int &curY,int newX,int newY);
//return true or false if moving to the pecified coordinate is valid
//return false if we have been to the cell already
bool validMove(char maze[][WIDTH],bool visited[][WIDTH],
                int newX, int newY)

{
    //check for going offf maze edges
    if (newX <0 ||  newX>=WIDTH)
        return false;
    if (newY<0 ||  newY>=HEIGHT)
        return false;
    //check if target is wall
    if (maze[newY][newX] =='+')
        return false;
    //check if visited
    if (visited[newY][newX])
        return false;
    return true;
}
//mke the move on the maz e to move to a nnew coordnte ,,passing curX and curY by reference so they r  changed  to the new ccordnates.we assume the move coorntaes are valid,it returns true if we mov to exit ,false othrwise..also update the visited array
bool move (char maze[][WIDTH],bool visited[][WIDTH],
            int &curX, int &curY, int newX, int newY)
{
    bool foundExit =false;
    if (maze[newY][newX] =='P')//check for exit
        foundExit=true;
    curX =newX;//update location
    curY=newY;
    visited[curY][curX]=true;
    return foundExit;

}
//display the maze  in ASCII 

void printMaze(char maze[][WIDTH],int curx,int cury)
{
    for (int y=0; y<HEIGHT;y++)
    {
        for(int x=0; x<WIDTH;x++)
        {
             
            if ((x==curx) &(y==cury))
                 cout<<"M";
                        
            
            else
            
                cout <<maze[y][x];
            
        }
        cout <<endl;
    }

}           
//using recursive search from x,y until we find exit
bool search (char maze[][WIDTH],bool visited[][WIDTH],int x,int y)
{
    bool foundExit;
    if (maze[y][x]=='P')
        return true;
        
    visited[y][x]=true;
    if(validMove(maze,visited,x, y -1))
        foundExit =search(maze,visited,x,y -1);
    if (!foundExit &&(validMove(maze,visited, x,y+1)))
        foundExit =search(maze,visited,x,y +1);  
    if (!foundExit &&(validMove(maze,visited, x -1,y)))
        foundExit =search(maze,visited,x-1,y );
    if (!foundExit &&(validMove(maze,visited, x+1,y)))
        foundExit =search(maze,visited,x+1,y);
    if (foundExit)
    {
        printMaze(maze, x,y);
        
        cout <<endl;
        return true;
    }
    return false;

}
int main()
{
    char maze[HEIGHT][WIDTH]={
                {'+', '+', '+', '+', '+', '+', '+', '+', '+', '+'},
        {'+', ' ', ' ', ' ', ' ', ' ', '+', ' ', ' ', '+'},
        {'+', ' ', '+', ' ', ' ', ' ', '+', ' ', ' ', '+'},
        {'+', ' ', '+', '+', '+', ' ', '+', ' ', ' ', '+'},
        {'+', ' ', ' ', ' ', '+', ' ', '+', ' ', ' ', '+'},
        {'+', ' ', ' ', ' ', '+', ' ', ' ', ' ', '+', '+'},
        {'+', ' ', '+', '+', '+', ' ', ' ', ' ', ' ', '+'},
        {'+', ' ', '+', ' ', ' ', ' ', '+', ' ', ' ', '+'},
        {'+', ' ', ' ', ' ', ' ', ' ', '+', ' ', 'P', '+'},
        {'+', '+', '+', '+', '+', '+', '+', '+', '+', '+'}};

      bool visited[HEIGHT][WIDTH];
    int x = 1, y = 1;
    bool foundExit = false;
    // Initialize visited locations to false
    for (int x = 0; x < WIDTH; x++)
        for (int y = 0; y < HEIGHT; y++)
            visited[y][x] = false;
    visited[y][x] = true;
    cout << search(maze, visited, x, y) << endl;
}
    