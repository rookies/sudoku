/*
 * main.cpp
 * 
 * Copyright 2012 Robert Knauer <robert@privatdemail.net>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * g++ -std=c++11 -o sudoku-solve src/*.cpp
 */
#include <iostream>
#include <fstream>
#include "sudoku.hpp"

int main (int argc, char **argv)
{
	/*
	 * Variable declarations:
	*/
	Sudoku sudoku;
	int i, j;
	unsigned int values[81];
	std::ifstream file;
	std::string line;
	/*
	 * Read sudoku from file:
	*/
	if (argc < 2)
	{
		std::cerr << "Usage: " << argv[0] << " file" << std::endl;
		return 1;
	};
	file.open(argv[1], std::ios::in);
	if (!file.is_open())
	{
		std::cerr << argv[1] << ": Failed to open sudoku." << std::endl;
		return 1;
	};
	for (i=0; i < 9; i++)
	{
		getline(file, line);
		for (j=0; j < 9; j++)
		{
			values[(i*9+j)] = atoi(line.substr(j, 1).c_str());
		}
	}
	file.close();
	/*
	 * Fill:
	*/
	sudoku.fill(values);
	/*
	 * Solve:
	*/
	sudoku.solve();
	return 0;
}
