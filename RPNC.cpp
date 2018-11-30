/*Program: 
RPNC.cpp for CSC 230-02
Author: Miles Cumiskey 
---------------------------
Description: An RPN calculator that reads a series of expressions in RPN form from a file. 
The user has two options: they can enter the filename as a command line argument or they may be prompted for a filename after launching the program. 
In either case, the program halts if the file does not exist.

Individual expressions in RPN format (see below) are read from the file. 
If an expression is well-formed the program will evaluate it and display the expression along with its results on the console. 
Malformed expressions result in an error message being displayed on the console.
   
Input: an ASCII text files with the names of the files to process
Output: Wordcount and linecount of included files. Allows for searching documents for specific words. Displays the result
Preconditions: none
Postconditions: none
---------------------------*/