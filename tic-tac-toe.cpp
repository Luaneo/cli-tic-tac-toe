#include <iostream>
#include <array>

using namespace std;

enum class Cell {
	empty,
	cross,
	zero
};

ostream& operator<<(ostream& os, Cell cell) {
	switch (cell) {
	case Cell::empty:
		return os << ' ';
		break;
	case Cell::cross:
		return os << 'X';
		break;
	case Cell::zero:
		return os << 'O';
		break;
	}
}

enum class State {
	ongoing,
	tie,
	cross_won,
	zero_won
};

class Board {
private:
	array<array<Cell, 3>, 3> grid;
public:
	Board() {
		for (auto& row : grid) {
			for (auto& cell : row) {
				cell = Cell::empty;
			}
		}
	}
	const Cell& get_cell(int row, int col) const {
		return grid[row][col];
	}
	void set_cell(int row, int col, Cell cell) {
		grid[row][col] = cell;
	}
	State get_state() const {
		for (auto& row : grid) {
			if (row[0] != Cell::empty and row[0] == row[1] and row[1] == row[2]) {
				return (row[0] == Cell::cross ? State::cross_won : State::zero_won);
			}
		}
		for (int i = 0; i < 3; i++) {
			if (grid[0][i] != Cell::empty and grid[0][i] == grid[1][i] and grid[1][i] == grid[2][i]) {
				return (grid[0][i] == Cell::cross ? State::cross_won : State::zero_won);
			}
		}
		if (grid[0][0] != Cell::empty and grid[0][0] == grid[1][1] and grid[1][1] == grid[2][2]) {
			return (grid[0][0] == Cell::cross ? State::cross_won : State::zero_won);
		}
		if (grid[0][2] != Cell::empty and grid[0][2] == grid[1][1] and grid[1][1] == grid[2][0]) {
			return (grid[0][2] == Cell::cross ? State::cross_won : State::zero_won);
		}
		for (auto& row : grid) {
			for (auto& cell : row) {
				if (cell == Cell::empty) {
					return State::ongoing;
				}
			}
		}
		return State::tie;
	}
	void display() const {
		cout << "-------------\n"
			"|   |   |   |\n"
			"| " << grid[0][0] << " | " << grid[0][1] << " | " << grid[0][2] << " |\n"
			"|   |   |   |\n"
			"-------------\n"
			"|   |   |   |\n"
			"| " << grid[1][0] << " | " << grid[1][1] << " | " << grid[1][2] << " |\n"
			"|   |   |   |\n"
			"-------------\n"
			"|   |   |   |\n"
			"| " << grid[2][0] << " | " << grid[2][1] << " | " << grid[2][2] << " |\n"
			"|   |   |   |\n"
			"-------------\n";
	}
};

enum class Turn {
	cross,
	zero
};

int main()
{
	Board board;

	cout << "Welcome to Tic-tac-toe!\n";
	board.display();
	cout << "Enter the cells' position separated by one space (e.g. 3 2)\n";

	Turn turn = Turn::cross;
	while (board.get_state() == State::ongoing) {
		if (turn == Turn::cross) {
			cout << "X's turn\n";
		}
		else {
			cout << "O's turn\n";
		}
		int i, j;
		cin >> i >> j;
		if (turn == Turn::cross) {
			board.set_cell(--i, --j, Cell::cross);
			turn = Turn::zero;
		}
		else {
			board.set_cell(--i, --j, Cell::zero);
			turn = Turn::cross;
		}
		board.display();
	}

	switch (board.get_state()) {
	case State::tie:
		cout << "It's a tie!\n";
		return 0;
	case State::cross_won:
		cout << "X won!\n";
		return 0;
	case State::zero_won:
		cout << "O won!\n";
		return 0;
	}
}
