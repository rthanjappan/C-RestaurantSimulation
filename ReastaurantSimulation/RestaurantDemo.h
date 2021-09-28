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
//#include <ctime>
#include"Customer.h"
#include "Time.h"
#include "Table.h"
#include"SkillLevel.h"
#include "Waitress.h"
#include "LevelOfBusiness.h"
#include "RestaurantType.h"
#include "Scanner.h"
using namespace std;

#pragma once
#ifndef RESTAURANTDEMO_H
#define RESTAURANTDEMO_H
class RestaurantDemo {

public:
	void mainLine();
	void runTheRestaurant();
	void displayFinalReport();
	bool isConfigured = false;
	int iFromUserChoice = 0;
	void displayCustomers();
	void PrnHeadings();
	void eoj();
	

private:
	ifstream inputFile; 
	ofstream logFile;
	bool bEndFlag;

	char name[16];
	int levelOfBusiness;
	LevelOfBusiness lOfBusiness;
	int numTables;
	int restaurantType;
	RestaurantType restType;
	vector<Waitress> waitresses;

	
	bool bEndDay;
	vector<Table> tables;
	vector<Customer> waitingList;
	int numNewbies, numSeasoned, numProfessional;
	int newbiesTime, seasonedTime, professionalTime;
	int tableSize;
	int numCustomers;
	vector<int> numPartySizes;
	int TotalCustomers, TotalParties;
	vector<Customer> customers;
	Time restaurantOpenTime;
	Time currentTime;
	Time clockTime;
	int  lastCustomerServed=0;
	bool finalReportLogFlag = false;
	

	int iChoice;
	void initialization();
	
	
	void openFile(string, ifstream&, string);
	void readConfigFile();
	void getConfigParameters();
	void processConfigParams();
	bool getWaitressInfo(string, int &, int &);
	
	void createActivity();
	Time getRandomTime(int, int);

	//running the restaurant
	void updateClockTime();
	
	void leavingRoutine(Customer &);
	
	void vacateTable(Customer &, int);
	void allocateTable(Customer &, Table&);
	void allocateTable(Customer&, Table&, Time);
	void addToWaitingList(Customer &);
	void allocateFromWaitingList(int);
	void allocateWaitress(Customer&, Time);
	bool configureTheRestaurant();
	
	void displayConfigParameters();
	void displayAveWaitingTime();
	void displayAveWaitingParties();
	void displayAveTurnAroundTime();
	
	void writeIt();
	class InvalidDataException {
	public:
		InvalidDataException() :InvalidDataException("Exception occured") {}
		InvalidDataException(string exStr) {
			exceptionStr = exStr;
		}
		string getMessage() {
			return exceptionStr;
		}
	private:
		string exceptionStr;

	};


};
#endif // !RESTAURANTDEMO_H