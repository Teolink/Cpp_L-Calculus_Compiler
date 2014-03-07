// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: main.cpp

#include "Compiler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;

int main(void) try
{
	Compiler compiler(200);

	// Input stage
	string fname = "input_lambda.txt", expr;
	ifstream fs(fname.c_str(), ios_base::in);
	if(!fs.is_open()) {
		cerr << "File " << fname << " could not be opened" << endl;
		cerr << "Make sure that the file exists" << endl;
		cerr << "Aborting program" << endl;
		return 1;
	}
	if(fs.bad()) {
		cerr << "There was a critical error with the opening of file: " << fname << endl;
		cerr << "Aborting program" << endl;
		return 1;
	}
	string line;
	while(getline(fs, line))
		expr += line;
	compiler.input(expr);

	// Lexical Analysis
	compiler.lexical_analysis();
	if(!compiler.is_lexed()) {
		cerr << "Main: There are lexical errors in the input lambda term" << endl;
		return 1;
	}

	// Syntax Analysis
	compiler.syntax_analysis();
	if(!compiler.is_syntaxed()) {
		cerr << "Main: There are syntax errors in the input lambda term" << endl;
		return 1;
	}

	// Find normal form
	compiler.find_normal();

	cout << endl;
	cout << "Press enter to quit program" << endl;
	string dummy;
	getline(cin,dummy);
	return 0;
}
catch(exception exc) {
	cerr << exc.what() << endl;
	return 1;
}
