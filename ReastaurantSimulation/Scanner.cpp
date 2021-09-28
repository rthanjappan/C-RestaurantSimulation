#include <iostream>
#include "Scanner.h"
using namespace std;
//getting an integer value from the user
int Scanner::getIntValue() {
	string choice = "a";
	int iChoice = 0;
	bool flag = false;

	while (flag == false) {
		getline(cin, choice);
		if (choice == "\n") {
			continue;
		}
		try {
			iChoice = stoi(choice);
			flag = true;
			
		}
		catch (invalid_argument e) {
			cout << "The value entered is not a valid integer." << endl;
			cout << "Please enter an integer(-2,147,483,648 to 2,147,483,647)  : ";
			flag = false;

			
		}
		catch (out_of_range e) {
			cout << "The value entered is too big for an integer." << endl;
			cout << "Please enter an integer(-2,147,483,648 to 2,147,483,647)  : ";
			flag = false;

			
		}
		catch (...) {
			cout << "An exception occured." << endl;
			cout << "Please enter an integer (-2,147,483,648 to 2,147,483,647): ";
			flag = false;
			
		}
	}
	return iChoice;
}