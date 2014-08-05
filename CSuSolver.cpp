#include<iostream>
#include "./Board.cpp"    

int main(int argc, char* argv[]) {

Board board(argv[1]);
board.PrintBoard();
cout << board.BruteForce() << endl;
board.PrintBoard();

}    
