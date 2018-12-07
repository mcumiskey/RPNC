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
            cout << "pushing: " << newElement << endl;
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
            cout << "popping: " << returnElement << endl;
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

void run(ifstream &infile); //pops everything from the file stream line by line
void parseLine(string currentLine); //looks at a line, uses a stack to store numbers, and evaluates what if it is valid
bool isOperator(string ch); //checks to see if a string is an operator 
bool isNumber(string ch);   //checks to see if string is a number
bool isNumber(char ch);
int  howManyDigits(string ch, int position); //checks to see if a number has multiple digits, and if it does, returns the digits (1, 2, or 3)
int  evaluate(int num2, int num1, string op); //does math on a specific part 

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
    string tempString;
    while (!infile.eof()) {
        getline(infile, tempString);
        parseLine(tempString);
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

bool isNumber(char ch){
    string numbers = "0123456789";
    for(int i = 0; i < numbers.size(); i++){
        if(ch == numbers.at(i)){
            return true;
        }
    }
    return false;
}

int  howManyDigits(string ch, int position){
    int digits = 1;
    int nextPos = position + 1;
    int twoNext = position + 2;
    int threeNext = position + 3;
    string numbers = "0123456789";
    if((nextPos != ch.size()) && (isNumber(ch.at(nextPos)))){ //if that char is a number
            digits = 2;
        if((twoNext != ch.size()) && (isNumber(ch.at(twoNext)))){ //if that char is a number
            digits = 3;
            if((threeNext != ch.size()) && (isNumber(ch.at(threeNext)))){ //if that char is a number
                digits = 4;
            }
        }
    }

    return digits;
}

//function to evaluate the expression
void parseLine(string curExpression){
    Stack workStack;        //stores and sends data to be evaluated 
    string curChar;
    int answer;

    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
    cout << "Evaluating: " << curExpression << endl;

    for(int i = 0; i < curExpression.size(); i++) {             //while there are more chars in a line....
        Stack lastAnswer;                                       //store the answers for the line, in case of multiple operatons 
        cout << "curExpression is: " << curExpression << endl;
        curChar = curExpression.at(i);

        if(isNumber(curChar)){    
            cout << "im number " << curChar << endl;             
            if(howManyDigits(curExpression, i) > 1){       
                workStack.push(stoi(curExpression.substr(i, i + howManyDigits(curExpression, i))));
                curExpression.erase(i, i + howManyDigits(curExpression, i));           
            } else {
                workStack.push(stoi(curChar));                  //otherwise, just add 1-digit number to the stack
                curExpression.erase(i);                
            }
        }
        if(isOperator(curChar)) {
            cout << "I'm an operator" << endl;
            if(workStack.isEmpty()){                            //if there are no numbers, error 
                cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
                cout << "RPNC ERROR Invalid Expression: empty stack ";
                cout << curChar << endl; //output the operator 
            }
            if((workStack.size == 1) && (lastAnswer.size == 1)){//if you have a number, an answer and an operator...
                evaluate(lastAnswer.pop(), workStack.pop(), curChar);
                lastAnswer.push(answer);
            }
            if (workStack.size == 1){
                cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
                cout << "RPNC ERROR Invalid Expression: not enough ";
                cout << workStack.pop() << " " << curChar << endl; //output the operator 
            }
            if(workStack.size > 2){                            //if there is an operator and more than two operands, send error
                cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
                cout << "RPNC ERROR Invalid Expression: numbers ";
                while(!workStack.isEmpty()){
                    cout << workStack.pop() << " "; //output the failed numbers
                }
                cout << curChar << endl; //output the operator too 
            } 
            else {
                answer = evaluate(workStack.pop(), workStack.pop(), curChar);
                lastAnswer.push(answer);
            }
        }
    }
}
//look at two numbers and their operator, and return the given math bit
// goes in num2 num1 because of stack weirdness
int evaluate(int num2, int num1, string op) {
    cout << "IM BEING EVALUATED" << endl;
    cout << num1 << " " << num2 << " " << op << endl;

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
    
    return answer;
}
