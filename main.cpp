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
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]) try
{
	Compiler compiler(200, true);

        if(argc > 2) {
            cerr << "Too many arguments given" << endl;
            return EXIT_FAILURE;
        }
       
	// Input stage
	string line;
        string expr;
        if(argc == 2) { // Input file name is given
            string fname = argv[1];
            ifstream fs(fname.c_str(), ios_base::in);
            if(!fs.is_open()) {
                    cerr << "File " << fname << " could not be opened" << endl;
                    cerr << "Make sure that the file exists" << endl;
                    cerr << "Aborting program" << endl;
                    return EXIT_FAILURE;
            }
            if(fs.bad()) {
                    cerr << "There was a critical error with the opening of file: " << fname << endl;
                    cerr << "Aborting program" << endl;
                    return EXIT_FAILURE;
            }
            while(getline(fs, line))
		expr += line;
        }
        else {
            cout << "Provide the input lambda expression" << endl << "expr: ";
            getline(cin, expr);
        }
	compiler.input(expr);

	// Lexical Analysis
	compiler.lexical_analysis();
	if(!compiler.is_lexed()) {
		cerr << "Main: There are lexical errors in the input lambda term" << endl;
		return EXIT_FAILURE;
	}

	// Syntax Analysis
	compiler.syntax_analysis();
	if(!compiler.is_syntaxed()) {
		cerr << "Main: There are syntax errors in the input lambda term" << endl;
		return EXIT_FAILURE;
	}

	// Find normal form
	compiler.find_normal();

	cout << endl;
	cout << "Press enter to quit program" << endl;
	string dummy;
	getline(cin,dummy);
	return EXIT_SUCCESS;
}
catch(exception exc) {
	cerr << exc.what() << endl;
	return EXIT_FAILURE;
}
