# Smart Tic-Tac-Toe

The "Tic Tac Toe" is a very classic puzzle game with simple operation and great entertainment. Two players, one in a circle (O), one in a fork (X), take turns to play their own symbols on a 3 by 3 grid, the first to be horizontal, straight, and oblique to form a line to win.

If both parties are correct, they will get a tie. This game is actually controlled by the first player, the first player is the attack and the second player is the defender. This game has only 765 possible games and 26,830 games.

## Visualisation

![minimax](https://raw.githubusercontent.com/anandman03/Smart-Tic-Tac-Toe/main/Public/minimax.jpg)

## Installation

```
$ git clone https://github.com/anandman03/Smart-Tic-Tac-Toe.git
$ cd Smart-Tic-Tac-Toe
$ g++ Source.cpp
$ ./a.out
```

## Code Snippets

#### Cell Class

The `Cell class` contains x, y attributes representing ith row and jth column in grid.

```c++
class Cell {
private:
	int x, y;

public:
	Cell() {
		this->x = this->y = 0;
	}

	void setCoordinates(const vector<int> &p) {
		this->x = p[0];
		this->y = p[1];
	}

	vector<int> getCoordinates() {
		return {x, y};
	}
};
```

#### Game Class

The `constructor` takes the board, symbol of current player and symbol of opponent.

```c++
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
```

The `evaluate` function calculates if the current player wins/loses/draws based on checking of symbols in row, column and diagonal of board.

```c++
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
```

The `isMovesleft` check if the any moves can be taken or not.

```c++
bool isMovesLeft() {
	for(int i = 0 ; i < n ; ++i) {
		for(int j = 0 ; j < n ; ++j) {
			if(board[i][j] == '.') return true;
		}
	}
	return false;
}
```

The `miniMax` function considers all the possible ways the game can go and returns the value of the board.

```c++
int miniMax(bool isMaximizer) {
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

	int bestScore;
	// if this is maximizer's move.
	if(isMaximizer) {
		bestScore = -INF;
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				if(board[i][j] == '.') {
					board[i][j] = player;
					bestScore = max(bestScore, miniMax(!isMaximizer));
					board[i][j] = '.';
				}
			}
		}
	}
	// if this is not maximizer's move.
	else {
		bestScore = INF;
		for(int i = 0 ; i < n ; ++i) {
			for(int j = 0 ; j < n ; ++j) {
				if(board[i][j] == '.') {
					board[i][j] = opponent;
					bestScore = min(bestScore, miniMax(!isMaximizer));
					board[i][j] = '.';
				}
			}
		}
	}
	return bestScore;
}
```

The `getBestMove` returns the best possible move for the current player.

```c++
void getBestMove() {
	int bestValue = -INF;
	Cell bestMove;

	// Traverse all cells, evaluate minimax function for
	// all empty cells. And return the cell with optimal
	// value.
	for(int i = 0 ; i < n ; ++i) {
		for(int j = 0 ; j < n ; ++j) {
			// if cell is empty.
			if(board[i][j] == '.') {
				board[i][j] = player;
				int currValue = miniMax(false);
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
```

## License

[MIT](LICENSE)# Smart-tic-tac-toe
# Smart-tic-tac-toe
