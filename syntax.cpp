// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: syntax.cpp

#include "Error.h"
#include "Compiler.h"
#include "V_Table.h"
#include "S_Table.h"
#include "Lambda.h"
#include <string>
#include <iterator>
#include <iostream>

using namespace std;

//----------------------- SYNTAX ANALYSIS FUNCTIONS -----------------------------

// This function detects the lambda term beginning from 'start' of the token matrix 'stab'.
// 'end' will hold an iterator pointing just after the end of said lambda term.
// Returns true if the operation is successful, otherwise it returns false.
// It is assumed at this point that the token matrix contents represent a lambda term
bool Compiler::_lambdaDetect(const S_Storage_t::const_iterator &start, S_Storage_t::const_iterator &end) const {
	unsigned int stack = 0; // Counts the current number of left parentheses that need to be balanced by right ones
	if(start->type == VARIABLE) {// Case of variable
		end = start;
		end++;
		return true;
	}
	else if(start->type == LEFT_PAR) {// Case of parenthesized lambda term
		S_Storage_t::const_iterator i = start;
		while(i != _sTable.cend()) {// Check for balanced parenthesization
			if(i->type == LEFT_PAR)
				stack++;
			if(i->type == RIGHT_PAR) {
				stack--;
				if(!stack) {
					end = ++i;
					return true;
				}
			}
			++i;
		}
		cerr << "lambda_detect: Imbalanced parenthesization detected" << endl;
		return false;
	}
	cerr << "lambda_detect: Illegal starting symbol " << start->name << endl;
	return false;
}


// This function checks if the input expression represented by the symbols between the
// 'start' and 'end' pointers of the symbol table 'stab' is a syntactically correct lambda term.
// In this program lambda terms must be fully parenthesized and can also
// contain an arbitrary number of whitespace characters.
Lambda* Compiler::_syntaxAnalyze(const S_Storage_t::const_iterator &start, const S_Storage_t::const_iterator &end) {
	int dist = distance(start, end);
	if(!dist) {// Empty input case
		cerr << "Syntax analysis: Empty input" << endl;
		return 0;
	}
	if(dist == 1) { // Case 1. Lambda term must be a variable
		if(start->type != VARIABLE) {
			cerr << "Syntax_analysis: Token " << start->name << " is not a variable" << endl;
			return 0;
		}
		return new Lambda(start->name);
	}

	S_Storage_t::const_iterator i_start = start;
	S_Storage_t::const_iterator i_end = end;
	if((i_start->type == LEFT_PAR) && ((--i_end)->type == RIGHT_PAR)) { 
		if((++i_start)->type == LAMBDA) {
			// Case 2. Lambda term is of the form (\x.M) where 'x' is a variable and 'M' a lambda term
			if(dist >= 6) {
				if(((++i_start)->type == VARIABLE) &&
					((++i_start)->type == DOT)) {
					S_Storage_t::const_iterator M_expr_start, M_expr_end;
					M_expr_start = ++i_start;
					M_expr_end = i_end;
					Lambda *M_lambda = _syntaxAnalyze(M_expr_start, M_expr_end);
					if(!M_lambda)
						return 0;
					else {
						i_start = start;
						++(++i_start); // Get i_start to point to variable 'x'
						return new Lambda(i_start->name, M_lambda);
					}
				}
			}
			else { // form (\x.M) must consist of at least 6 lexical tokens
				cerr << "Syntax_analysis: Form (\\var.expr) must consist of at least 6 tokens" << endl;
				return 0;
			}
		}
		if(dist >= 4) {
			// Case 3. Lambda term is of the form (M N) where 'M' and 'N' are lambda terms
			S_Storage_t::const_iterator M_expr_start, M_expr_end, N_expr_start, N_expr_end;
			M_expr_start = start;
			++M_expr_start;
			if(!_lambdaDetect(M_expr_start, M_expr_end)) {
				cerr << "Syntax_analysis: Could not detect first expression of term ";
				_sTable.print(start, end);
				cerr << endl;
				return 0;
			}
			N_expr_start = M_expr_end;
			if(!_lambdaDetect(N_expr_start, N_expr_end)) {
				cerr << "Syntax_analysis: Could not detect second expression of term ";
				_sTable.print(start, end);
				cerr << endl;
				return 0;
			}
			i_end = end;
			if(N_expr_end != (--i_end)) {
				cerr << "Syntax_analysis: Parenthesized form ";
				_sTable.print(start, end);
				cerr << " contains more than two seperate expressions" << endl;
				return 0;
			}
			Lambda *M_lambda = _syntaxAnalyze(M_expr_start, M_expr_end);
			Lambda *N_lambda = _syntaxAnalyze(N_expr_start, N_expr_end);
			if(!M_lambda || !N_lambda)
				return 0;
			return new Lambda(M_lambda, N_lambda);
		}
		else { // form (M N) must consist of at least 4 lexical tokens
			cerr << "Syntax_analysis: form (expr expr) must consist of at least 4 lexical tokens" << endl;
			return 0;
		}
	}
	else {
		cerr << "Syntax_analysis: Input expression is not parenthesized" << endl;
		return 0;
	}
}

// This function performs syntax analysis to the input lambda term
void Compiler::syntax_analysis(void) {
	if(_synAnalyzed) {
		cerr << "Input expression is already syntactically analyzed" << endl;
		return;
	}
	_synAnalyzed = ((_lambda = _syntaxAnalyze(_sTable.cbegin(), _sTable.cend())) != 0);
	return;
}