/*
 * Sudoku.cpp
 *
 *  Created on: Jun 21, 2018
 *      Author: naing
 */

#include "Sudoku.h"
#include <set>
#include <algorithm>
#include <array>


int Sudoku::sudoku[size][size] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // dummy array since all arrays start at index 0

	{0, 	3, 7, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 8, 0, 	1, 6, 0, 	3, 2, 0},
	{0, 	0, 0, 0, 	0, 2, 0, 	0, 0, 0},

	{0, 	0, 0, 0, 	0, 5, 1, 	0, 4, 0},
	{0, 	0, 0, 9, 	8, 0, 2, 	5, 0, 0},
	{0, 	0, 4, 0, 	6, 3, 0, 	0, 0, 0},

	{0, 	0, 0, 0, 	0, 9, 0, 	0, 0, 0},
	{0, 	0, 9, 4, 	0, 1, 3, 	0, 7, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 8, 5}
};


/*	{0, 	0, 7, 8, 	0, 4, 0, 	0, 0, 0},
	{0, 	2, 0, 0, 	1, 0, 0, 	7, 0, 3},
	{0, 	0, 0, 0, 	7, 0, 0, 	0, 6, 0},

	{0, 	4, 0, 3, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 6, 0, 	5, 0, 9, 	0, 4, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	1, 0, 9},

	{0, 	0, 8, 0, 	0, 0, 3, 	0, 0, 0},
	{0, 	6, 0, 7, 	0, 0, 4, 	0, 0, 2},
	{0, 	0, 0, 0, 	0, 5, 0, 	3, 8, 0}
 *
 *
 */

/* 	{0, 	8, 0, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 0, 3, 	6, 0, 0, 	0, 0, 0},
	{0, 	0, 7, 0, 	0, 9, 0, 	2, 0, 0},

	{0, 	0, 5, 0, 	0, 0, 7, 	0, 0, 0},
	{0, 	0, 0, 0, 	0, 4, 5, 	7, 0, 0},
	{0, 	0, 0, 0, 	1, 0, 0, 	0, 3, 0},

	{0, 	0, 0, 1, 	0, 0, 0, 	0, 6, 8},
	{0, 	0, 0, 8, 	5, 0, 0, 	0, 1, 0},
	{0, 	0, 9, 0, 	0, 0, 0, 	4, 0, 0}
 *
 */

/* {0, 	3, 7, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 8, 0, 	1, 6, 0, 	3, 2, 0},
	{0, 	0, 0, 0, 	0, 2, 0, 	0, 0, 0},

	{0, 	0, 0, 0, 	0, 5, 1, 	0, 4, 0},
	{0, 	0, 0, 9, 	8, 0, 2, 	5, 0, 0},
	{0, 	0, 4, 0, 	6, 3, 0, 	0, 0, 0},

	{0, 	0, 0, 0, 	0, 9, 0, 	0, 0, 0},
	{0, 	0, 9, 4, 	0, 1, 3, 	0, 7, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 8, 5}
 *
 *
 */

/* 	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},

	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},

	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0},
	{0, 	0, 0, 0, 	0, 0, 0, 	0, 0, 0}
*/

map< pair<int, int>, vector<int>> Sudoku::cons;

Sudoku::Sudoku(int row, int col) {
	constraint(row, col);
	setConsArray(row, col);
}

Sudoku::~Sudoku() {
	for (int i = 0; i <= 9; ++i) {
		finding_constraint[i] = 0;
	}
}

void Sudoku::rowconstraint(int row) {
	for (int i = 1; i <= 9; i++) {
		finding_constraint[sudoku[row][i]] = true;
	}
}

void Sudoku::colconstraint(int col) {
	for (int i = 1; i <= 9; i++) {
		finding_constraint[sudoku[i][col]] = true;
	}
}

