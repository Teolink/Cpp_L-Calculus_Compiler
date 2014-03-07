// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: Compiler.h

#ifndef _LCC_COMPILER_
#define _LCC_COMPILER_

#include "V_Table.h"
#include "S_Table.h"
#include "Lambda.h"
#include <string>
#include <iostream>
#include <fstream>
#include <iterator>

class Compiler {
private:
	const unsigned int max_steps;
	bool lex_analyzed;
	bool syn_analyzed;
	std::string expr;
	V_Table vtab;
	S_Table stab;
	Lambda* lambda;

	// This function detects the lambda term beginning from 'start' of the token matrix 'stab'.
	// 'end' will hold an iterator pointing just after the end of said lambda term.
	// Returns true if the operation is successful, otherwise it returns false.
	// It is assumed at this point that the token matrix contents represent a lambda term
	bool lambda_detect(const S_Storage_t::const_iterator &start, S_Storage_t::const_iterator &end) const;

	// This function checks if the input expression represented by the symbols between the
	// 'start' and 'end' pointers of the symbol table 'stab' is a syntactically correct lambda term.
	// In this program lambda terms must be fully parenthesized and can also
	// contain an arbitrary number of whitespace characters.
	Lambda* Compiler::syntax_analyze(const S_Storage_t::const_iterator &start, const S_Storage_t::const_iterator &end);
public:
	Compiler(unsigned int max_s = 500); // Constructor
	~Compiler(); // Destructor
	bool is_lexed(void); // Returns 'lex_analyzed'
	bool is_syntaxed(void); // Returns 'syn_analyzed'

	// This function gives an input to the compiler. If the compiler already worked with an input
	// then this function resets the compiler's state before assigning the new input
	void input(const std::string &inp);

	// This function provides lexical analysis to the input lambda expression 'expr'.
	// The 'stab' matrix stores the lexical tokens of the input expression in the order that they were written.
	// The 'vtab' matrix stores the names of the variables found in the input expression in alphabetic order.
	void lexical_analysis(void);

	// This function checks if the input expression represented by the symbols between the
	// 'start' and 'end' pointers of the symbol table 'stab' is a syntactically correct lambda term.
	// In this program lambda terms must be fully parenthesized and can also
	// contain an arbitrary number of whitespace characters.
	void syntax_analysis(void);


	void find_normal(void);
};

#endif // #ifndef _LCC_COMPILER_