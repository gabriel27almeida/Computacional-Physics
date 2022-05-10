#include "board.h"

/////////////////////////
//////
Board::Board(int N, int** a){
	n = N;
	dim = N*N;
	board = new int*[dim];
	fixed = new bool*[dim];
	filled = 0;
	for(int i = 0; i < dim; i++){
		board[i] = new int[dim];
		fixed[i] = new bool[dim];
		for(int j = 0; j < dim; j++){
			board[i][j] = a[i][j];

			if(a[i][j]) filled++;
			fixed[i][j] = (a[i][j] != 0);
		} 
	}
}


/////////////////////////
//////
Board::Board(const Board& b){
	n = b.n;
	dim = b.dim;
	filled = b.filled;
	board = new int*[dim];
	fixed = new bool*[dim];
	for(int i = 0; i < dim; i++){
		board[i] = new int[dim];
		fixed[i] = new bool[dim];
		for(int j = 0; j < dim; j++){
			board[i][j] = b.board[i][j];
			fixed[i][j] = b.fixed[i][j];
		} 
	}
}

/////////////////////////
//////
Board& Board::operator=(const Board& b){
	this->n = b.n;
	this->dim = b.dim;
	this->filled = b.filled;
	this->board = new int*[dim];
	this->fixed = new bool*[dim];
	for(int i = 0; i < dim; i++){
		this->board[i] = new int[dim];
		this->fixed[i] = new bool[dim];
		for(int j = 0; j < dim; j++){
			this->board[i][j] = b.board[i][j];
			this->fixed[i][j] = b.fixed[i][j];
		} 
	}

	return *this;
}

/////////////////////////
//////
int Board::GetDim(){
	return dim;
}

/////////////////////////
//////
int Board::operator()(int i, int j){
	return board[i][j];
}

/////////////////////////
//////
void Board::Fill(int i, int j, int value){
	board[i][j] = value;
	if(value) filled++;
	else filled--;
}

/////////////////////////
//////
bool Board::isPlayable(int i, int j){
	return i >= 0 && i < dim && j>= 0 && j < dim && !fixed[i][j];
}

/////////////////////////
//////
bool Board::isValidFull(){

	//check lines
	for(int i=0; i<dim; i++){
		bool has_occurred[dim];
		for(auto& u: has_occurred) u = false;

		for(int j=0; j<dim; j++){
			if (! board[i][j] ) continue;

			if( has_occurred[board[i][j] - 1]) return false;

			has_occurred[board[i][j] - 1] = true;
		}
	}

	//check columns
	for(int i=0; i<dim; i++){
		bool has_occurred[dim];
		for(auto& u: has_occurred) u = false;

		for(int j=0; j<dim; j++){
			if (! board[j][i] ) continue;

			if( has_occurred[board[j][i] - 1]) return false;

			has_occurred[board[j][i] - 1] = true;
		}
	}

	//check boxes
	for(int i=0; i<dim; i++){
		//position if up-left element of the box
		int row = i/n * n;
		int col = n * (i%n);

		bool has_occurred[dim];
		for(auto& u: has_occurred) u = false;

		for(int j = 0; j < dim; j++){
			int drow = j/n;
			int dcol = j%n;

			if (! board[row+drow][col+dcol] ) continue;

			if (has_occurred[board[row + drow][col + dcol] - 1]) return false;

			has_occurred[board[i][j] - 1] = true;
		}
	}

	//all clear
	return true;
}



/////////////////////////
//////
bool Board::isValidPlay(int i, int j, int value){
	if (! value) return true;
	
	//Check line
	for(int k=0; k < dim; k++){
		if (board[i][k] == value) return false;
	}

	//Check column
	for(int k=0; k < dim; k++){
		if (board[k][j] == value) return false;
	}

	//Check box

	int row = i/n * n; //position of up-left element of the box
	int col = j/n * n;

	for(int k = 0; k < dim; k++){
		int drow = k/n;
		int dcol = k%n;

		if (board[row + drow][col + dcol] == value) return false;
	}	

	//all clear
	return true;
}


/////////////////////////
//////

bool Board::isComplete(){
	return (filled == dim*dim);
}


/////////////////////////
//////
ostream& operator<<(ostream& out, Board b){
	int n = b.n;
	int dim = b.dim;

	for(int i=0; i < n; i++){
		for(int j=0; j < n; j++){
			for(int k = 0; k < dim; k++){
				if (k!= 0 && k % n == 0) out << "| ";

				if(b(n*i + j, k) != 0) out << b(n*i + j, k) << " ";
				else out << "  ";
			}
			out << "\n";
		}

		//fill - - - + - - - ...
		if(i == n-1) continue;

		for(int k = 0; k < dim; k++){
			if( k!= 0 && k % n == 0) out << "+ ";
			out << "- ";
		}
		out << "\n";
	}

	return out;
}