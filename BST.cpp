#include <iostream>
#include <cstring>

using namespace std;

void PARSE();

int main() {
  bool running = true;
  char command[10];

  cout << "Binary Search Tree" << endl << endl;
  while (running == true) {
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
	
      }
      else if (strcmp(command, "Manual") == 0) {
	
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
      cout << "Input invalid, try again" << endl;
    }
  }
}
