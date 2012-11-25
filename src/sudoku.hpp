/*
 * sudoku.hpp
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
#ifndef SUDOKU_HPP
#	define SUDOKU_HPP

#	include <iostream>
#	include "field.hpp"
	
	struct FieldSuggestionPair
	{
		int field;
		int suggestion;
	};
	
	class Sudoku
	{
		public:
			Sudoku();
			virtual ~Sudoku();

			bool solve(void);
			void fill(unsigned int values[81]);
			void dump(void);
			void dump_suggestions(void);
			bool is_solved(void);
		private:
			void fill_suggestions(void);
			bool try_numbers(void);
			bool try_numbers_step3(void);
			bool is_suggestion_already_checked(int field, int suggestion);
			bool is_suggestion_already_checked_step3(int field, int suggestion);
			void get_blockfields(int field, int *blockfields);

			Field m_fields[81];
			Field m_fields_bak[81];
			Field m_fields_bak2[81];
			FieldSuggestionPair m_checked_suggestions[729];
			FieldSuggestionPair m_checked_suggestions_step3[729];
	};
#endif // SUDOKU_HPP
