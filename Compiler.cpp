// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: Compiler.cpp

#include "Compiler.h"
#include "V_Table.h"
#include "S_Table.h"
#include <iostream>
#include <string>
#include <iterator>

using namespace std;

//------------------------ LEXICAL ANALYSIS FUNCTIONS --------------------------
static const string alphabetic = "abcdefghijklmnopqrstuvwxyz" "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const string symbol = "().\\";
static const string whitespace = " \n\t\f\v";

// Constructor
Compiler::Compiler(unsigned int max_s) : max_steps(max_s), lex_analyzed(false),
	syn_analyzed(false), expr(), vtab(), stab(), lambda(0) {}

// Destructor
Compiler::~Compiler() {
	if(lambda)
		delete lambda;
}

// Returns 'lex_analyzed'
bool Compiler::is_lexed(void) { return lex_analyzed; } 

// Returns 'syn_analyzed'
bool Compiler::is_syntaxed(void) { return syn_analyzed; } 

// This function gives an input to the compiler. If the compiler already worked with an input
// then this function resets the compiler's state before assigning the new input
void Compiler::input(const string &inp) {
	lex_analyzed = false;
	syn_analyzed = false;
	expr = inp;
	stab.clear();
	vtab.clear();
	if(lambda) {
		delete lambda;
		lambda = 0;
	}
	cout << "Compiler was given the input: " << expr << endl;
	return;
}

// This function provides lexical analysis to the input lambda expression 'expr'.
// The 'stab' matrix stores the lexical tokens of the input expression in the order that they were written.
// The 'vtab' matrix stores the names of the variables found in the input expression in alphabetic order.
void Compiler::lexical_analysis(void)
{
	if(lex_analyzed) {
		cerr << "Input expression was already lexically analyzed" << endl;
		return;
	}

	const string checkstr = alphabetic + symbol + whitespace;

	// Check the lambda term for illegal symbols
	size_t res = expr.find_first_not_of(checkstr);
	if(res != string::npos) {
		cerr << "Lexical analysis: Symbol \'" << expr[res] << "\' is not allowed" << endl;
		lex_analyzed = false;
		return;
	}
	else { // Find the lexical tokens of the input expression 'expr' given.
		Symbol token;
		const size_t inp_size = expr.size();
		size_t p = 0;
		while(p < inp_size) {
			p = expr.find_first_not_of(whitespace, p);// Ignore whitespaces
			if(p == string::npos) 
				break; // End of input reached
			else {
				switch(expr[p]) {
				case '(':
					token.type = LEFT_PAR;
					token.name = "(";
					++p;
					break;
				case ')': 
					token.type = RIGHT_PAR;
					token.name = ")";
					++p;
					break;
				case '\\':
					token.type = LAMBDA;
					token.name = "\\";
					++p;
					break;
				case '.':
					token.type = DOT;
					token.name = ".";
					++p;
					break;
				default:
					// Lexical token corresponds to a variable
					token.type = VARIABLE;
					size_t q = expr.find_first_not_of(alphabetic, p);
					if(q == string::npos)
						token.name = expr.substr(p);
					else
						token.name = expr.substr(p, q - p);
					vtab.insert(token.name);
					p = q;
					break;
				}
			} // end else
			stab.insert(token); // This line gets executed in all cases but whitespaces and end of input
		}// end while
	}
	lex_analyzed = true;
	return;
}

void Compiler::find_normal(void) {
	if(!syn_analyzed) {
		cerr << "Input expression is not syntactically analyzed yet" << endl;
		return;
	}
	lambda->normalize(max_steps, vtab);
	return;
}