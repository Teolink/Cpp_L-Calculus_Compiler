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
#include <exception>

// Exception class denoting "an error has happened".
// Used in try-catch blocks.
class Error : public std::exception {
	const char* const _msg;
public:
	Error(const char* const msg = 0);
	const char *what() const noexcept;
};

#endif // #ifndef _LCC_ERROR_