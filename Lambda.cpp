// Name: Theodoros Gatsos
// Record Number: 1115200200013
// Semester: 5th  
// University of Athens
// Department of Informatics and Telecommunications 
// Subject: Principles of Programming Languages 
// February 2005  
// Project: Implementation of a lambda calculus compiler 

// File: Lambda.cpp

#include "Lambda.h"
#include "V_Table.h"
#include <string>
#include <iostream>

using namespace std;

// Construct a lambda term of type 'VAR' (variable)
Lambda::Lambda(const string &vname) : type(VAR), var(vname), lam1(0), lam2(0) {}

// Construct a lambda term of type 'FUNC' (function)
Lambda::Lambda(const string &vname, Lambda *const l1) : type(FUNC), var(vname), lam1(l1), lam2(0) {}

// Construct a lambda term of type 'PAIR' (pair)
Lambda::Lambda(Lambda *const l1, Lambda *const l2) : type(PAIR), var(""), lam1(l1), lam2(l2) {}

// Copy constructor
Lambda::Lambda(const Lambda &lam) : type(lam.type), var(lam.var), lam1(0), lam2(0) {
	switch(type) {
	case VAR:	
		break;
	case FUNC:	
		lam1 = new Lambda(*(lam.lam1));
		break;
	case PAIR:	
		lam1 = new Lambda(*(lam.lam1));;
		lam2 = new Lambda(*(lam.lam2));;
		break;
	}
}

// Destructor
Lambda::~Lambda() {
	switch(type) {
	case VAR:	
		break;
	case FUNC:	
		delete lam1;
		break;
	case PAIR:	
		delete lam1;
		delete lam2;
		break;
	}
}

// This function returns a pointer to a V_Table containing the list of 
// free variables of the calling lambda term
V_Table *Lambda::free_vars() const {
	V_Table *fvars = NULL; 
	switch(type) {
	case VAR:
		fvars = new V_Table();
		fvars->insert(var);
		break;
	case FUNC:
		fvars = lam1->free_vars();
		fvars->remove(var);
		break;
	case PAIR:
		{
			fvars = lam1->free_vars();
			V_Table *temp = lam2->free_vars();
			fvars->unite(*temp);
			delete temp;
		}
		break;
	}
	return fvars;
}

// This function substitutes a variable with a lambda term in the given lambda term
void Lambda::substitute(const string &vname, const Lambda &lterm, V_Table &vtab) {

	switch(type) {
	case VAR:
		if(var == vname) { // x[x:=N] -> N
			type = lterm.type;
			switch(lterm.type) {
			case VAR:
				var = lterm.var;
				break;
			case FUNC:
				var = lterm.var;
				lam1 = new Lambda(*lterm.lam1);
				break;
			case PAIR:
				var = "";
				lam1 = new Lambda(*lterm.lam1);
				lam2 = new Lambda(*lterm.lam2);
				break;
			}
		}
		// y[x:=N] -> y
		break;
	case FUNC:
		if(var != vname) {
			const V_Table *n_vars = lterm.free_vars();
			const V_Table *p_vars = lam1->free_vars();
			if( (!n_vars->exists(var)) || (!p_vars->exists(vname)) )
				lam1->substitute(vname, lterm, vtab); // (\y.P)[x:=N] -> \y.P[x:=N] if y not in FV(P) and x not in FV(N)
			else { // (\y.P)[x:=N] -> \z.P[y:=z][x:=N] if y in FV(P) and x in FV(N) where z not in (FV(P) union FV(N))
				string new_name = vtab.get_new_var();
				lam1->substitute(var,Lambda(new_name),vtab);
				lam1->substitute(vname, lterm, vtab);
				var = new_name;
			}
			delete n_vars;
			delete p_vars;
		}
		// (\x.P)[x:=N] -> \x.P
		break;
	case PAIR: // (P Q) [x:=N] -> (P[x:=N] Q[x:=N])
		lam1->substitute(vname, lterm, vtab);
		lam2->substitute(vname, lterm, vtab);
		break;
	}
}



// This function makes an H-conversion to the given lambda term of the form (\x.(M x))
// provided it is possible.
bool Lambda::h_redex() {
	if((type == FUNC) && 
		(lam1->type == PAIR) &&
		(lam1->lam2->type == VAR)) {
		V_Table *fvar = lam1->lam1->free_vars(); 	
		if(!fvar->exists(lam1->lam2->var)) {
			// Lambda term is of the form (\x.(M x)) with 'x' not a free variable in 'M'. Convert to M
			delete lam1->lam2;
			Lambda *temp = lam1->lam1;
			type = temp->type;
			switch(type) {
			case VAR:
				var = temp->var;
				break;
			case FUNC:
				var = temp->var;
				lam1 = temp->lam1;
				break;
			case PAIR:
				var = "";
				lam1 = temp->lam1;
				lam2 = temp->lam2;
			} // end switch(type)
			delete fvar;
			return true;
		} // end if(!fvar->exists(lam1->lam2->var))
		delete fvar;
	} // end if(type == FUNC)
	return false;
}

// This function makes a B-conversion to the given lambda term of the form (\x.(M x))
// provided it is possible.
bool Lambda::b_redex(V_Table &vtab) {

	if((type == PAIR) && (lam1->type == FUNC)) {
		lam1->lam1->substitute(lam1->var, *lam2, vtab);
		Lambda* temp = lam1->lam1;
		type = temp->type;
		lam1->var = "";
		delete lam2;
		switch(type) {
		case VAR:
			var = temp->var;
			break;
		case FUNC:
			var = temp->var;
			lam1 = temp->lam1;
			break;
		case PAIR:
			lam1 = temp->lam1;
			lam2 = temp->lam2;
			break;
		}
		return true;
	}
	return false;
}

// overloading operator << of ostream to print lambda terms
ostream& operator<<(ostream& os, const Lambda& lambda) {
	switch(lambda.type) {
	case 0: os << lambda.var;	break;
	case 1: os << "(\\" << lambda.var << '.' << *lambda.lam1 << ')'; break;
	case 2: os << '(' << *lambda.lam1 << ' ' << *lambda.lam2 << ')'; break;
	}
	return os;
}

// This function proceeds a step in the normalization of the lambda term.
// The step is made on the lambda term with the lambda symbol to the 
// leftmost of the expression
// Returns "true" if the term can be further reduced, otherwise it returns "false"
bool Lambda::reduce(V_Table &vtab) {
	switch(type) {
	case VAR:
		return false; // Variables cannot be further reduced
	case FUNC:
		if(h_redex())
			return true;
		return lam1->reduce(vtab);
	case PAIR:
		if(b_redex(vtab))
			return true;
		return ((lam1->reduce(vtab)) || (lam2->reduce(vtab)));
	default: 
		return false;
	}
}

// This function finds the normal form of the given lambda term (provided it exists)
// using the normal series deduction strategy
void Lambda::normalize(unsigned int max_steps, V_Table &vtab, bool verbose = false) {
	unsigned int counter = 0;
        if(verbose) {
            cout << "Initial: " << *this << endl;
            while(reduce(vtab) && (counter < max_steps)) 
                    cout << "Step " << (++counter) << ": " << *this << endl;
            if(counter == max_steps)
                    cout << "Normalization effort stopped after " << max_steps << " steps" << endl;
            else
                    cout << "Input term normalized after " << counter << " steps" << endl;
            cout << "The result is: " << *this << endl;
        }
        else {
            while(reduce(vtab))
                ;
            cout << *this << endl;
        }
}