/*
 * main.cpp
 *
 *  Created on: Jun 21, 2018
 *      Author: naing
 */

#include <iostream>

#include "Sudoku.h"
using namespace std;

int main() {

    int upper_bound = 10; // replace with any desired number of iterations
	for (int c = 1; c <= upper_bound; c++) {
		//cout << c << ": " << endl;

		for (int row = 1; row <= 9; ++row) {
			for (int col = 1; col <= 9; ++col) {
				Sudoku t(row, col);

				//cout << row << " " << col << ": ";

				if (t.sudoku[row][col] != 0 || row == 0 || col == 0) {
					//cout << "filled ";

				}

				else {
					if (t.cons[{row, col}].size() == 1) {
						t.setSudokuCell(row, col, t.cons[{row, col}][0]);
						//cout << t.cons[{row, col}][0] << " (lone cons) ";
					}
					/*
					else {
						for (int i : t.cons[{row, col}]) {
							cout << i << " ";
						}
					} */
				}

				//cout << endl;

			}
		}

		Sudoku test;
		if (c == 1) {
		    cout << "PUZZLE: " << endl;
		    test.printSudoku();
		    cout << endl;
		}

		//cout << endl;
		//cout << "ROW PROPOGATE: " << endl;
		for (int row=1; row<=9; row++) {
			test.rowpropogate(row);
		}
		//cout << endl;

		//cout << "COL PROPOGATE: " << endl;
		for (int col=1; col<=9; col++) {
			test.colpropogate(col);
		}
		//cout << endl;

		//cout << "CELL PROPOGATE: " << endl;
		for (int cell=1; cell<=9; cell++) {
			test.cellpropogate(cell);
		}
		//cout << endl;


		if (c == upper_bound) {
		    cout << "SOLUTION: ";

		    cout << endl;
		    test.printSudoku();
		    cout << endl;
		}
		//cout << endl;
	}

}


