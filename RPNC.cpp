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

using namespace std;

//Linked list is the underlying data structure for my stack
class Node {
    public:
        int data;
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
        void push(int value) {
            Node *temp = new Node();
            temp->data = value;
            temp->next = head;
            head = temp;
        }
        int pop(){
            int temp = head->data;
            Node *oldHead = head;
            head = head->next;
            delete oldHead;
            return temp;
        }
        int peek() {
            if(!empty()){
                return head->data;
            } 
        }
};

//Basic Stack
class Stack {
    private: 
     LinkedList data;
     int s = 0;

     public:

     bool empty() {
         return data.empty();
     }

     void push(int value) {
         cout << "pushing " << value << endl;
         data.push(value);
         s++;
     }

     int pop(){
         if (data.empty())    
         {
            cout << "Error on pop: Stack is empty" << endl;
            return -99;
         } else {
            s--;
            return data.pop();
         }       
     }

     int peek() {
         if (empty()) {
            cout << "Error on peek: Stack is empty" << endl;
            return -99;
         } else {
            return data.peek();
         }
     }
};

int main(int argc, char* argv[]){
}
