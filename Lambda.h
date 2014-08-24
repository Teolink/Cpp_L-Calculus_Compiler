// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: Lambda.h

#ifndef _LCC_LAMBDA_
#define _LCC_LAMBDA_

#include "V_Table.h"
#include <string>
#include <ostream>

class Lambda {
protected:
	enum {VAR, FUNC, PAIR} type;
	std::string var;
	Lambda *lam1, *lam2;
public:
	// Construct a lambda term of type 'VAR' (variable)
	Lambda(const std::string &vname);

	// Construct a lambda term of type 'FUNC' (function)
	Lambda(const std::string &vname, Lambda *const l1);

	// Construct a lambda term of type 'PAIR' (pair)
	Lambda(Lambda *const l1, Lambda *const l2);

	// Copy constructor
	Lambda(const Lambda &lam);

	// Destructor
	~Lambda();

	// This function returns a pointer to a V_Table containing the list of 
	// free variables of the calling lambda term
	V_Table *free_vars() const;


	void substitute(const std::string &vname, const Lambda &lterm, V_Table &vtab);

	// This function makes an H-conversion to the given lambda term of the form (\x.(M x))
	// provided it is possible.
	bool h_redex();

	// This function makes a B-conversion to the given lambda term of the form (\x.(M x))
	// provided it is possible.
	bool b_redex(V_Table &vtab);

	// This function proceeds a step in the normalization of the lambda term.
	// The step is made on the lambda term with the lambda symbol to the 
	// leftmost of the expression
        // Returns "true" if the term can be further reduced, otherwise it returns "false"
	bool reduce(V_Table &vtab);

	// This function finds the normal form of the given lambda term (provided it exists)
	// using the normal series deduction strategy
	// If the reduction steps exceed 'max_steps', the normalization stops as a safety measure
        // Enable 'verbose' to print each step in the procedure
	void normalize(unsigned int max_steps, V_Table &vtab, bool verbose);

	// overloading operator << of ostream to print lambda terms
	friend std::ostream& operator<<(std::ostream& os, const Lambda& lambda);
};

#endif // #ifndef _LCC_LAMBDA_