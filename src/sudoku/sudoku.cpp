#include "sudoku.h"

using namespace std;


/////////////////////////
//////
Sudoku::Sudoku(int n, int** a){
	gameBoard = Board(n, a);
	solution = Board(n,a);
	solved = false;
}

/////////////////////////
//////
void Sudoku::Play(int i, int j, int value){
	if (! gameBoard.isPlayable(i,j)){
		cout << "You can't play there\n\n";
		return;
	}

	if(value < 0 || value > gameBoard.GetDim()){
		cout << "Invalid input\n\n";
		return;
	}

	if (! gameBoard.isValidPlay(i, j, value)){
		cout << "Invalid input\n\n";
		return;
	}

	gameBoard.Fill(i,j, value);
}


/////////////////////////
//////
void Sudoku::Print(){
	cout << gameBoard;
}


/////////////////////////
//////
void Sudoku::StartGame(){
	cout << "WELCOME TO SUDOKU!\n\n";
	cout << "Menu:\n-1 to exit\n-2 to solve,\n-3 for a hint\n\n";
	
	while(true){
		this->Print();
		cout << "\nWhere do you want to play? (-1 to exit)\nRow: ";

		int row, col, value;

		cin >> row;
		if(row == -1) break;

		if(row == -2){
			if (!solved) this->Solve();
			cout << "The solution is:\n" << solution;
			break;
		}

		if (row == -3){
			if (!solved) this->Solve();
			cout << "Row for the hint: ";
			cin >> row;
			cout << "Column for the hint: ";
			cin >> col;
			cout << "The value is " << solution(row-1, col-1) << endl;
			continue;
		}

		cout << "Column: ";
		cin >> col;

		cout << "Value (0 to delete): ";
		cin >> value;

		this->Play(row-1, col-1, value);

		if(gameBoard.isComplete()){
			cout << "YOU WON!!!\n";
			break;
		}
	}

	cout << "Bye bye!\n";
}


/////////////////////////
//////
void Sudoku::Solve(){
	Board aux = solution;
	int Nsol = 0;

	this->backtrack(0,aux, Nsol);

	if (Nsol == 0) badSudoku = 2;
	else if(Nsol == 1) badSudoku = 0;

	solved = true;
}

void Sudoku::backtrack(int i1, Board& aux, int& Nsol){
	if (aux.isComplete()){
		if(Nsol) badSudoku = 1;
		
		else{
			solution = aux;
			Nsol++;
		}

		return;
	}
		
	
	int dim = aux.GetDim();

	bool flag = false;
	for(int i=i1; i<dim; i++){
		for(int j=0; j<dim; j++){
			if(aux(i,j)) continue;

			flag = true;

			for(int val = 1; val <= dim; val++){
				if(aux.isValidPlay(i,j,val)){
					//cout << i << ", " << j << ": "<<val << endl;
					aux.Fill(i,j,val);
					//cout << aux << endl;
					this->backtrack(i, aux, Nsol);
					aux.Fill(i,j,0);
				}
				
			}

			break;	
		}
		if (flag) break;
	}
}

