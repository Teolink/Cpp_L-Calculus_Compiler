Name: Theodoros Gatsos
Record Number: 1115200200013
Semester: 5th  
University of Athens
Department of Informatics and Telecommunications 
Subject: Principles of Programming Languages 
February 2005  
Project: Implementation of a lambda calculus compiler 

General information about the program

This program is a compiler for lambda calculus. What it does actually is receiving a fully
parenthesized lamda expression as input and using normal series deduction strategy to find its
normal form, provided it exists. Whitespaces are ignored. A token matrix is created as well as
a matrix for variables corresponding to the given expression. Variables consist only of letters
of the English alphabet (both small and capitals).                
                                                                                      
When a change of a variable in an expression is deemed neccessary in the context
of a B-conversion, the new variable is received from an imaginary matrix which contains all the 
legal variables that can be used in the program, sorted lexicographically.        
                                                                                       
Finally, some constraints are placed in the beginning of the program regarding the size
of the main program structures (e.g. INPUT_SIZE and MAX_SLOTS) for protection reasons.    
