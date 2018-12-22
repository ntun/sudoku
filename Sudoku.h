/*
 * Sudoku.h
 *
 *  Created on: Jun 21, 2018
 *      Author: naing
 */


#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <map>
using namespace std;

#ifndef SUDOKU_H_
#define SUDOKU_H_

class Sudoku {
public:
	Sudoku(int=0, int=0);
	~Sudoku();

	void rowconstraint(int row);
	void colconstraint(int col);
	void constraint(int row, int col);
	void resetConstraint();

	void rowpropogate(int);
	void colpropogate(int);
	void cellpropogate(int);
	static void removecons(int, int, int);

	void setConsArray(int, int);
	static void setSudokuCell(int, int, int);


	void printSudoku();

	static constexpr int size = 10;
	static int sudoku[10][10];
	bool finding_constraint[size+1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

	vector< pair< pair<int, int>, int > > newKB;

	static map< pair<int, int>, vector<int>> cons;

	// new stuffs
	static map< vector<int>, vector< pair<int, int> > > cons_to_block;
};




#endif /* SUDOKU_H_ */
