// Program : Restaurant Simulation
//Programmer : Rosemol Thanjappan
//Date : 3/30/2019

#include <conio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include<time.h>
#include<vector>
#include<Windows.h>

#include"Customer.h"
#include "Time.h"
#include "Table.h"
#include"SkillLevel.h"
#include "Waitress.h"
#include "LevelOfBusiness.h"
#include "RestaurantType.h"
#include "RestaurantDemo.h"
#include "Scanner.h"
using namespace std;



class MainProcess
{
public:
	void mainMenu(void);
	RestaurantDemo  rD1;
private:
	int iChoice;

	void showMenu(void);
	void enterChoice(void);
	void makeSelection(void);
};

int main(void)
{		
	
	MainProcess MP;
	MP.mainMenu();

	return 0;
}

//processing the main menu
void MainProcess::mainMenu(void)
{
	showMenu();
	enterChoice();
	while (iChoice != 6)
	{
		makeSelection();
		showMenu();
		enterChoice();
	}
	rD1.eoj();
	return;
}
//showing the main menu
void MainProcess::showMenu(void)
{
	system("cls");
	cout << "\n\t         Welcome to Restaurant Simulation program";
	cout << "\n\n\t          Main Menu";
	cout << "\n\n\t          Select one:";
	cout << "\n\n\t          1. Configuring the restaurant from file.";
	cout << "\n\n\t          2. Configuring the restaurant from user.";
	cout << "\n\n\t          3. Running the restaurant.";
	cout << "\n\n\t          4. View customer details.";
	cout << "\n\n\t          5. Final report";
	cout << "\n\n\t          6. exit";
	cout << "\n\n\t          Enter choice (1 - 6) ===> ";
	return;
}

//reading the choice
void MainProcess::enterChoice(void)
{
	
	iChoice = Scanner::getIntValue();
	while (iChoice < 1 || iChoice > 6)
	{
		cout << "\nERROR...re-enter choice (1 - 6) ===> ";
		iChoice = Scanner::getIntValue();
	}
	return;
}
//selecting the corresponding program according to users choice
void MainProcess::makeSelection(void)
{

	// Clear Screen before printing Headings
	system("cls");
	switch (iChoice)
	{
	case 1:
		cout << "       Configuring the restaurant from file\n\n " << endl;
		rD1.iFromUserChoice = 0;
		rD1.mainLine();
		system("pause");
		break;
	case 2:
		cout << "       Configuring the restaurant from the user\n\n " << endl;
		rD1.iFromUserChoice = 1;
		rD1.mainLine();
		system("pause");
		break;
	case 3:
		
		
		if (rD1.isConfigured == true) {
			rD1.PrnHeadings();
			cout << "\n      Running the restaurant\n\n " << endl;
			rD1.runTheRestaurant();
		}
		else {
			cout << "The restaurant is not configured yet." << endl;
			cout << "Please configure the restaurant." << endl;
			cout << "Please use choice 1 or 2 from the menu.\n\n" << endl;
		}
		
		system("pause");
		break;
	case 4:
		if (rD1.isConfigured == true) {
			rD1.PrnHeadings();
			cout << "\n     Display customer details.\n\n " << endl;
			rD1.displayCustomers();
		}
		else {
			cout << "No customers yet.";
			cout << "The restaurant is not configured or it is not run yet." << endl;
			cout << "Please configure the restaurant and run it." << endl;
			cout << "Please use choice 1 or 2 from the menu.\n\n" << endl;
		}
		

		system("pause");
		break;

	case 5:
		
		
		if (rD1.isConfigured == true) {
			rD1.PrnHeadings();
			cout << "\n       Final report " << endl;
			rD1.displayFinalReport();
		}
		else {
			cout << "The restaurant is not configured yet." << endl;
			cout << "Please configure the restaurant." << endl;
			cout << "Please use choice 1 or 2 from the menu.\n\n" << endl;
		}
		system("pause");
		break;
	
	}

	return;
}


//Grade : 100/100