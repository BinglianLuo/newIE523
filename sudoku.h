/*
 *  sudoku.h
 *  Sudoku
 *  Created by Prof. Ramavarapu Sreenivas 
 *  Inspired by: http://web.eecs.utk.edu/courses/spring2012/cs140/Notes/Sudoku/index.html
*/

#ifndef sudoku
#define sudoku

#include <vector>
#include <fstream>
#include <math.h>



using std::vector;
using namespace std;
class Sudoku 
{ 
	// Private
	int puzzle[9][9];
    int number_of_solutions = 0; // for all solutions
	
	// Private member function that checks if the named row is valid
	bool row_valid(int row)
	{
		// write code that checks if "row" is valid
        for (int i = 1; i < 9; i++){
            for (int j = 0; j < i; j++){
                if ((puzzle[row][i]>=1) && (puzzle[row][j]>=1) && (puzzle[row][i]==puzzle[row][j])){
                    return false;
                }
            }
        }
        return true;
	}
	
	// Private member function that checks if the named column is valid
	bool col_valid(int col)
	{
		// check validity of "col"
        for (int i = 1; i < 9; i++){
            for (int j = 0; j < i; j++){
                if ((puzzle[i][col]>=1) && (puzzle[j][col]>=1) && (puzzle[i][col]==puzzle[j][col])){
                    return false;
                }
            }
        }
        return true;
	}
	
	// Private member function that checks if the named 3x3 block is valid
	bool block_valid(int row, int col)
	{
		// check 3 x 3 block validity
        // Step 1, find the block in which [row,col] is located, and then put the factors into a vector
        int a = floor(row/3);
        int b = floor(col/3);
        vector <int> P;
        for (int i = 0; i <= 2; i++){
            for (int j = 0; j <= 2; j++){
                if (puzzle[3*a+i][3*b+j] >= 1){
                    P.push_back(puzzle[3*a+i][3*b+j]);
                }
            }
        }
        // Step2, check the validity of vector P
        vector <int> pos(9,0);
        for (int i = 0; i < P.size(); i++){
            pos[P[i]-1]++;
            if (pos[P[i]-1]==2){
                return false;
            }
        }
        return true;
	}
	
public:
	// Public member function that reads the incomplete puzzle
	// we are not doing any checks on the input puzzle -- that is,
	// we are assuming they are indeed valid
	void read_puzzle(int argc, char * const argv[]) //
	{
		// write code that reads the input puzzle using the 
		// guidelines of figure 23 of the bootcamp material
        //double value_input;
        //vector <double> P;

        ifstream input_file(argv[1]);
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                input_file >> puzzle[i][j];
            }
        }
	}
	
	// Public member function that prints the puzzle when called

    void print_puzzle()
	{
		std::cout << "Board Position" << std::endl;
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				// check if we have a legitimate integer between 1 and 9
				if ((puzzle[i][j] >= 1) && (puzzle[i][j] <= 9))
				{
					// printing initial value of the puzzle with some formatting
					std::cout << puzzle[i][j] << " ";
				}
				else {
					// printing initial value of the puzzle with some formatting
					std::cout << "X ";
				}
			}
			std::cout << std::endl;
		}
	}

	// Public member function that (recursively) implements the brute-force 
	// search for possible solutions to the incomplete Sudoku puzzle
	bool Solve(int row, int col) // Find ONE Solution Function
	{
		// this part of the code identifies the row and col number of the 
		// first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
		// no zeros, the variable row will be 9 => the puzzle is done, as 
		// each entry is row-, col- and block-valid...
		
		// use the pseudo code of figure 3 of the description
        
        // Step 1, locate the first 0 in the puzzle, and record the row & col of this zero
        int flag = 0;
        int row_loc = 0, col_loc = 0;
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9 ; j++){
                if (puzzle[i][j] == 0){
                    flag = 1;
                    row_loc = i;
                    col_loc = j;
                    break;
                }
            }
            if (flag == 1){
                break; // Jump out of the loop, because we only need to find the FISRT 0
            }
        }
        
        if (flag == 0){
            std::cout << endl << "Final Solution" << endl;
            print_puzzle();
            return true;
        }
        
        else
        {
            for (int k = 1; k <= 9; k++){
                puzzle[row_loc][col_loc] = k;
               // std::cout << puzzle[row_loc][col_loc];
               // std::cout << row_valid(row_loc) << col_valid(col_loc) << block_valid(row_loc,col_loc) << endl;
                if (row_valid(row_loc) && col_valid(col_loc) && block_valid(row_loc,col_loc) && Solve(row_loc,col_loc)){
                    return true;
                    
                }
                else
                    puzzle[row_loc][col_loc] = 0;
            }
        }
        return false;
	}

    bool alternate_Solve(int row, int col) // Find ALL Solution Function
    {
        // this part of the code identifies the row and col number of the
        // first incomplete (i.e. 0) entry in the puzzle.  If the puzzle has
        // no zeros, the variable row will be 9 => the puzzle is done, as
        // each entry is row-, col- and block-valid...
        
        // use the pseudo code of figure 3 of the description
        
        // Step 1, locate the first 0 in the puzzle, and record the row & col of this zero
        int flag = 0;
        int row_loc = 0, col_loc = 0;
        for (int i = 0; i < 9; i++){
            for (int j = 0; j < 9 ; j++){
                if (puzzle[i][j] == 0){
                    flag = 1;
                    row_loc = i;
                    col_loc = j;
                    break;
                }
            }
            if (flag == 1){
                break; // Jump out of the loop, because we only need to find the FISRT 0
            }
        }
        
        if (flag == 0){
            number_of_solutions++;
            std::cout << endl << "Solution #" << number_of_solutions << endl;
            print_puzzle();
        }
        
        else
        {
            bool found_at_least_one_solution = false;
            for (int k = 1; k <= 9; k++){
                puzzle[row_loc][col_loc] = k;
               // std::cout << puzzle[row_loc][col_loc];
               // std::cout << row_valid(row_loc) << col_valid(col_loc) << block_valid(row_loc,col_loc) << endl;
                if (row_valid(row_loc) && col_valid(col_loc) && block_valid(row_loc,col_loc) && alternate_Solve(row_loc,col_loc)){
                    found_at_least_one_solution = true;
                }
                else
                    puzzle[row_loc][col_loc] = 0;
            }
        }
        return false;
    }





};



#endif
