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

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cmath>
#include <vector>

using namespace std;

class Stack {
    public:
    int a[10];
    int size;
    int top;

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
            //cout << "Pushing: " << newElement << endl;
            top = newElement;
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
            //cout << "Popping: " << returnElement << endl;
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

void run(ifstream &infile);     //pops everything from the file streams and works math magic
bool isValid(string line);      //checks to make sure the file can be safely parsed
int parseLine(string line);     //looks at the line provided by run and evaluates
bool isOperator(char ch);       //checks to see if a char is an operator
bool isNumber(string ch);       //checks if a string is a number
int evaluate(int num2, int num1, char op); //does math on a specific part 

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
    string tempString;
    while (!infile.eof()) {
        getline(infile, tempString);
        if(isValid(tempString)){
            int answer;
            cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
            cout << "Evaluating: " << tempString << endl;
            answer = parseLine(tempString);
            cout << "The answer is: " << answer << endl;
        } else {
            cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
            cout << "Evaluating: " << tempString << endl;
            cout << "RPNC ERROR Invalid Expression: " << tempString << endl;
        }
    }
    cout << "+ + + + + + + + + + + + + + + + + + + + + + + + + + + " << endl;
}

//this function checks if a given expression can be evaluated 
bool isValid(string line){
    
    vector <string> tokens;             //vector is used bc no actual calculations need to be done on numbers, we just need
                                        //to split by whitespace + know if there is a number or an operator 
    int numOperators = 0;
    int numNumbers = 0;
    string sep = " ";
    size_t start = 0, end = 0;
    while ((end = line.find(sep, start)) != std::string::npos) {
        tokens.push_back(line.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(line.substr(start));

    for(int j = 0; j < tokens.size(); j ++){ //if there are two operates next to each other, error 
        if(isNumber(tokens.at(j))){
            numNumbers++;
        } else {
            numOperators++;
        }
    }

    if((numOperators <= 1) && (numNumbers <=1)){    //if there is less than one number or operator, cannot be true
        return false;
    }
    if(numNumbers - numOperators != 1){             //if there is more than 2 operators per number, cannot be true
        return false;
    }
    
    return true;
}


//this function takes a (valid) expression, and splits it up to be evaluated 
int parseLine(string line){
    int length = line.size();
    char exp[length];                 //array for expression
    char buffer[length];              //char array for spaces
    int i, num1, num2, j, space;      //variables for operations
    Stack workStack;

    strcpy(exp, line.c_str());       //copy string to char array to parse
    
    //parses expression
    j = 0;
    //parses the expression and inserts them into the stack
    for(i = 0; i < length; i++){
        //checks how long the expression is
        if(exp[i] >= '0' && exp[i] <= '9'){
            buffer[j++] = exp[i];                       //inserts into array
        }
        else if(exp[i] == ' '){                         //checks for spaces
            if(j > 0){                                  //if j is greater than 0
                buffer[j] = '\0';                       // j is equal to '\0'
                space = atoi(buffer);                   //space is equal to the space
                workStack.push(space);                  //push into stack
                j = 0;                                  //j = 0;
            }
        }
        
        //performs the operation on the expression
        else if(isOperator(exp[i])){
            num1 = workStack.pop(); //num1 is equal to the top of stack
            num2 = workStack.pop(); //num2 is equal to the top of stack
            workStack.push(evaluate(num1, num2, exp[i])); //performs the operations of the expression
        }
    }
    
    //returns answer 
    return workStack.pop();
}

//check if something is an operator 
bool isOperator(char ch) {
    if (ch =='+' || ch =='-' || ch =='*' || ch =='/' || ch == '^'){ //supported operators
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
int evaluate(int num1, int num2, char op){
    int answer; 
    if(op == '+'){
        answer = num2 + num1; //answer is equal to the two numbers added
    } 
    if(op == '-'){ 
        answer = num2 - num1; // answer is equal to the two numbers subtracted
    }
    if(op == '*'){ 
        answer = num2 * num1; //answer is equal to the two numbers multiplied
    }
    if(op == '/'){ 
        answer = num2 / num1; //answer is equal to the two numbers divided
    }
    if(op == '^'){ 
        answer = pow(num2, num1); //answer is equal to num2^num1
    }
    return answer;
}