/*
 * field.cpp
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
#include "field.hpp"

Field::Field() : m_solution(0), m_suggestions{1, 2, 3, 4, 5, 6, 7, 8, 9}
{
	
}
Field::~Field()
{

}
unsigned int Field::get_solution(void)
{
	return m_solution;
}
char Field::get_solution_showable(void)
{
	switch (m_solution)
	{
		case 0:
			return ' ';
		case 1:
			return '1';
		case 2:
			return '2';
		case 3:
			return '3';
		case 4:
			return '4';
		case 5:
			return '5';
		case 6:
			return '6';
		case 7:
			return '7';
		case 8:
			return '8';
		case 9:
			return '9';
	}
}
unsigned int *Field::get_suggestions(void)
{
	return m_suggestions;
}
unsigned int Field::get_suggestions_count(void)
{
	unsigned int i;
	unsigned int count = 0;
	for (i=0; i < 9; i++)
		if (m_suggestions[i] != 0)
			count++;
	return count;
};
bool Field::set_solution(unsigned int solution)
{
	if (solution > 9)
		return false;
	m_solution = solution;
	return true;
}
bool Field::add_suggestion(unsigned int suggestion)
{
	/*
	 * Variable declarations:
	*/
	int i;
	/*
	 * Check if the suggestion is already set:
	*/
	for (i=0; i < 9; i++)
	{
		if (m_suggestions[i] == suggestion)
			return false;
	}
	/*
	 * Add suggestion:
	*/
	for (i=0; i < 9; i++)
	{
		if (m_suggestions[i] == 0)
		{
			m_suggestions[i] = suggestion;
			return true;
		};
	}
	return false;
}
bool Field::rm_suggestion(unsigned int suggestion)
{
	/*
	 * Variable declarations:
	*/
	int i;
	/*
	 * Remove suggestion:
	*/
	for (i=0; i < 9; i++)
	{
		if (m_suggestions[i] == suggestion)
		{
			m_suggestions[i] = 0;
			return true;
		};
	}
	return false;
}
