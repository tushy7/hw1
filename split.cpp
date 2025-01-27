/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
/* Add a prototype for a helper function here if you need */
void append(Node*& in, Node*& eveOdd);


void split(Node*& in, Node*& odds, Node*& evens) {
  if (in == nullptr){
    return;
  }
  if(in -> value % 2 == 0) {
    append(in, evens);
  }
  else {
    append(in, odds);
  }
  return split(in, odds, evens);
}

/* If you needed a helper function, write it here */
void append(Node*& in, Node*& eveOdd) {
  Node* tmp = in -> next; 

  if (eveOdd == nullptr) { //check if even/odd are set to NULL (meaning they are empty)
    eveOdd = in; //set even/odd linked list to proper node, which "in" is currently pointing to
    eveOdd -> next = nullptr; //make the added nodes "next" pointer, point to null meaning it doesn't point to anything else
  }
  else {
    append(in, eveOdd->next); //find the last element in the even/odd linked list
    return;
    
    eveOdd -> next = in; //make the current last element's "next" pointer, point to what "in" points to 
    eveOdd = eveOdd -> next; //go to the next node
    eveOdd -> next = nullptr; //set next node's "next" pointer to null so it doesn't point to anything else
  }
  in = tmp; //after moving the node "in" points to, move in to the next node
}