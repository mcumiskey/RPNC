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
            return NULL; //not good
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
bool isValidNext(string ch); //checks for an number and operator after an evaluate in case a expression is more than one step 
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

    while (!infile.eof()) {
        infile >> tempChar;
        if(isNumber(tempChar)){
            workStack.push(stoi(tempChar));
        } 
        if(isOperator(tempChar) && (workStack.size > 2)){       //if the stack is greater than 2, there are too many numbers for an operation
                cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
                cout << "RPNC ERROR Invalid Expression: ";
                while(workStack.size != 0){
                    cout << workStack.pop() << " "; //output the failed numbers
                }
                cout << tempChar << endl; //output the operator too 
            if (isOperator(tempChar) && (workStack.isEmpty())) {   //if there is a number and no operator, invalid  
                cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
                cout << "RPNC ERROR Invalid Expression: ";
                while(workStack.size != 0){
                    cout << workStack.pop() << " "; //output the failed numbers
                }
                cout << tempChar << " " << endl; //output the operator too 
            }
            else {    //the expression is valid
                evaluate(workStack.pop(), workStack.pop(), tempChar);
            }
        }        
    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
    }
}

bool isValidNext(string ch){

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

//checks the stream lines and returns a vector of instructions to do the math magic

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
