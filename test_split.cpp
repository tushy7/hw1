/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ -g -Wall split.cpp test_split.cpp -o split_test
*/

#include "split.h"

#include <iostream>
#include <string>

using namespace std;

void printList(std::string title, Node* head) {
	std::cout << "[" << title << "]\t";
	int count = 0;
	while (head) {
		std::cout << count << ":" << head->value << " ";
		head = head->next;
		count++;
	}
	std::cout << std::endl;
}

Node* createList(int* values, int size) {
	if (!values || size == 0)
		return nullptr;

	Node* head = new Node(values[0], nullptr);
	Node* current = head;
	for (int i = 1; i < size; i++) {
		current->next = new Node{values[i], nullptr};
		current = current->next;
	}
	return head;
}

Node* deleteList(Node* head) {
	if (!head)
		return nullptr;
	while (head) {
		Node* next = head->next;
		delete head;
		head = next;
	}
	return nullptr;
}

void checkNums(Node* head, bool checkOdd) {
	while (head) {
		if (checkOdd) {
			ASSERT_TRUE(head->value % 2 == 1);
		} else {
			ASSERT_TRUE(head->value % 2 == 0);
		}
		head = head->next;
	}
}

void run(int* vals, int size) {
	std::cout << "[START_RUN]\n";
	Node* in = nullptr;
	Node* odds = nullptr;
	Node* evens = nullptr;
	in = createList(vals, size);
	printList("IN", in);
	split(in, odds, evens);
	printList("ODDS", odds);
	printList("EVENS", evens);
	printList("IN_AFTER", in);

	// checks
	checkNums(odds, true);
	checkNums(evens, false);
	ASSERT_FALSE(in);

	// cleanup
	deleteList(odds);
	deleteList(evens);
	deleteList(in);
	std::cout << "[END_RUN]\n";
}

TEST(Split, Consecutive) {
	int set1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	run(set1, 10);

	int set2[] = {1, 2, 5, 6, 7, 20, 21, 29, 65, 101};
	run(set2, 10);
}

TEST(Split, Odd) {
	int set1[] = {1, 3, 5, 7, 9};
	run(set1, 5);
}

TEST(Split, Even) {
	int set1[] = {2, 4, 6, 8, 10};
	run(set1, 5);
}

TEST(Split, Empty) {
	int set1[] = {};
	run(set1, 0);
}

TEST(Split, Repeating) {
	int set1[] = {1, 1, 1, 1, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5};
	run(set1, 16);
}

TEST(Split, Single) {
	int set1[] = {1};
	run(set1, 1);

	int set2[] = {2};
	run(set2, 1);
}

int main(int argc, char* argv[]) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}