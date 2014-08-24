// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: S_Table.h

#ifndef _LCC_S_TABLE_
#define _LCC_S_TABLE_

#include <list>
#include <string>

// This enumberation type is used to characterize lexical tokens (symbols)
enum s_type {
	VARIABLE,
	LEFT_PAR,
	RIGHT_PAR,
	LAMBDA,
	DOT
};


// A lexical token (symbol) is represented by its type and value (string content).
struct Symbol {
	s_type type;
	std::string name;
};

typedef std::list<Symbol> S_Storage_t;

class S_Table { // The class of a table of lexical symbols
private:
	S_Storage_t _elem;
public:
	void clear(void); // Clears the table's contents
	const S_Storage_t::const_iterator cbegin(void) const; // Returns an iterator to the start of the table	
	const S_Storage_t::const_iterator cend(void) const; // Returns an iterator to the end of the table
	void insert(const Symbol &sym); // Insert 'sym' to symbol table

	// Print the contents of the symbol table from 'start' to 'end'
	void print(const S_Storage_t::const_iterator start, const S_Storage_t::const_iterator end) const;
};

#endif // #ifndef _LCC_S_TABLE_