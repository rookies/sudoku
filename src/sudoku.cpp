/*
 * sudoku.cpp
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
 * 
 */
#include "sudoku.hpp"
#undef DEBUG

Sudoku::Sudoku() : m_solved(false), m_filled(false)
{
	
}
Sudoku::~Sudoku()
{

}
void Sudoku::fill(unsigned int values[81])
{
	/*
	 * Variable declarations:
	*/
	int i;
	/*
	 * Fill:
	*/
	for (i=0; i < 81; i++)
	{
		m_fields[i].set_solution(values[i]);
	}
}
bool Sudoku::solve(void)
{
	/*
	 * Variable declarations:
	*/
	bool failed = false;
	int i, j;
	/*
	 * Fill suggestions:
	*/
	while (!failed)
	{
		fill_suggestions();
		dump();
		dump_suggestions();
		failed = true;
		for (i=0; i < 81; i++)
		{
			if (m_fields[i].get_suggestions_count() == 1 && m_fields[i].get_solution() == 0)
			{
				for (j=0; j < 9; j++)
				{
					if (m_fields[i].get_suggestions()[j] != 0)
					{
						m_fields[i].set_solution(m_fields[i].get_suggestions()[j]);
						m_fields[i].rm_suggestion(m_fields[i].get_suggestions()[j]);
						failed = false;
						break;
					};
				}
			};
		}
	}
	return true;
}
void Sudoku::fill_suggestions(void)
{
	/*
	 * Variable declarations:
	*/
	int i, j, k, l;
	/*
	 * Run through fields:
	*/
	for (i=0; i < 81; i++)
	{
		if (m_fields[i].get_solution() == 0)
		{
			/*
			 * Field is not filled!
			*/
			//std::cout << "Block number: " << std::endl;
			/*
			 * Run through numbers:
			*/
			for (j=1; j <= 9; j++)
			{
				/*
				 * Run through the row:
				 * row_number = i/9
				 * range = (i/9)*9 ... ((i/9)*9)+8
				*/
				for (k=(i/9)*9; k < ((i/9)*9)+9; k++)
				{
					if (m_fields[k].get_solution() == j)
					{
#ifdef DEBUG
						std::cout << "rm@row " << i << " " << j << std::endl;
#endif // DEBUG
						m_fields[i].rm_suggestion(j);
					}
				}
				/*
				 * Run through the column:
				 * column_number = i-((i/9)*9)
				*/
				for (k=i-((i/9)*9); k < (i-((i/9)*9))+(8*9); k += 9)
				{
					if (m_fields[k].get_solution() == j)
					{
#ifdef DEBUG
						std::cout << "rm@column " << i << " " << j << std::endl;
#endif // DEBUG
						m_fields[i].rm_suggestion(j);
					}
				}
				/*
				 * Run through the block:
				 * x_block_nr = (i-((i/9)*9))/3
				 * y_block_nr = (i/9)/3
				 * 
				 * ... in x direction:
				*/
				for (k=((i-((i/9)*9))/3)*3; k < (((i-((i/9)*9))/3)*3)+3; k++)
				{
					/*
					 * ... and in y direction:
					*/
					for (l=((i/9)/3)*3; l < ((i/9)/3)+3; l++)
					{
						if (m_fields[(l*9)+k].get_solution() == j)
						{
#ifdef DEBUG
							std::cout << "rm@block " << i << " " << j << std::endl;
#endif // DEBUG
							m_fields[i].rm_suggestion(j);
						}
					}
				}
			}
		}
	}
}
void Sudoku::dump(void)
{
	int i;
	std::cout << "===================" << std::endl;
	for (i=0; i < 81; i += 9)
	{
		std::cout << "|" << m_fields[i].get_solution_showable() << "|";
		std::cout << m_fields[i+1].get_solution_showable() << "|";
		std::cout << m_fields[i+2].get_solution_showable() << "|";
		std::cout << m_fields[i+3].get_solution_showable() << "|";
		std::cout << m_fields[i+4].get_solution_showable() << "|";
		std::cout << m_fields[i+5].get_solution_showable() << "|";
		std::cout << m_fields[i+6].get_solution_showable() << "|";
		std::cout << m_fields[i+7].get_solution_showable() << "|";
		std::cout << m_fields[i+8].get_solution_showable() << "|" << std::endl;
	}
	std::cout << "===================" << std::endl;
}
void Sudoku::dump_suggestions(void)
{
	int i, j;
	for (i=0; i < 81; i++)
	{
		if (m_fields[i].get_solution() == 0)
		{
			std::cout << "Suggestions for #" << i << ": ";
			for (j=0; j < 9; j++)
			{
				if (m_fields[i].get_suggestions()[j] != 0)
					std::cout << m_fields[i].get_suggestions()[j] << " ";
			}
			std::cout << std::endl;
		};
	}
}
void Sudoku::refill_suggestions(unsigned int field, unsigned int value)
{

}
