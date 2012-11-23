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
#include "sudoku.hpp"

int main (int argc, char **argv)
{
	/*
	 * Variable declarations:
	*/
	Sudoku sudoku;
	// RELATIV SCHWER:
	/*unsigned int values[81] = {
		1,0,3,0,0,5,0,4,0,
		0,4,0,9,2,8,6,0,1,
		0,6,8,3,0,0,2,0,0,
		0,5,0,6,3,0,0,0,0,
		0,0,0,1,0,2,0,0,0,
		0,0,6,0,0,0,9,7,0,
		8,0,0,0,9,0,4,0,0,
		0,7,0,4,8,6,0,0,5,
		0,0,0,0,0,0,0,0,0
	};*/
	// SEHR EINFACH:
	unsigned int values[81] = {
		6,5,1,2,0,4,3,0,7,
		4,7,3,0,9,6,0,0,8,
		2,0,8,5,3,7,1,6,4,
		7,4,9,8,6,3,2,1,5,
		3,2,6,7,5,1,4,8,9,
		8,1,5,0,2,9,7,0,6,
		0,8,7,0,4,2,6,0,0,
		0,6,4,3,1,0,9,7,2,
		9,3,2,6,7,5,0,4,0
	};
	/*
	 * Fill:
	*/
	sudoku.fill(values);
	sudoku.solve();
	return 0;
}
