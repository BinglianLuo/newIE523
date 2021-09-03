// Soduku Solver using Brute-Force Search implemted using 
// recursion.
// Written for IE523: Financial Computation by Prof. Sreenivas
// and GE523: Discrete Event Systems
//
#include <iostream>
#include "sudoku.h"

int main (int argc, char * const argv[]) //
{
	Sudoku x;
    cout << "Input File name: " << argv[1] << endl;
	x.read_puzzle(argc, argv); //
	x.print_puzzle();
	// x.Solve(0,0); // find ONE solution function
    x.alternate_Solve(0, 0); // fine ALL solutions function
	// x.print_puzzle();

	
    return 0;
}
