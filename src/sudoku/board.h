#ifndef __BOARD_H__
#define __BOARD_H__

#include <iostream>

using namespace std;

class Board {
	public:
		Board() = default;
		Board(int, int**);
		Board(const Board&);

		//Getters
		int GetDim();
		int operator()(int i, int j);

		//Modifiers
		void Fill(int i, int j, int value);

		//Checkers
		bool isPlayable(int i, int j); 
		bool isValidFull();
		bool isValidPlay(int i, int j, int value); //assumes current sudoku is valid
		bool isComplete();

		//Utility
		friend ostream& operator<<(ostream&, Board);
		Board& operator=(const Board&);
		

	public:
		int n; // board of n x n blocks
		int dim; // board of dim x dim grids (dim = n*n)
		int** board; //1...9, or 0 if empty
		bool** fixed; 

		int filled;
};

#endif