//Author: Nathan Zou
//Date: 4/21/22
//Done with help from Chris Zou, Stefan Ene, and Jayden Huang
/*
Other Resources Used:
Previously done Heap: https://github.com/AgentSlimy/Heap
Printing Tree: https://www.techiedelight.com/c-program-print-binary-tree
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

struct Trunk { //Used for printing
    Trunk *previous;
    char* str;

    Trunk(Trunk* previous, char* str) {
        this->previous = previous;
        this->str = str;
    }
};

void showTrunks(Trunk* p) { //Uesd for printing
    if (p == NULL) 
        return;

    showTrunks(p->previous);

    cout << p->str;
}

void PARSE(char* in, int* modify, int& count);
void BUILD(Node*& head, Node*& current, Node*& previous, int value);
void PRINT(Node* root, Trunk *prev, bool isLeft);
void SEARCH(Node* current, int &data);
Node* DELETE();

int main() {
    bool running = true;
    char command[10];
    char fileName[30];
    char input[10000];
    int count = 0; //Number of chars
    int modify[100];
    int modSize = 0; //Size of modify array
    cout << "Binary Search Tree" << endl << endl;
    while (running == true) {
        memset(input, 0, 10000);
        memset(modify, 0, 100);
        modSize = 0; 
        count = 0; //Clear char count
        cout << "Options: Run and Quit" << endl;
        cin.get(command, 10);
        cin.clear();
        cin.ignore(10000, '\n');
        if (strcmp(command, "Run") == 0) {
            cout << "File input or Manual input? ";
            cin.get(command, 10);
            cin.clear();
            cin.ignore(10000, '\n');
            bool tree = false;
            if (strcmp(command, "File") == 0) { //File command, for file input of numbers
                //Essentially the same code from my previous Heap project for file input
                tree = true;
                cout << endl << "What is the name of the file? ";
                cin.get(fileName, 30);
                cin.clear();
                cin.ignore(10000, '\n');
                streampos size;
                ifstream file(fileName, ios::in | ios::binary | ios::ate);
                if (file.is_open()) {
                    size = file.tellg();
                    file.seekg(0, ios::beg);
                    file.read(input, size);
                    file.close();
                    PARSE(input, modify, count); //Parse input to modify array
                    cout << "Input: ";
                    for (int i = 0; i < 100; i++) {
                        if (modify[i] != 0) {
                            cout << modify[i] << " ";
                            modSize++;
                        }
                    }
                    cout << endl << "Size: " << modSize << endl;
                }
            }
            else if (strcmp(command, "Manual") == 0) { //Manual command, for manual input of numbers
                tree = true;
                cout << "Enter each number followed by a space:" << endl;
                char in[10000];
                cin.get(in, 10000);
                cin.clear();
                cin.ignore(1000000, '\n');
                //Parse input by spaces
                PARSE(in, modify, count); //Parse input to modify array
                cout << "Input: ";
                for (int i = 0; i < 100; i++) {
                    if (modify[i] != 0) {
                        cout << modify[i] << " ";
                        modSize++;
                    }
                }
                cout << endl << "Size: " << modSize << endl;
            }
            else {
                tree = false;
                cout << "Invalid input, restart." << endl << endl;
            }
            if (tree == true) { //Tree creation
                Node* head = NULL;
                Node* current = NULL;
                Node* previous = NULL;
                for (int i = 0; i < modSize; i++) {
                    if (modify[i] != 0) {
                        current = head;
                        BUILD(head, current, previous, modify[i]);
                    }
                }
                cout << endl << "Tree Built" << endl << endl;
		PRINT(head, NULL, false);
		cout << endl << endl;
		bool inTree = true;
		char treeCom[10];
    int searchInput;
		while (inTree == true) {
		  cout << "Tree Options: Search, Add, Delete, Quit" << endl;
		  cin.get(treeCom, 10);
		  cin.clear();
		  cin.ignore(10000, '\n');
		  if (strcmp(treeCom, "Search") == 0) {
		    cout << "Search Value: ";
        cin >> searchInput;
        cin.clear();
        cin.ignore(10000, '\n');
        SEARCH(head, searchInput);
		  }
		  else if (strcmp(treeCom, "Add") == 0) {
		    int value;
        cout << "Add Value: ";
        cin >> value;
        cin.clear();
        cin.ignore(10000, '\n');
        Node* current = NULL;
        Node* previous = NULL;
        current = head;
        BUILD(head, current, previous, value);
        cout << endl << value << " added to tree." << endl << endl;
        PRINT(head, NULL, false);
        cout << endl;
		  }
		  else if (strcmp(treeCom, "Delete") == 0) {
		    //Delete
		  }
		  else if (strcmp(treeCom, "Quit") == 0) {
		    cout << "Quitting Current Tree" << endl << endl;
		    inTree = false;
		  }
		  else {
		    cout << endl << "Invalid Command, Try Again." << endl;
		  }
		}
            }
        }
        else if (strcmp(command, "Quit") == 0) {
            cout << endl << "Quitting Program." << endl;
            running = false;
        }
        else {
            cout << endl << "Input invalid, try again" << endl;
        }
    }
}

void PARSE(char* in, int* modify, int& count) { //Parse function, takes in input
    int x = 0;  //keeps track of # of chars before space
    for (int i = 0; i < strlen(in); i++) {
        if (in[i] == ' ') {
            if (x == 1) {
                int temp = 0;
                temp = in[i - 1] - '0';
                modify[count] = temp;
                count++;
                x = 0;
            }
            else {
                int temp = 0;
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (in[i - x + a] - '0');
                }
                modify[count] = temp;
                count++;
                x = 0;
            }
        }
        else {
            int temp = 0;
            x++;
            if (i == strlen(in) - 1) {  //last possible pair of chars
                for (int a = 0; a < x; a++) {
                    temp = 10 * temp + (in[i + a + 1 - x] - '0');
                }
                modify[count] = temp;
                count++;
            }
        }
    }
}

void BUILD(Node*& head, Node*& current, Node*& previous, int value) { //Build functions, adds nodes with the value to the tree recursively
    if (head == NULL) {
        head = new Node();
        head->setData(value);
        return;
    }
    else {
        if (value < current->getData()) { //Lower value goes left
            previous = current;
            current = current->getLeft();
            if (current == NULL) { //If empty, insert
                current = new Node();
                current->setData(value);
                previous->setLeft(current);
                return;
            }
            else { //If not empty, keep going
                BUILD(head, current, previous, value);
            }
        }
        else {
            previous = current;
            current = current->getRight(); //Higher value goes right
            if (current == NULL) { //If empty, insert
                current = new Node();
                current->setData(value);
                previous->setRight(current);
                return;
            }
            else { //If not empty, keep going
                BUILD(head, current, previous, value);
            }
        }
    }
}

void PRINT(Node* root, Trunk *previous, bool isLeft) { //Print functions, prints out tree
  if (root == NULL) {
    return;
  }
  char* prevStr = (char*)("    ");
  Trunk *trunk = new Trunk(previous, prevStr);
  PRINT(root->getLeft(), trunk, true);
  if (!previous) {
    trunk->str = (char*)("---");
  }
  else if (isLeft) {
    trunk->str = (char*)(".---");
    prevStr= (char*)("   |");
  }
  else {
    trunk->str = (char*)("'---");
    previous->str = prevStr;
  }
  showTrunks(trunk);
  cout << " " << root->getData() << endl;

  if (previous) {
    previous->str = prevStr;
  }
  trunk->str = (char*)("   |");
  PRINT(root->getRight(), trunk, false);
}

void SEARCH(Node* current, int& data) { //Search function, used to find a specific value in a given tree
    while (current->getData() != data && current != NULL) {
        if (current != NULL) {
            if (current->getData() > data) {
                current = current->getLeft();
            }
            else {
                current = current->getRight();
            }
        }
        if (current == NULL) {
            break;
        }
    }
    if (current != NULL) {
        if (current->getData() == data) {
            cout << "The element is present in the list!" << endl << endl;
        }
    }
    else {
        cout << "The element is not present in the list!" << endl << endl;
    }
}
