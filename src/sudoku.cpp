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

Sudoku::Sudoku() : m_stats_step1(0), m_stats_step2(0), m_stats_step3(0)
{
	int i;
	/*
	 * Init checked suggestions:
	*/
	for (i=0; i < 729; i++)
	{
		m_checked_suggestions[i].field = -1;
		m_checked_suggestions[i].suggestion = -1;
	}
	for (i=0; i < 729; i++)
	{
		m_checked_suggestions_step3[i].field = -1;
		m_checked_suggestions_step3[i].suggestion = -1;
	}
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
	 * STEP #1 // Fill suggestions:
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
		m_stats_step1++;
	}
	/*
	 * Check if we solved the sudoku:
	*/
	if (is_solved())
	{
		std::cout << "SOLVED after Step#1 (Fill suggestions)" << std::endl;
		stats();
		return true;
	};
	/*
	 * STEP #2 // Try one number:
	*/
	while (try_numbers())
	{
		/*
		 * Fill suggestions:
		*/
		failed = false;
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
		if (is_solved())
		{
			std::cout << "SOLVED after Step#2 (Try one number)" << std::endl;
			stats();
			return true;
		};
		/*
		 * Restore fields:
		*/
		for (i=0; i < 81; i++)
			m_fields[i] = m_fields_bak[i];
		m_stats_step2++;
	}
	if (is_solved())
	{
		std::cout << "SOLVED after Step#2 (Try one number)" << std::endl;
		stats();
		return true;
	};
	/*
	 * STEP #3 // Try two numbers:
	*/
	for (i=0; i < 729; i++)
	{
		m_checked_suggestions[i].field = -1;
		m_checked_suggestions[i].suggestion = -1;
	}
	while (try_numbers())
	{
		/*
		 * Fill suggestions:
		*/
		failed = false;
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
		while (try_numbers_step3())
		{
			/*
			 * Fill suggestions:
			*/
			failed = false;
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
			if (is_solved())
			{
				std::cout << "SOLVED after Step#3 (Try two numbers)" << std::endl;
				stats();
				return true;
			};
			/*
			 * Restore fields:
			*/
			for (i=0; i < 81; i++)
				m_fields[i] = m_fields_bak2[i];
			m_stats_step3++;
		}
		/*
		 * Clear checked suggestions:
		*/
		for (i=0; i < 729; i++)
		{
			m_checked_suggestions_step3[i].field = -1;
			m_checked_suggestions_step3[i].suggestion = -1;
		}
		/*
		 * Restore fields:
		*/
		for (i=0; i < 81; i++)
			m_fields[i] = m_fields_bak[i];
	}
	if (is_solved())
	{
		std::cout << "SOLVED after Step#3 (Try two numbers)" << std::endl;
		stats();
		return true;
	};
	std::cout << "SOLVE FAILED (no success with trying two numbers)" << std::endl;
	stats();
	return false;
}
void Sudoku::stats(void)
{
	std::cout << "== STATS ==" << std::endl;
	std::cout << "Rounds Step#1: " << m_stats_step1 << std::endl;
	std::cout << "Rounds Step#2: " << m_stats_step2 << std::endl;
	std::cout << "Rounds Step#3: " << m_stats_step3 << std::endl;
}
bool Sudoku::is_solved(void)
{
	int i;
	/*
	 * Check fields:
	*/
	for (i=0; i < 81; i++)
	{
		if (m_fields[i].get_solution() == 0)
			return false;
	}
	return true;
}
void Sudoku::fill_suggestions(void)
{
	/*
	 * Variable declarations:
	*/
	int i, j, k, l;
	int blockfields[9];
	/*
	 * Run through fields:
	*/
	for (i=0; i < 81; i++)
	{
		if (m_fields[i].get_solution() == 0)
		{
			/*
			 * Field is not filled!
			 * Run through numbers:
			*/
			for (j=1; j <= 9; j++)
			{
				/*
				 * Run through the row:
				 * row_number = i/9
				 * range = (i/9)*9 ... ((i/9)*9)+8
				*/
				for (k=(i/9)*9; k <= ((i/9)*9)+8; k++)
				{
					if (m_fields[k].get_solution() == j)
					{
#ifdef DEBUG
						std::cout << "rm@row " << i << " " << j << std::endl;
#endif // DEBUG
						m_fields[i].rm_suggestion(j);
					};
				}
				/*
				 * Run through the column:
				 * column_number = i-((i/9)*9)
				*/
				for (k=i-((i/9)*9); k <= (i-((i/9)*9))+(8*9); k += 9)
				{
					if (m_fields[k].get_solution() == j)
					{
#ifdef DEBUG
						std::cout << "rm@column " << i << " " << j << std::endl;
#endif // DEBUG
						m_fields[i].rm_suggestion(j);
					};
				}
				/*
				 * Run through the block:
				*/
				get_blockfields(i, blockfields);
				for (k=0; k < 9; k++)
				{
					if (m_fields[(blockfields[k])].get_solution() == j)
					{
#ifdef DEBUG
						std::cout << "rm@block " << (blockfields[k]) << " " << j << std::endl;
#endif // DEBUG
						m_fields[i].rm_suggestion(j);
					};
				}
			}
		}
	}
}
void Sudoku::get_blockfields(int field, int *blockfields)
{
	if ((field >= 0 && field <= 2) || (field >= 9 && field <= 11) || (field >= 18 && field <= 20))
	{
		blockfields[0] = 0;
		blockfields[1] = 1;
		blockfields[2] = 2;
		blockfields[3] = 9;
		blockfields[4] = 10;
		blockfields[5] = 11;
		blockfields[6] = 18;
		blockfields[7] = 19;
		blockfields[8] = 20;
	}
	else if ((field >= 3 && field <= 5) || (field >= 12 && field <= 14) || (field >= 21 && field <= 23))
	{
		blockfields[0] = 3;
		blockfields[1] = 4;
		blockfields[2] = 5;
		blockfields[3] = 12;
		blockfields[4] = 13;
		blockfields[5] = 14;
		blockfields[6] = 21;
		blockfields[7] = 22;
		blockfields[8] = 23;
	}
	else if ((field >= 6 && field <= 8) || (field >= 15 && field <= 17) || (field >= 24 && field <= 26))
	{
		blockfields[0] = 6;
		blockfields[1] = 7;
		blockfields[2] = 8;
		blockfields[3] = 15;
		blockfields[4] = 16;
		blockfields[5] = 17;
		blockfields[6] = 24;
		blockfields[7] = 25;
		blockfields[8] = 26;
	}
	else if ((field >= 27 && field <= 29) || (field >= 36 && field <= 38) || (field >= 45 && field <= 47))
	{
		blockfields[0] = 27;
		blockfields[1] = 28;
		blockfields[2] = 29;
		blockfields[3] = 36;
		blockfields[4] = 37;
		blockfields[5] = 38;
		blockfields[6] = 45;
		blockfields[7] = 46;
		blockfields[8] = 47;
	}
	else if ((field >= 30 && field <= 32) || (field >= 39 && field <= 41) || (field >= 48 && field <= 50))
	{
		blockfields[0] = 30;
		blockfields[1] = 31;
		blockfields[2] = 32;
		blockfields[3] = 39;
		blockfields[4] = 40;
		blockfields[5] = 41;
		blockfields[6] = 48;
		blockfields[7] = 49;
		blockfields[8] = 50;
	}
	else if ((field >= 33 && field <= 35) || (field >= 42 && field <= 44) || (field >= 51 && field <= 53))
	{
		blockfields[0] = 33;
		blockfields[1] = 34;
		blockfields[2] = 35;
		blockfields[3] = 42;
		blockfields[4] = 43;
		blockfields[5] = 44;
		blockfields[6] = 51;
		blockfields[7] = 52;
		blockfields[8] = 53;
	}
	else if ((field >= 54 && field <= 56) || (field >= 63 && field <= 65) || (field >= 72 && field <= 74))
	{
		blockfields[0] = 54;
		blockfields[1] = 55;
		blockfields[2] = 56;
		blockfields[3] = 63;
		blockfields[4] = 64;
		blockfields[5] = 65;
		blockfields[6] = 72;
		blockfields[7] = 73;
		blockfields[8] = 74;
	}
	else if ((field >= 57 && field <= 59) || (field >= 66 && field <= 68) || (field >= 75 && field <= 77))
	{
		blockfields[0] = 57;
		blockfields[1] = 58;
		blockfields[2] = 59;
		blockfields[3] = 66;
		blockfields[4] = 67;
		blockfields[5] = 68;
		blockfields[6] = 75;
		blockfields[7] = 76;
		blockfields[8] = 77;
	}
	else if ((field >= 60 && field <= 62) || (field >= 69 && field <= 71) || (field >= 78 && field <= 80))
	{
		blockfields[0] = 60;
		blockfields[1] = 61;
		blockfields[2] = 62;
		blockfields[3] = 69;
		blockfields[4] = 70;
		blockfields[5] = 71;
		blockfields[6] = 78;
		blockfields[7] = 79;
		blockfields[8] = 80;
	};
}
bool Sudoku::try_numbers(void)
{
	int i, j;
	int result = -1;
	int suggestion;
	int suggnr;
	/*
	 * Backup fields:
	*/
	for (i=0; i < 81; i++)
		m_fields_bak[i] = m_fields[i];
	/*
	 * Run through fields:
	*/
	for (i=0; i < 81; i++)
	{
		suggestion = -1;
		if (m_fields[i].get_suggestions_count() > 2 && m_fields[i].get_solution() == 0)
		{
			/*
			 * Get the suggestion:
			*/
			for (j=0; j < 9; j++)
			{
				if (m_fields[i].get_suggestions()[j] != 0)
				{
					if (!is_suggestion_already_checked(i, m_fields[i].get_suggestions()[j]))
					{
						suggestion = m_fields[i].get_suggestions()[j];
						break;
					};
				};
			}
		};
		if (suggestion != -1)
		{
			result = i;
			break;
		};
	}
	if (result == -1)
	{
		return false;
	}
	else
	{
		/*
		 * Mark it as checked:
		*/
		for (i=0; i < 729; i++)
		{
			if (m_checked_suggestions[i].field == -1)
			{
				suggnr = i;
				break;
			};
		}
		m_checked_suggestions[suggnr].field = result;
		m_checked_suggestions[suggnr].suggestion = suggestion;
		/*
		 * ... and set the solution to it:
		*/
		m_fields[result].set_solution(suggestion);
		std::cout << "===== Trying " << suggestion << " in " << result << " =====" << std::endl;
		return true;
	};
}
bool Sudoku::is_suggestion_already_checked(int field, int suggestion)
{
	int i;
	for (i=0; i < 729; i++)
	{
		if (m_checked_suggestions[i].field == field && m_checked_suggestions[i].suggestion == suggestion)
			return true;
	}
	return false;
}
bool Sudoku::try_numbers_step3(void)
{
	int i, j;
	int result = -1;
	int suggestion;
	int suggnr;
	/*
	 * Backup fields:
	*/
	for (i=0; i < 81; i++)
		m_fields_bak2[i] = m_fields[i];
	/*
	 * Run through fields:
	*/
	for (i=0; i < 81; i++)
	{
		suggestion = -1;
		if (m_fields[i].get_suggestions_count() > 2 && m_fields[i].get_solution() == 0)
		{
			/*
			 * Get the suggestion:
			*/
			for (j=0; j < 9; j++)
			{
				if (m_fields[i].get_suggestions()[j] != 0)
				{
					if (!is_suggestion_already_checked_step3(i, m_fields[i].get_suggestions()[j]))
					{
						suggestion = m_fields[i].get_suggestions()[j];
						break;
					};
				};
			}
		};
		if (suggestion != -1)
		{
			result = i;
			break;
		};
	}
	if (result == -1)
	{
		return false;
	}
	else
	{
		/*
		 * Mark it as checked:
		*/
		for (i=0; i < 729; i++)
		{
			if (m_checked_suggestions_step3[i].field == -1)
			{
				suggnr = i;
				break;
			};
		}
		m_checked_suggestions_step3[suggnr].field = result;
		m_checked_suggestions_step3[suggnr].suggestion = suggestion;
		/*
		 * ... and set the solution to it:
		*/
		m_fields[result].set_solution(suggestion);
		std::cout << "===== (Layer 2) Trying " << suggestion << " in " << result << " =====" << std::endl;
		return true;
	};
}
bool Sudoku::is_suggestion_already_checked_step3(int field, int suggestion)
{
	int i;
	for (i=0; i < 729; i++)
	{
		if (m_checked_suggestions_step3[i].field == field && m_checked_suggestions_step3[i].suggestion == suggestion)
			return true;
	}
	return false;
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
