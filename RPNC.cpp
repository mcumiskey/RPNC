/*Program: 
RPNC.cpp for CSC 230-02
Author: Miles Cumiskey 
---------------------------
Description: An RPN calculator that reads a series of expressions in RPN form from a file. 
The user has two options: they can enter the filename as a command line argument or they may be prompted for a filename after launching the program. 
In either case, the program halts if the file does not exist.
Individual expressions in RPN format are read from the file. 
If an expression is well-formed the program will evaluate it and display the expression along with its results on the console. 
Malformed expressions result in an error message being displayed on the console.
   
Input: an ASCII text files with formatted numbers and operands - can also be entered via command line
Output: Math
Preconditions: none
Postconditions: none
---------------------------*/

#include <string> 
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

class Stack {
    public:
    int a[10];
    int size;

    Stack() {
        size = 0;
    }
    bool isEmpty(){
        return size == 0;
    }
    void push (int newElement) {
        if (size == 10) {
            cout << "Error: stack is full." << endl;
        } else {
            a[++size] = newElement;
        }
    }

    int pop () {
        if (size == 0) {
            cout << "Error: stack is empty." << endl;
            return -999; //not good
        } else {
            int returnElement = a[size];
            --size;
            return returnElement;
        }
    }

    int peek() {
        return a[size];
    }
};
//check if a given file opens
bool doesFileOpen(ifstream &infile) {
    if(infile.fail()) {
        return false;
    } else {
        return true;
    }
};

void run(ifstream &infile); //pops everything from the file streams and works math magic
bool isOperator(string ch); //checks to see if a string is an operator 
bool isNumber(string ch);   //checks to see if string is a number
void evaluate(int num2, int num1, string op); //does math on a specific part 

int main(int argc, char* argv[]){

    string filename;
    ifstream infile;
    
    if (argc == 1) {
        cout << "Please an input file: ";
        cin >> filename;
        ifstream infile(filename);  
        if (doesFileOpen(infile) == true) { 
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            cout << "File: " << filename << " opened sucessfully." << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            run(infile);
        } else {
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            cout << "Error - couldn't process " << filename << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;

            return 1;
        }  
    } else {
        filename = argv[1];
        ifstream argfile(filename);  
         if (doesFileOpen(argfile) == true) { 
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            cout << "File: " << filename << " opened sucessfully." << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            run(argfile);
        } else {
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            cout << "Error - couldn't process " << filename << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            return 1;
        }
    }    

    return 0;
}

void run(ifstream &infile){
    Stack workStack;
    string tempChar;
    vector <string> previousChar;
    while (!infile.eof()) {
        infile >> tempChar;
        string nextChar = infile.peek();    //look at the next character for evaluation 
        if(isNumber(tempChar)){
            workStack.push(stoi(tempChar));
        } 
        if(isOperator(tempChar)) {

            if((workStack.size > 2)){       //if the stack is greater than 2, there are too many numbers for an operation
                cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
                cout << "RPNC ERROR Invalid Expression: ";
                while(workStack.size != 0){
                    cout << workStack.pop() << " "; //output the failed numbers
                }
                cout << tempChar << endl; //output the operator too 
            } if (isOperator(nextChar)){   //if the next character is also an operator (two in a row) its invalid 
                cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
                cout << "RPNC ERROR Invalid Expression: ";
                while(workStack.size != 0){
                    cout << workStack.pop() << " "; //output the failed numbers
                }
                cout << tempChar << " " << nextChar << endl; //output the operator too 
            }
            
            
            else {    //the expression is valid
                evaluate(workStack.pop(), workStack.pop(), tempChar);
            }
        }        
    }
    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
}


bool isOperator(string ch) {
    if (ch == "+" || ch == "-" || ch == "*" || ch == "/" || ch == "^"){ //supported operators
        return true; 
    } else { 
        return false; 
    }
}

bool isNumber(string ch){
    string numbers = "0123456789";
        return !ch.empty() && ch.find_first_not_of(numbers) == std::string::npos;
}

//look at two numbers and their operator, and return the given math bit
// goes in num2 num1 because of stack
void evaluate(int num2, int num1, string op){
    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
    cout << "Evaluating: " << num1 << " " << num2 << " " << op << endl;

    int answer; 
    if(op == "+"){ 
        answer = num1 + num2; //answer is equal to the two numbers added
    } 
    if(op == "-"){ 
        answer = num1 - num2; // answer is equal to the two numbers subtracted
    }
    if(op == "*"){ 
        answer = num1 * num2; //answer is equal to the two numbers multiplied
    }
    if(op == "/"){ 
        answer = num2 / num1; //answer is equal to the two numbers divided
    }
    if(op == "^"){ 
        answer = pow(num1, num2); //answer is equal to num2^num1
    }
    
    cout << num1 << " " << op << " " << num2  << "         = " << answer << endl;
}
