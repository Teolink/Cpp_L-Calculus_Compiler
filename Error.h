// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: lambda.h

#ifndef _LCC_ERROR_
#define _LCC_ERROR_

#include <iostream>

// Exception class denoting "an error has happened".
// Used in try-catch blocks.
class Error {
	const char* const message;
public:
	Error(const char* const msg = 0) : message(msg) {}
	void print() {std::cerr << "Error"; if(message) std::cerr << ": " << message << std::endl;}
};

#endif // #ifndef _LCC_ERROR_