// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: V_Table.cpp

#include "V_Table.h"
#include <string>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

V_Table::V_Table() {} // Constructor

// Clears the table's contents
void V_Table::clear() {elem.clear();}

// Returns an iterator to the start of the table	
const list<string>::iterator V_Table::begin(void) { return elem.begin(); }

// Returns an iterator to the end of the table
const list<string>::iterator V_Table::end(void) { return elem.end(); }

// Returns an iterator to the start of the const table	
const list<string>::const_iterator V_Table::cbegin(void) const { return elem.cbegin(); }

// Returns an iterator to the end of the const table
const list<string>::const_iterator V_Table::cend(void) const { return elem.cend(); }

// Returns 'true' if 'str' exists in the table, otherwise it returns 'falese'
bool V_Table::exists(const string &str) const {
	return (find(elem.begin(), elem.end(), str) != elem.end());
}

// Performs a sorted insert provided 'str' does not already exist in the table
void V_Table::insert(const string &str) {
	list<string>::iterator place = lower_bound(elem.begin(), elem.end(), str);
	if((place == elem.end()) || (*place != str))
		elem.insert(place, str);
}

// Removes 'str' from table
void V_Table::remove(const std::string &str) { elem.remove(str); }

// Performs set union between the object's element table with 'table'
void V_Table::unite(const V_Table &table) {

	// Perform set union on the two tables. The result will be stored in 'elem'
	list<string>::iterator i = elem.begin();
	list<string>::const_iterator j = table.cbegin();
	while(i != elem.end() && j != table.cend()) {
		if(*i < *j)
			++i;
		else if(*i == *j) {
			++i;
			++j;
		}
		else {
			elem.insert(i, *j++);
		}
	} // end while

	// Append the remaining elements of table (which are greater than all elements of 'elem')
	while(j != table.cend()) 
		elem.push_back(*j++);
}

// Produce a new variable not already at the table
std::string V_Table::get_new_var(void) {

	string new_var = "a";

	// Check the variable matrix for existence of variable named 'new_var'
	// If 'new_var' already exists in the variable matrix then we choose the next 
	// lexicographical name and we retry
	while(exists(new_var)) {
		size_t p = new_var.find_last_not_of('Z');
		if(p == string::npos) { // original name was "ZZ...Z"
			// new name will be "aa...a" with one more 'a' than original 'Z's
			new_var.insert(new_var.begin(), 'a');
			new_var.replace(0, new_var.size(), new_var.size(), 'a');
		}
		else {
			if(new_var[p] == 'z')
				new_var[p++] = 'A'; // Capitals come after non-capitals
			else
				++new_var[p++]; // Pick the next letter in the same caategory (i.e. capital or non-capital)

			if(p == new_var.size() - 1)
				new_var.replace(p, new_var.size() - p, new_var.size() - p, 'a');
		}
	}
	insert(new_var);
	return new_var;
}
