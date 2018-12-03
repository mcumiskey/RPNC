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
#include <string.h>
#include <vector>
#include <cstdlib>


using namespace std;

//Linked list is the underlying data structure for my stack
class Node {
    public:
        string data;
        Node *next;
};

class LinkedList {
    private: 
        Node *head;

    public:
        LinkedList() {
            head = NULL;
        }

        bool empty() {
            return (head == NULL);
        }

        void push(string value) {
            Node *temp = new Node();
            temp->data = value;
            temp->next = head;
            head = temp;
        }

        string pop(){
            string temp = head->data;
            Node *oldHead = head;
            head = head->next;
            delete oldHead;
            return temp;
        }

        string peek() {
            if(!empty()){
                return head->data;
            } else {
                return "Error on peek.";
            }
        }
         //dumps out the contents of a list
        void display() {
            Node *temp = new Node;
            temp = head;
            while(temp != NULL) {
                cout << temp->data << "\n";
                temp = temp->next;
            }
        }
};

//Basic Stack
class Stack {
    private: 
     LinkedList data;

     public:
    int size = 0;

     bool empty() {
         return data.empty();
     }

     void push(string value) {
         cout << "pushing " << value << endl;
         data.push(value);
         size++;
     }

     string pop(){
         if (data.empty()) {
            return "Error on pop: Stack is empty";
         } else {
            size--;
            return data.pop();
         }       
     }

     string peek() {
         if (empty()) {
            return "Error on peek: Stack is empty";
         } else {
            return data.peek();
         }
     }

     void display(){
        data.display();
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

Stack Expressions_by_Line(ifstream &infile);
Stack parseLines(Stack expressions);


int main(int argc, char* argv[]){

    /* * * * * * * * * * * * * FILE INPUT * * * * * * * * * * * * * * */
    string filename;
    ifstream infile;
    Stack stackofExpressions;   //reads file line-by-line
    Stack stackOfElements;       //parses the expressions into one stack, separated by endExp
                                //this was done to successfully store the data in a way that kept expressioms 
                                //seperate in an easy and visual way. 

    //figure out if the file is an command line argument or a manual input, check it, and begin to run it
    if (argc == 1) {
        cout << "Please an input file: ";
        cin >> filename;
        ifstream infile(filename);  
        if (doesFileOpen(infile) == true) { 
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            cout << "File: " << filename << " opened sucessfully." << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            stackofExpressions = Expressions_by_Line(infile);
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
            stackofExpressions = Expressions_by_Line(argfile);
        } else {
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            cout << "Error - couldn't process " << filename << endl;
            cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - " << endl;
            return 1;
        }
    }
    /* * * * * * * * * * * * * * * PUSHING FROM LINE TO STACK * * * * * * * * * * * * * * * * */
    stackofExpressions.display();
    stackOfElements = parseLines(stackofExpressions);
    stackOfElements.display();

    return 0;
}

Stack Expressions_by_Line(ifstream &infile){
    Stack stackofExpressions;
    string newLine;
    string endExp = "YOUSHALLNOTPASS"; //  the end of each expression is marked for evaluation 

    while (!infile.eof()) {
        getline(infile, newLine); 
        stackofExpressions.push(newLine); //store line as one big string
        stackofExpressions.push(endExp); //mark where an expression ends
    }
    return stackofExpressions;
}

Stack parseLines(Stack expressions) {
    Stack inividualStack; // a stack of individual elements 
    string curWord; //one element in a line of expressions 
    string nonAphabetical = "0123456789+*-/"; //a string representation of non alphabetical characters 
    while(!expressions.empty()){
        string curLine = expressions.pop();
        cout <<  curLine << " is the current line." << endl;
        for(int j = 0; j < curLine.size(); j++){
            if(curLine.at(j) == nonAphabetical){    //if the char is not " " or a letter
                inividualStack.push(curLine.at(j)); //push single digit nonAlpha to the stack
            }
            if ((!(curLine.at(j+1) > curline.size())) //if j+1 is not out of bounds...
                &&(curLine.at(j) == nonAphabetical) 
                && (curLine.at(j+1) == nonAphabetical)){ // check for 2 digit numbers 
                inividualStack.push(curLine.substr(j, j+1)); //if found, add two digits to the stack
            }
            if ((!(curLine.at(j+2) > curline.size())) //if j+2 is not out of bounds...
                &&(curLine.at(j) == nonAphabetical) 
                && (curLine.at(j+1) == nonAphabetical)
                && (curLine.at(j+2) == nonAphabetical)){ // check for 3 digit numbers 
                inividualStack.push(curLine.substr(j, j+2)); //if found, add three digits to the stack
            } else {
                inividualStack.push(curLine); //curline will be "YOU SHALL NOT PASS"
            }
        }   
    }
    return inividualStack;
}