/* Sat-Chitta-Ananda */

#include <bits/stdc++.h>
using namespace std;

// Cell Class
class Cell {
private:
	int x, y;

public:
	Cell(const int &x, const int &y) {
		this->x = x;
		this->y = y;
	}

	void setCoordinates(const vector<int> &p) {
		this->x = p[0];
		this->y = p[1];
	}

	vector<int> getCoordinates() {
		return {x, y};
	}
};

// Game Class
class Game {
private:
	int n;
	char player, opponent;
	vector<vector<char>> board;
	const int INF = (int)1e5;

public:
	Game(vector<vector<char>> board, char player, char opponent) {
		this->n = 3;
		this->board.resize(n, vector<char>(n, 0));
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				this->board[i][j] = board[i][j];
			}
		}
		this->player = player;
		this->opponent = opponent;
	}
	
	// check if the current player wins/loses/draw.
	int evaluate() {
		// check status for rows.
		for(int i = 0 ; i < n ; ++i) {
			if(board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
				if(board[i][0] == player) {
					return 10;
				}
				if(board[i][0] == player) {
					return -10;
				}
			}
		}
		// check status for columns.
		for(int i = 0 ; i < n ; ++i) {
			if(board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
				if(board[0][i] == player) {
					return 10;
				}
				if(board[0][i] == player) {
					return -10;
				}
			}
		}
		// check for top-left to bottom-right diagonal.
		if(board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
			if(board[1][1] == player) {
				return +10;
			}
			else {
				return -10;
			}
		}
		// check for top-right to bottom-left diagonal.
		if(board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
			if(board[1][1] == player) {
				return +10;
			}
			else {
				return -10;
			}
		}
		// in case of DRAW.
		return 0;
	}

	// check if the board is filled.
	bool isMovesLeft() {
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				if(board[i][j] == '.') return true;
			}
		}
		return false;
	}

	// This will return the best possible move for the player.
	void miniMaxAlgorithm() {
		int bestValue = -INF;
		Cell bestMove(-1, -1);
		// Traverse all cells, evaluate minimax function for all empty cells. And 
		// return the cell with optimal value.
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				// if cell is empty.
				if(board[i][j] == '.') {
					board[i][j] = player;
					int currValue = minimizer(0, -INF, INF);
					board[i][j] = '.';
					// update best move.
					if(bestValue < currValue) {
						bestValue = currValue;
						bestMove.setCoordinates({i, j});
					}
				}
			}
		}

		vector<int> currCoordinates = bestMove.getCoordinates();
		board[currCoordinates[0]][currCoordinates[1]] = player;
	}

	int maximizer(int level, int alpha, int beta) {
		// evaluate score based on current board.
		int score = evaluate();
		// if maximizer has won/lost return evaluated score.
		if(score == 10 || score == -10) {
			return score;
		}
		// if no moves are left then there is draw return 0 score.
		if(!isMovesLeft()) {
			return 0;
		}

		int bestScore = -INF;
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				if(board[i][j] == '.') {
					board[i][j] = player;
					bestScore = max(bestScore, minimizer(level+1, alpha, beta)-level);
					alpha = max(bestScore, alpha);
					board[i][j] = '.';
					if(alpha >= beta) {
						return alpha;
					}
				}
			}
		}
		return bestScore;
	}

	int minimizer(int level, int alpha, int beta) {
		// evaluate score based on current board.
		int score = evaluate();
		// if maximizer has won/lost return evaluated score.
		if(score == 10 || score == -10) {
			return score;
		}
		// if no moves are left then there is draw return 0 score.
		if(!isMovesLeft()) {
			return 0;
		}

		int bestScore = INF;
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				if(board[i][j] == '.') {
					board[i][j] = opponent;
					bestScore = min(bestScore, maximizer(level+1, alpha, beta)+level);
					beta = min(beta, bestScore);
					board[i][j] = '.';
					if(alpha >= beta) {
						return beta;
					}
				}
			}
		}
		return bestScore;
	}

	// print the board.
	void print() {
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				cout << board[i][j] << ' ';
			}
			cout << '\n';
		}
	}
};

int32_t main()
{
	// taking input
	vector<vector<char>> board(3, vector<char>(3));
	for(int i = 0 ; i < 3 ; ++i) {
		for(int j = 0 ; j < 3 ; ++j) {
			cin >> board[i][j];
		}
	}
	char player;
	cin >> player;
	char opponent = (player == 'x') ? 'o' : 'x';

	// initialize board
	Game g(board, player, opponent);
	g.miniMaxAlgorithm();
	g.print();

	return 0;
}