#ifndef __SUDOKU_H__
#define __SUDOKU_H__

#include "board.h"

class Sudoku {
	public:
		Sudoku() = default;
		Sudoku(int, int**);

		void StartGame();
		void Play(int i, int j, int value);
		void Print();
		void Solve();
		void Hint(int i, int j);

	private:
		Board gameBoard;
		Board solution;

		void backtrack(int i_start, Board& aux, int& Nsol);
		int badSudoku; //0 if good, 1 if ambiguous, 2 if impossible
		bool solved;

};

#endif