void Sudoku::constraint(int row, int col) {
	rowconstraint(row);
	colconstraint(col);
	if (row%3 == 1) {
		if (col%3 == 1) {
			finding_constraint[sudoku[row+1][col+1]] = true;
			finding_constraint[sudoku[row+1][col+2]] = true;
			finding_constraint[sudoku[row+2][col+1]] = true;
			finding_constraint[sudoku[row+2][col+2]] = true;
		}

		if (col%3 == 2) {
			finding_constraint[sudoku[row+1][col-1]] = true;
			finding_constraint[sudoku[row+1][col+1]] = true;
			finding_constraint[sudoku[row+2][col-1]] = true;
			finding_constraint[sudoku[row+2][col+1]] = true;
		}

		if (col%3 == 0) {
			finding_constraint[sudoku[row+1][col-1]] = true;
			finding_constraint[sudoku[row+1][col-2]] = true;
			finding_constraint[sudoku[row+2][col-1]] = true;
			finding_constraint[sudoku[row+2][col-2]] = true;
		}
	}

	if (row%3 == 2) {
		if (col%3 == 1) {
			finding_constraint[sudoku[row-1][col+1]] = true;
			finding_constraint[sudoku[row-1][col+2]] = true;
			finding_constraint[sudoku[row+1][col+1]] = true;
			finding_constraint[sudoku[row+1][col+2]] = true;
		}

		if (col%3 == 2) {
			finding_constraint[sudoku[row-1][col-1]] = true;
			finding_constraint[sudoku[row-1][col+1]] = true;
			finding_constraint[sudoku[row+1][col-1]] = true;
			finding_constraint[sudoku[row+1][col+1]] = true;
		}

		if (col%3 == 0) {
			finding_constraint[sudoku[row-1][col-1]] = true;
			finding_constraint[sudoku[row-1][col-2]] = true;
			finding_constraint[sudoku[row+1][col-1]] = true;
			finding_constraint[sudoku[row+1][col-2]] = true;
		}
	}

	if (row%3 == 0) {
		if (col%3 == 1) {
			finding_constraint[sudoku[row-1][col+1]] = true;
			finding_constraint[sudoku[row-1][col+2]] = true;
			finding_constraint[sudoku[row-2][col+1]] = true;
			finding_constraint[sudoku[row-2][col+2]] = true;
		}

		if (col%3 == 2) {
			finding_constraint[sudoku[row-1][col-1]] = true;
			finding_constraint[sudoku[row-1][col+1]] = true;
			finding_constraint[sudoku[row-2][col-1]] = true;
			finding_constraint[sudoku[row-2][col+1]] = true;
		}

		if (col%3 == 0) {
			finding_constraint[sudoku[row-1][col-1]] = true;
			finding_constraint[sudoku[row-1][col-2]] = true;
			finding_constraint[sudoku[row-2][col-1]] = true;
			finding_constraint[sudoku[row-2][col-2]] = true;
		}
	}
}


void Sudoku::setConsArray(int row, int col) {

	vector<int> c;
	for (int i = 1; i <=9; ++i) {
		if (sudoku[row][col] != 0) {
			c = {};
			break;
		}

		if (finding_constraint[i] == false) {
			c.push_back(i);
		}
	}
	cons[{row, col}] = c;
}

void Sudoku::setSudokuCell(int row, int col, int num) {
	sudoku[row][col] = num;

	for (int r = 1; r <= 9; r++) {
		/*cons[{r, col}].erase( remove( cons[{r, col}].begin(), cons[{r, col}].end(), num ),
				cons[{r, col}].end() );
				*/
		removecons(r, col, num);
	}

	for (int c = 1; c <= 9; c++) {
		/* cons[{row, c}].erase( remove( cons[{row, c}].begin(), cons[{row, c}].end(), num ),
				cons[{row, c}].end() );
				*/
		removecons(row, c, num);
	}

	int r[2];
	int c[2];

	switch(row%3) {
		case 0 : r[0] = row - 1;
				 r[1] = row - 2;
				 break;
		case 1 : r[0] = row + 1;
				 r[1] = row + 2;
				 break;
		case 2 : r[0] = row - 1;
				 r[1] = row + 1;
				 break;
	}

	switch(col%3) {
		case 0 : c[0] = col - 1;
				 c[1] = col - 2;
				 break;
		case 1 : c[0] = col + 1;
				 c[1] = col + 2;
				 break;
		case 2 : c[0] = col - 1;
				 c[1] = col + 1;
				 break;
	}

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			removecons(r[i], c[j], num);
		}
	}

}

void Sudoku::removecons(int row, int col, int num) {
	cons[{row, col}].erase( remove( cons[{row, col}].begin(), cons[{row, col}].end(), num ),
			cons[{row, col}].end() );
}

