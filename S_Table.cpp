// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: S_Table.cpp

#include "S_Table.h"
#include <string>
#include <iostream>

using namespace std;

// Clears the table's contents
void S_Table::clear(void) { elem.clear(); }

// Returns an iterator to the start of the table	
const S_Storage_t::const_iterator S_Table::cbegin(void) const {return elem.cbegin(); } 

// Returns an iterator to the end of the table
const S_Storage_t::const_iterator S_Table::cend(void) const {return elem.cend(); } 

// Insert 'sym' at the end of the symbol table
void S_Table::insert(const Symbol &sym) { elem.push_back(sym); }

void S_Table::print(const S_Storage_t::const_iterator start, const S_Storage_t::const_iterator end) const {
	bool prev_var = false; // true if the previous symbol that was printed was a variable
	for(S_Storage_t::const_iterator i = start; i != end; ++i) {
		switch(i->type) {
		case LEFT_PAR:	
			cout << '(';	
			prev_var = false;	
			break;
		case RIGHT_PAR:	
			cout << ')';	
			prev_var = false;	
			break;
		case LAMBDA:	
			cout << '\\';	
			prev_var = false;	
			break;
		case DOT:		
			cout << '.';	
			prev_var = false;	
			break;
		case VARIABLE:
			if(prev_var)
				cout << ' ';
			cout << i->name;
			prev_var = true;
			break;
		default: break;
		}
	}
}