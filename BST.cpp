#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void PARSE();

int main() {
  bool running = true;
  char command[10];
  char fileName[30];
  char input[10000];
  int count = 0;
  int modify[100];
  int size = 0;

  cout << "Binary Search Tree" << endl << endl;
  while (running == true) {
    memset(input, 0, 10000);
    memset(modify, 0, 100);
    size = 0;
    count = 0;
    cout << "Options: Run and Quit" << endl;
    cin.get(command, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(command, "Run") == 0) {
      cout << "File input or Manual input? ";
      cin.get(command, 10);
      cin.clear();
      cin.ignore(10000, '\n');
      if (strcmp(command, "File") == 0) {
	cout << endl << "What is the name of the file? ";
	cin.get(fileName, 30);
	cin.clear();
	cin.ignore(10000, '\n');
	streampos size;
	ifstream file(fileName, ios::in | ios:: binary | ios::ate);
	if (file.is_open()) {
	  size = file.tellg();
	  file.seekg(0, ios::beg);
	  file.read(input, size);
	  file.close();
	  //PARSE();
	  cout << "Input: ";
	}
      }
      else if (strcmp(command, "Manual") == 0) {
	cout << "Enter each number followed by a space:" << endl;
	char in[10000];
	cin.get(in, 10000);
	cin.clear();
	cin.ignore(1000000, '\n');
	//PARSE();
	cout << "Input: ";
      }
      else {
	cout << "Invalid input, restart." << endl << endl;
      }
    }
    else if (strcmp(command, "Quit") == 0) {
      cout << endl << "Quitting Program." << endl << endl;
      running = false;
    }
    else {
      cout << endl << "Input invalid, try again" << endl;
    }
  }
}
