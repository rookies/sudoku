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

	class Sudoku
	{
		public:
			Sudoku();
			virtual ~Sudoku();

			bool solve(void);
			void fill(unsigned int values[81]);
			void dump(void);
			void dump_suggestions(void);
		private:
			void fill_suggestions(void);
			void refill_suggestions(unsigned int field, unsigned int value);

			Field m_fields[81];
			bool m_solved;
			bool m_filled;
	};
#endif // SUDOKU_HPP
