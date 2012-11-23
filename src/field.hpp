/*
 * field.hpp
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
#ifndef FIELD_HPP
#	define FIELD_HPP

#	include <iostream>

	class Field
	{
		public:
			Field();
			virtual ~Field();

			unsigned int get_solution(void);
			char get_solution_showable(void);
			unsigned int *get_suggestions(void);
			unsigned int get_suggestions_count(void);
			bool set_solution(unsigned int solution);
			bool add_suggestion(unsigned int suggestion);
			bool rm_suggestion(unsigned int suggestion);
		private:
			unsigned int m_solution;
			unsigned int m_suggestions[9];
	};
#endif // FIELD_HPP
