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

using namespace std;

class Stack {
    public:
    int a[10];
    int top;

    Stack() {
        top = 0;
    }
    bool isEmpty(){
        return top == 0;
    }
    void push (int newElement) {
        if (top == 10) {
            cout << "Error: stack is full." << endl;
        } else {
            a[++top] = newElement;
        }
    }

    int pop () {
        if (top == 0) {
            cout << "Error: stack is empty." << endl;
            return NULL; //not good
        } else {
            int returnElement = a[top];
            --top;
            return returnElement;
        }
    }

    int peek() {
        return a[top];
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
bool isOperator(string ch); //checks to see if a character is an operator 
bool isNumber(string ch);
int evaluatePart(int num1, int num2, string op); //does math on a specific part 

int main(int argc, char* argv[]){

    /* * * * * * * * * * * *  * * * * FILE INPUT * * * * * * * * * * * * * * * * * */
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
    /* * * * * * * * * * * * * * * PUSHING FROM LINES TO INDIVIDUAL STACK * * * * * * * * * * * * * * * * */
    

    /* * * * * * * * * * * * * * * EVALUATE FROM NDIVIDUAL STACK * * * * * * * * * * * * * * * * */


    return 0;
}

void run(ifstream &infile){
    Stack workStack;
    string tempChar;
    while (!infile.eof()) {
        infile >> tempChar;
        cout << tempChar << endl;
        if(isNumber(tempChar)){
            cout << "I'm a number" << endl;
            workStack.push(stoi(tempChar));
        } 
        if(isOperator(tempChar)) {
        cout << "I'm an operator" << endl;
        cout << evaluatePart(workStack.pop(), workStack.pop(), tempChar) << endl;
        cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
        }
    }
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
int evaluatePart(int num1, int num2, string op){
    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
    cout << "Evaluating: " << num1 << " " << num2 << " " << op << endl;

    int answer; 
    if(op == "+"){ 
        answer = num2 + num1; //answer is equal to the two numbers added
    } 
    if(op == "-"){ 
        answer = num2 - num1; // answer is equal to the two numbers subtracted
    }
    if(op == "*"){ 
        answer = num2 * num1; //answer is equal to the two numbers multiplied
    }
    if(op == "/"){ 
        answer = num2 / num1; //answer is equal to the two numbers divided
    }
    if(op == "^"){ 
        answer = pow(num2, num1); //answer is equal to num2^num1
    }
    return answer; //returns the answer
}
