//***************************************************
// Filename: driver.cpp
//
// Author: Kyle Jacobson
//***************************************************

#include <iostream>
using namespace std;

#include "life.hpp"

int main(int argc, char** argv) {
	// The program requires a file name to start.
	if (argc != 2) {
		cout << ("\nWARNING: This program requires a filename as the second argument.\n");
		cout << ("Usable .gol files are included in the project folder.\n\n");
		cout << ("Example Command: ./driver glider.gol\n\n");
		exit(EXIT_FAILURE);
	}

	// Assigns variables that will be used interacting with grid.
    int rows, cols;
    char **grid, **mutatedGrid, *str;

	// Load the grid from the file.
    grid = loadGridFromFile(argv[1],&rows,&cols);
    str = toString(rows,cols,grid);
    std::cout << "\n" << str;
    free(str);

	// Provides instructions on how to operate the program.
    while (true) {
		// Options are displayed to the user each time the program runs.
		cout << ("\nPress N to choose number of iterations.\n");
		cout << ("Press S to save to data to a specified file.\n");
		cout << ("Press Q to quit the Game of Life program.\n");
		cout << ("\nPress any other key to move to next generation: ");
		
		// Creates an array of chars for user inputs.
		char input[5];
		fgets(input,5,stdin);

		// Switch accepts the input provided by the user and acts accordingly.
        switch(input[0]) {
			// Free memory and exit the game.
            case 'q':
			case 'Q':
				free(grid);
				return 0;
			
			// Stores the grid values in a specified text file.
            case 's':
			case 'S':
				// Ask the user to specify the name of the saved file.
				cout << ("Enter a filename: ");
				char filename[254];
				fgets(filename,254,stdin);

				// Replace newline character with string terminator character.
				filename[strlen(filename)-1] = '\0';
                saveGridToFile(filename,rows,cols,grid);
				cout << "\nGrid data saved to " << filename << ".\n";
                break;

			// Inquires the user to specify an iteration value and iterates the grid.
            case 'n':
			case 'N':
				// Ask the user to specify the number of grid iterations.
				cout << ("How many iterations: ");
				char buf[5];
				fgets(buf,5,stdin);

                // Replace newline character with string terminator character.
				buf[strlen(buf)-1] = '\0';
				
				int num; 
				num = atoi(buf);

				// Displays the approriate message based on user input.
				if(num <= 0)
					cout << "\nYou cannot iterate 0 or less times.\n";
				else if(num == 1)
					cout << "\nIterating " << num << " time.\n";
				else
					cout << "\nIterating " << num << " times.\n";

				// If the input is acceptable, mutate the grid the specified amount of times.
				for(int i = 0; i < num; ++i) {
					mutatedGrid = mutateGrid(rows,cols,grid);
					str = toString(rows,cols,mutatedGrid);
                    cout << "\n" << str;
                    free(str);
                    free(grid);
                    grid = mutatedGrid;
				}
				break;

			// Whenever any other key is pressed, mutate the grid one time.
            default:
				mutatedGrid = mutateGrid(rows,cols,grid);
				str = toString(rows,cols,mutatedGrid);
                cout << "\n" << str;
                free(str);
                free(grid);
                grid = mutatedGrid;
        }
    }

    return EXIT_SUCCESS;
}