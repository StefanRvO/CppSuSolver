#include<iostream>
#include "./Board.cpp"    

int main(int argc, char* argv[]) {

Board board(argv[1]);
board.PrintBoard();
board.LogicSolveBoard();
board.PrintBoard();
board.BruteForceRandomParrent();
board.PrintBoard();
}    
