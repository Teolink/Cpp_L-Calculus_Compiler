// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: V_Table.h

#ifndef _LCC_V_TABLE_
#define _LCC_V_TABLE_

#include <list>
#include <string>
#include <iterator>

class V_Table { // The class of a table of variables
private:
	std::list<std::string> elem;
public:	
	V_Table(); // Constructor
	void clear(); // Clears the table's contents
	const std::list<std::string>::iterator begin(void); // Returns an iterator to the start of the table	
	const std::list<std::string>::iterator end(void); // Returns an iterator to the end of the table
	const std::list<std::string>::const_iterator cbegin(void) const; // Returns an iterator to the start of the const table	
	const std::list<std::string>::const_iterator cend(void) const; // Returns an iterator to the end of the const table

	// Returns 'true' if 'str' exists in the table, otherwise it returns 'false'
	bool exists(const std::string &str) const;

	// Performs a sorted insert provided 'str' does not already exist in the table
	void insert(const std::string &str);

	// Removes 'str' from table
	void remove(const std::string &str);

	// Performs set union between the object's element table with 'table'
	void unite(const V_Table &table);

	// Produce a new variable not already at the table
	std::string get_new_var(void);
};

#endif // #ifndef _LCC_V_TABLE_