void Sudoku::rowpropogate(int row) {

	map<int, int> counter;
	map<int, int> cons_to_cell_mapper; // extra
	for (int i=1; i <= 9; i++) {
		counter[i] = 0;
		cons_to_cell_mapper[i] = 0;
	}

	for (int col=1; col <= 9; col++) {
		if (sudoku[row][col] == 0) {
			for (int i : cons[{row, col}]) {
				counter[i]++;
				if (counter[i] == 1) {
					cons_to_cell_mapper[i] = col;
				}
				else {
					cons_to_cell_mapper[i] = 0;
				}
			}
		}
	}


	for (int i=1; i <= 9; i++) {
		if (counter[i] == 1) {
			//cout << "(" << row << ", " << cons_to_cell_mapper[i] << "): " << i << endl;
			setSudokuCell(row, cons_to_cell_mapper[i],  i);
		}
	}

	/*
	map<int, int> counter;
	for (int i=1; i <=9; i++) {
		if (i != row) {
			counter[i] = 0;
		}
	}

	for (int i=1; i <= 9; i++) {
		if (i != row) {
			for (int j : cons[{i, col}]) {
				counter[j]++;
			}
		}

	}

	for (int i = 1; i <= 9; i++) {
		if (counter[i] == 1) {
			cout << i << " ";
		}
	}
	*/

	/*
	//set<int> x = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	set<int> x = {};

	for (int r = 1; r <= 9; r++) {
		for (int c=1; c <= 9; c++) {

			if (r != row && c != col) {
				for (int i : cons[{r, c}]) {
					x.insert(i);
				}
			}
		}
	}
	*/

}

void Sudoku::colpropogate(int col) {
	map<int, int> counter;
	map<int, int> cons_to_cell_mapper; // extra

	for (int i=1; i <= 9; i++) {
		counter[i] = 0;
		cons_to_cell_mapper[i] = 0; // extra
	}

	for (int row=1; row <= 9; row++) {
		if (sudoku[row][col] == 0) {
			for (int i : cons[{row, col}]) {
				counter[i]++;
				if (counter[i] == 1) {
					cons_to_cell_mapper[i] = row;
				}
				else {
					cons_to_cell_mapper[i] = 0;
				}
			}
		}
	}


	for (int i=1; i <= 9; i++) {
		if (counter[i] == 1) {
			//cout << "(" << cons_to_cell_mapper[i] << ", " << col << "): " << i << endl;
			setSudokuCell(cons_to_cell_mapper[i], col, i);

		}
	}
}

void Sudoku::cellpropogate(int cell) {

	map<int, int> counter;
	map<int, pair<int, int>> cons_to_cell_mapper; // extra

	for (int i=1; i <= 9; i++) {
		counter[i] = 0;
		cons_to_cell_mapper[i] = {0, 0}; // extra
	}


	int rowfactor = ((cell-1)/3) * 3;
	int colfactor = ((cell-1)%3) * 3;

	for (int row = 1 + rowfactor; row <= 3 + rowfactor; row++) {
		for (int col = 1 + colfactor; col <= 3 + colfactor; col++) {
			if (sudoku[row][col] == 0) {

				for (int i : cons[{row, col}]) {
					counter[i]++;
					if (counter[i] == 1) {
						cons_to_cell_mapper[i] = {row, col};
					}
					else {
						cons_to_cell_mapper[i] = {0, 0};
					}
				}


			}

		}
	}

	for (int i=1; i <= 9; i++) {
		if (counter[i] == 1) {
			//cout << "(" << cons_to_cell_mapper[i].first << ", "
			//		<< cons_to_cell_mapper[i].second << "): " << i << endl;
			setSudokuCell(cons_to_cell_mapper[i].first, cons_to_cell_mapper[i].second, i);


		}
	}
}


void Sudoku::printSudoku() {
	for (int row = 1; row <= 9; row++) {
		for (int col = 1; col <= 9; col++) {
			cout << sudoku[row][col] << " ";
			if (col == 3 || col == 6) {
				cout << "| ";
			}
		}
		if (row == 3 || row == 6) {
			cout << "\n---------------------";
		}
		cout << endl;

	}
}
