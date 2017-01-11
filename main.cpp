#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>

using namespace std;

//Global Constants
const int COLUMNS = 20;
const int ROWS = 20;
const int OFFSET_FACTOR = 1;

void initializeHotPlate(double array[][COLUMNS], int ROWS)
{
	const double TOP_BOTTOM_INITIAL_VALUE = 100.0;
	const double LEFT_RIGHT_MIDDLE_INITIAL_VALUE = 0.0;
	int secondRow = 1;

	//First row of initialized array
	for (int firstRow = 0; firstRow < secondRow; firstRow++)
	{
		for (int firstColumn = 0; firstColumn < 1; firstColumn++)
		{
			array[firstRow][firstColumn] = LEFT_RIGHT_MIDDLE_INITIAL_VALUE;
		}
		for (int middleColumns = 1; middleColumns < COLUMNS; middleColumns++)
		{
			array[firstRow][middleColumns] = TOP_BOTTOM_INITIAL_VALUE;
		}
		for (int lastColumn = 19; lastColumn < COLUMNS; lastColumn++)
		{
			array[firstRow][lastColumn] = LEFT_RIGHT_MIDDLE_INITIAL_VALUE;
		}
	}

	//Middle 18 rows of initialized array
	for (int middleRows = 1; middleRows < (ROWS - OFFSET_FACTOR); middleRows++)
	{
		for (int middleColumns = 0; middleColumns < COLUMNS; middleColumns++)
		{
			array[middleRows][middleColumns] = LEFT_RIGHT_MIDDLE_INITIAL_VALUE;
		}
	}

	//Last row of initialized array
	for (int lastRow = 19; lastRow < ROWS; lastRow++)
	{
		for (int firstColumn = 0; firstColumn < 1; firstColumn++)
		{
			array[lastRow][firstColumn] = LEFT_RIGHT_MIDDLE_INITIAL_VALUE;
		}
		for (int middleColumns = 1; middleColumns < COLUMNS; middleColumns++)
		{
			array[lastRow][middleColumns] = TOP_BOTTOM_INITIAL_VALUE;
		}
		for (int lastColumn = 19; lastColumn < COLUMNS; lastColumn++)
		{
			array[lastRow][lastColumn] = LEFT_RIGHT_MIDDLE_INITIAL_VALUE;
		}
	}
}

void printHotPlate(double array[][COLUMNS], int ROWS)
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int column = 0; column < COLUMNS; column++)
		{
			cout << fixed << setprecision(2) << array[row][column] << " ";
		}
		cout << "\n";
	}
	cout << endl;
}

void passToNewArray(double array[][COLUMNS], double new_array[][COLUMNS], int ROWS)
{
	for (int firstColumn = 0; firstColumn < COLUMNS; firstColumn++)
	{
		for (int firstRow = 0; firstRow < ROWS; firstRow++)
		{
			new_array[firstRow][firstColumn] = array[firstRow][firstColumn];
		}
	}
}

void calculateAverageFourNeighbors(double old_array[][COLUMNS], double new_array[][COLUMNS], int row, int column)
{
	const int NUMBER_OF_NEIGHBORS = 4;

	new_array[row][column] = (((old_array[row][column - OFFSET_FACTOR]) + (old_array[row + OFFSET_FACTOR][column]) + (old_array[row][column + OFFSET_FACTOR]) + (old_array[row - OFFSET_FACTOR][column])) / NUMBER_OF_NEIGHBORS);
}

void averageFourNeighbors(double old_array[][COLUMNS], double new_array[][COLUMNS], int ROWS)
{
	for (int row = 1; row < (ROWS - OFFSET_FACTOR); row++)
	{
		for (int column = 1; column < (COLUMNS - OFFSET_FACTOR); column++)
		{
			calculateAverageFourNeighbors(old_array, new_array, row, column);
		}
	}
}

void averageHotPlate(double old_array[][COLUMNS], double new_array[][COLUMNS], int ROWS)
{
	passToNewArray(old_array, new_array, ROWS);

	averageFourNeighbors(old_array, new_array, ROWS);
}

int checkIterationChange(double array[][COLUMNS], double new_array[][COLUMNS], int ROWS)
{
	const double PRECISION_FACTOR = 0.1;
	int value;
	int addition;

	value = 0;

	for (int row = 1; row < (ROWS - OFFSET_FACTOR); row++)
	{
		for (int column = 1; column < (COLUMNS - OFFSET_FACTOR); column++)
		{
			if (abs(new_array[row][column] - array[row][column]) > PRECISION_FACTOR)
			{
				addition = 1;
				value = value + addition;
			}
			else
			{
				addition = 0;
				value = value + addition;
			}
		}
	}
	return value;
}

void exportHotPlate(double array[][COLUMNS], int ROWS)
{
	ofstream out_file;
	out_file.open("lab6output.csv");
	for (int row = 0; row < ROWS; row++)
	{
		for (int column = 0; column < COLUMNS; column++)
		{
			out_file << fixed << setprecision(2) << array[row][column] << ",";
		}
		out_file << "\n";
	}
	out_file << endl;

	out_file.close();
}

int main()
{
	double old_values_array[ROWS][COLUMNS];
	double new_values_array[ROWS][COLUMNS];

	//Part 1 - Initialize array and print it out
	initializeHotPlate(old_values_array, ROWS);
	printHotPlate(old_values_array, ROWS);

	//Part 2 - Calculate and print out first iteration
	averageHotPlate(old_values_array, new_values_array, ROWS);
	passToNewArray(new_values_array, old_values_array, ROWS);
	printHotPlate(new_values_array, ROWS);

	//Part 3 - Iterate until the hot plate is stable
	int checkDifference;
	do
	{
		averageHotPlate(old_values_array, new_values_array, ROWS);
		checkDifference = checkIterationChange(new_values_array, old_values_array, ROWS);
		passToNewArray(new_values_array, old_values_array, ROWS);
	} while (checkDifference > 0);

	//Export data to lab6output.csv
	exportHotPlate(new_values_array, ROWS);

	std::system("pause");
	return 0;
}