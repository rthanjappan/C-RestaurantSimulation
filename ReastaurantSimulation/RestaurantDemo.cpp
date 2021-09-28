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
#include "RestaurantDemo.h"
#include "Scanner.h"
using namespace std;

//main processing of restaurant demo
void RestaurantDemo::mainLine() {
	//initializing and getting configuration details	
	initialization();
	//checks whether the restaurant is configured successfully
	if (isConfigured == false) {
		return;
	}
	
	cout << "\n\nPlease enter the time restaurant opens : ";
	cin >> restaurantOpenTime;
	clockTime = restaurantOpenTime;
	currentTime = restaurantOpenTime;
	cin.get();
	
	isConfigured = true;
	system("pause");
	
	
}

//creating activities in the restaurant
void RestaurantDemo::createActivity() {
	
	unsigned seed = time(0);
	srand(seed);


	int y, maxValue = 15, minValue = 0;
	
	Time tempTime = getRandomTime(15, 0);

	
	if (customers.empty()) {
		currentTime = clockTime + tempTime;
	}
	else {
		currentTime = customers[customers.size()-1].getArrivalTime() + tempTime;
	}
	
	
	//random generating the size of the parties
	if (tableSize == 0) {
		return;
	}
	maxValue = tableSize, minValue = 1;
	y = (rand() % (maxValue - minValue + 1)) + minValue;//the partySize
	
	Sleep(1000);
	
	Customer cust("Sandy", currentTime, y);
	customers.push_back(cust);//adding the new customer to customers list
	waitingList.push_back(customers[customers.size() - 1]);//adding the new customer to waiting list
	
}
//randomly generating the time
Time RestaurantDemo::getRandomTime(int maxValue, int minValue) {
	unsigned seed = time(0);
	srand(seed);

	int y;
	y = (rand() % (maxValue - minValue + 1)) + minValue;//the time customer arrives
	

	string str = "00:", minuteStr = "";
	if (y < 10) {
		minuteStr = "0";
		minuteStr.append(to_string(y));
	}
	else {
		minuteStr.append(to_string(y));
	}
	
	str.append(minuteStr);
	str.append(":00");
	Time tempTime(str);
	return tempTime;
}
//opens the file specified
void RestaurantDemo::openFile(string filename, ifstream& file, string text) {

	
	file.open(filename);

	
		while (file.fail()) {
			cout << text + "  file open failes" << endl;
			cout << "Please enter the name of restaurant config file : ";
			string sFileName;
			getline(cin, sFileName);
			file.open(sFileName);
		}
		

	return;
}



//**Heading Lines

char PT1[] = "R E S T A U R A N T";
char HL1[] = "      ";
char HL2[] = "---------------------------------------------------";
void RestaurantDemo::PrnHeadings() {
	

	cout <<"\t"<<name<<"  "<<PT1 << endl;
	cout << endl << endl;
	//cout << HL1 << endl;
	cout << HL2 << endl;
	return;
}
//initializing the restaurant parameters
void RestaurantDemo::initialization() {
	bEndFlag = false;
	
	processConfigParams();
	if (bEndFlag == true) {
		return;
	}
	std::string s = " ";
	s.append(name);
	s.erase(s.find_last_not_of(" \n\r\t") + 1);
	int n = s.find_first_not_of(" \n\r\t") - 1;
	s.erase(0, n);
	strcpy_s(name,s.c_str());
	
	

	//opens the log file
	logFile.close();
	logFile.open("logFile.txt");
	while(logFile.fail()) {
		cout << "\n\nLog file open failes." << endl;
		cout << "Please enter the name of log file : " ;
		string sFileName;
		getline(cin, sFileName);
		logFile.open(sFileName);
	}
	writeIt();//write configuration parameters to log file

	int numCustomers;
	//clear the customers vector
	Customer::resetCUSTID();
	customers.clear();
	numPartySizes.clear();
	waitingList.clear();

	//initialize the Restaurant Type
	restType.setType(restaurantType);
	//initialize the Level of Business
	lOfBusiness.setLevel(levelOfBusiness);

	//initialize numPartySizes
	for (int i = 0; i < tableSize; i++) {
		numPartySizes.push_back(0);
	}

	int TotalCustomers, TotalParties;
	tables.clear();
	//initialize tables
	for (int i = 0; i < numTables; i++) {
		Table temp;
		temp.setTableNo(i);
		temp.setOccupied(false);
		tables.push_back(temp);
	}
	//create waitresses
	waitresses.clear();
	int waitressIDCount = 0;
	for (int i = 0; i < numProfessional; i++) {
		Waitress temp(waitressIDCount,2);
		waitresses.push_back(temp);
		waitressIDCount++;
	}

	for (int i = 0; i < numSeasoned; i++) {
		Waitress temp(waitressIDCount,1);
		waitresses.push_back(temp);
		waitressIDCount++;
	}
	for (int i = 0; i < numNewbies; i++) {
		Waitress temp(waitressIDCount,0);
		waitresses.push_back(temp);
		waitressIDCount++;
	}

	
}
//processing the configuration parameters
void RestaurantDemo::processConfigParams() {
	if (iFromUserChoice == 0) {//the choice is read configuration parameters from file
		openFile("RestaurantConfig.txt", inputFile, "Restaurant configuration ");
		if (inputFile.fail()) {
			bEndFlag = true;
			return;
		}
		else {
			
			readConfigFile();
			if (configureTheRestaurant() == false) {
				isConfigured = false;
				cout << "\n\nError in config file." << endl;
				cout << "Please enter correct data into \"RestaurantConfig.txt\"  file." << endl;
				cout << "The format is in \"restaurantData.txt\" file." << endl << endl;
				system("pause");
				bEndFlag = true;
				return;
			}
			else {
				isConfigured = true;
			}

		}
	}
	else if (iFromUserChoice == 1) {//the choice is read configuration parameters from the user
		getConfigParameters();
		while (configureTheRestaurant() == false) {
			isConfigured = false;
			cout << "\n\nError in config parameters." << endl;
			getConfigParameters();
			system("pause");
		}
		isConfigured = true;
	}

	
}

//end of run processing
void RestaurantDemo::eoj() {

	inputFile.close();
	logFile.close();
	cout << "\n ------< END OF RUN> -------------------" << endl;
	system("pause");
}


//reading the configuration parameters from the file
void RestaurantDemo::readConfigFile() {
	
	inputFile.get(name, 15);
	inputFile.get();
	inputFile>> levelOfBusiness >>
		numTables >> restaurantType >> tableSize;
	inputFile.get();
	inputFile >> numNewbies >> newbiesTime	;
	inputFile.get();
	inputFile >> numSeasoned >> seasonedTime;
	inputFile.get();
	inputFile >> numProfessional >> professionalTime;

	
	displayConfigParameters();

	
if (inputFile.eof() == true)
bEndFlag = true;
else
bEndFlag = false;

inputFile.close();
return;
}
//get configuration parameters form the user
void RestaurantDemo::getConfigParameters() {
	
	string strName;
	cout << "Please enter the name of the restaurant(14 characters in length) : ";
	getline(cin, strName);
	while (!(strName.length() < 15)){
		
			cout << "Please enter the name of the restaurant(14 characters in length) : ";
			getline(cin, strName);
					
	}
	strcpy_s(name, strName.c_str());

	
	cout << "Please enter the level of business (0.slow,1.busy,2.slammed) : ";
	levelOfBusiness = Scanner::getIntValue();
	while (levelOfBusiness < 0 || levelOfBusiness >2) {
		cout << "Please enter the level of business (0.slow,1.busy,2.slammed) : ";
		levelOfBusiness = Scanner::getIntValue();
	}
	cout << "Please enter the number of tables(greater than zero)  : ";
	numTables = Scanner::getIntValue();
	while (numTables <= 0) {
		cout << "Please enter the number of tables(greater than zero)  :  ";
		numTables = Scanner::getIntValue();
	}
	cout << "Please enter the restaurant type(0.Menu tier,1.Bistro,2.Gourmet)  : ";
	restaurantType = Scanner::getIntValue();
	while (restaurantType < 0 || restaurantType >2) {
		cout << "Please enter the restaurant type(0.Menu tier,1.Bistro,2.Gourmet)  :  ";
		restaurantType = Scanner::getIntValue();
	}
	cout << "Please enter the table size(1 to 4)  : ";
	tableSize = Scanner::getIntValue();
	while (tableSize <= 0 || tableSize >4) {
		cout << "Please enter the table size(1 to 4)  :  ";
		tableSize = Scanner::getIntValue();
	}

	
	getWaitressInfo("newbies", numNewbies, newbiesTime);
	getWaitressInfo("seasoned", numSeasoned, seasonedTime);
	getWaitressInfo("professional", numProfessional, professionalTime);

	displayConfigParameters();
}
//get the waitress information from the user
bool RestaurantDemo::getWaitressInfo(string waitressType, int &numWaitresses, int &time) {
	cout << "Please enter the number of " << waitressType << "(not less than zero) : ";
	numWaitresses = Scanner::getIntValue();
	while (numWaitresses < 0) {
		cout << "Please enter the number of " << waitressType << "(not less than zero) : ";
		numWaitresses = Scanner::getIntValue();
	}
	cout << "Please enter the service time of " << waitressType << "(greater than zero) : ";
	time = Scanner::getIntValue();
	while (time <= 0) {
		cout << "Please enter the service time of " << waitressType << "(greater than zero) : ";
		time = Scanner::getIntValue();
	}
	return true;
}

//configure and checking for valid parameters for the restaurant
bool RestaurantDemo::configureTheRestaurant() {
	bool flag = true;
	string str;
	try {
		if (!LevelOfBusiness::isValidLevel(levelOfBusiness)) {
			throw RestaurantDemo::InvalidDataException("The level of business at the restaurant is invalid.");
			//return false;
		}
		if (numTables <= 0) {
			throw RestaurantDemo::InvalidDataException("The number of tables must be greater than zero.");
			//return false;
		}
		if (!RestaurantType::isValidRestType(restaurantType)) {
			throw RestaurantDemo::InvalidDataException("The type of restaurant is invalid.");
			//return false;
		}
		if (tableSize <= 0) {
			throw RestaurantDemo::InvalidDataException("The size of the tables must be greater than zero");
			//return false;
		}
		if (numNewbies < 0) {
			throw RestaurantDemo::InvalidDataException("The number of newbies waitresses cannot be negative.");
			//return false;
		}
		if (newbiesTime <= 0) {
			throw RestaurantDemo::InvalidDataException("The serving time for newbie waitress must be greater than zero.");
			//return false;
		}
		if (numSeasoned < 0) {
			throw RestaurantDemo::InvalidDataException("The number of seasoned waitresses cannot be negative.");
			//return false;
		}
		if (seasonedTime <= 0) {
			throw RestaurantDemo::InvalidDataException("The serving time for seasoned waitress must be greater than zero.");
			//return false;
		}
		if (numProfessional < 0) {
			throw RestaurantDemo::InvalidDataException("The number of professional waitresses cannot be negative.");
			//return false;
		}
		if (professionalTime <= 0) {
			throw RestaurantDemo::InvalidDataException("The serving time for professional waitress must be greater than zero.");
			//return false;
		}
		int totalWaitresses = numNewbies + numSeasoned + numProfessional;
		if (totalWaitresses <= 0) {
			throw RestaurantDemo::InvalidDataException("No waitresses in the restaurant.");
		}
	}
	catch (RestaurantDemo::InvalidDataException e) {
		cout <<"\n\n"<< e.getMessage() << endl << endl;
		system("pause");
		return false;
	}
	catch (...) {
		cout << "Exception : Error in configuration file." << endl << endl;
		system("pause");
		return false;
	}
	
	return true;
}
//running the activities according to the clock
void RestaurantDemo::updateClockTime() {
	
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i].getLeft() == false) {
			lastCustomerServed = i;
			break;
		}
		
			lastCustomerServed = 0;
		
		
	}
	//checking for customer arrival
	for (int i = lastCustomerServed; i < customers.size(); i++) {

		if ((customers[i].getArrivalTime()).compareTo(clockTime) == 0) {
			cout << "\nThe customer " << customers[i].getCustID() <<
				"  arrives." << endl;
			logFile << "\nThe customer " << customers[i].getCustID() <<
				"  arrives." << endl;
			createActivity();



		}
		//checking for whether customer is seated
		if ((customers[i].getSeatedTime()).compareTo(clockTime) == 0) {
			cout << "\nThe customer " << customers[i].getCustID() <<
				"  is seated" << endl;
			logFile << "\nThe customer " << customers[i].getCustID() <<
				"  is seated" << endl;
			
			
		}
		//allocating waitress and serving the customer
		if ((customers[i].getServingTime()).compareTo(clockTime) == 0) {
			cout <<  "allocating waitress ID " <<
				customers[i].getWaitress().getWaitressID() << "(" <<
				customers[i].getWaitress().getLevelString() << ")"
				<< "  to customer " <<
				customers[i].getCustID() << endl;
			logFile  << "allocating waitress ID " <<
				customers[i].getWaitress().getWaitressID()<<"("<<
				customers[i].getWaitress().getLevelString()<<")"
				<< "  to customer " <<
				customers[i].getCustID() << endl;
			cout << "\nNow serving customer  number " << customers[i].getCustID()  << endl;
			logFile << "\nNow serving customer  number " << customers[i].getCustID() << endl;
			leavingRoutine(customers[i]);


		}
		//checking whether customer is leaving
		if ((customers[i].getLeavingTime()).compareTo(clockTime) == 0) {
			cout << "\nThe customer " << customers[i].getCustID() <<
				"  is leaving." << endl;
			logFile << "\nThe customer " << customers[i].getCustID() <<
				"  is leaving." << endl;
			customers[i].setLeft(true);
			tables[customers[i].getTableNo()].setOccupied(false);
			cout << "Vacating the table no " << (customers[i].getTableNo() + 1) << endl;
			logFile << "Vacating the table no " << (customers[i].getTableNo() + 1) << endl;
			for (int n = 0; n < waitresses.size(); n++) {
				if (customers[i].getWaitress() == waitresses[n]) {
					waitresses[n].setAvailable(true);
					cout << "deallocating waitress ID " <<
						customers[i].getWaitress().getWaitressID() <<
						" from customer " << customers[i].getCustID()
						<< endl;
					logFile << "deallocating waitress ID " <<
						customers[i].getWaitress().getWaitressID() <<
						" from customer " << customers[i].getCustID()
						<< endl;
				}
			}

		}

		//allocating customers from waiting list
		for (int j = 0; j < tables.size(); j++) {
			allocateFromWaitingList(tables[j].getTableNo());
		}
		//allocating waitresses for the customers
		for (int m = lastCustomerServed; m < customers.size(); m++) {
			if (customers[m].getSeated() == true){
				if (customers[m].getIsWaitressAllocated() == false) {
					allocateWaitress(customers[m], clockTime);
				}
			}

		}
		Sleep(300);

	}
}
//running the restaurant
void RestaurantDemo::runTheRestaurant() {
	bEndDay = false; finalReportLogFlag = false;
	//cout << "Run the restaurant " << endl;
	createActivity();
	allocateTable(customers[0], tables[0]);
	allocateWaitress(customers[0], customers[0].getArrivalTime());
	
	Time increment("00:01:00");
	/*Time restRunTime("00:45:00");
	Time restClosingTime = clockTime + restRunTime + increment;*/
	
	int count = 15;
	string choice = "a";
	
	//cin.get();
	while (tolower((choice.at(0))) != 'q') {
		updateClockTime();//running the restaurant activities
		count--;
		if (count == 0) {
			
			cout << "Do you want to continue (q for quit)  : ";
			
			
			getline(cin, choice);
			while (choice == "") {
				cout << "Do you want to continue (q for quit)  : ";
				getline(cin, choice);
			}
			count = 15;
		}
		clockTime = clockTime + increment;//incrementing  the clock time 
		cout << "clockTime : " << clockTime << endl;
		logFile << "clockTime : " << clockTime << endl;
	}
	//writing the customers details to log file
	for (int i = 0; i < customers.size(); i++) {
		logFile << customers[i] << endl;
	}
	//displaying the final report
	displayFinalReport();

	bEndDay = true;

}
//displaying the customer details
void RestaurantDemo::displayCustomers() {
	if (customers.empty()) {
		cout << "No customers available.\n\n" << endl;
	}
	else {
		
		for (int i = 0; i < customers.size(); i++) {
			cout << customers[i] << "\n\n\n";
			if ((i+1) % 10 == 0) {
				system("pause");
			}
			
		}
	}
	
}
//doing the activities of leaving the restaurant
void RestaurantDemo::leavingRoutine(Customer& cust) {
	vacateTable(cust, cust.getTableNo());
	
}
//allocating the table to the customer
void RestaurantDemo::allocateTable(Customer& cust, Table& table) {
	if (table.getOccupied() == false) {
			cust.setTableNo(table.getTableNo());
			table.setOccupied(1);
			Time increment("00:01:00");
			cust.setSeatedTime(cust.getArrivalTime()+increment);
			cust.setSeated(true);
				
	}

}
//allocating the table to the customer at specified time
void RestaurantDemo::allocateTable(Customer& cust, Table& table, Time timeOfActivity) {
	Time increment("00:01:00");
	
	if (table.getOccupied() == false) {
		
		if (cust.getArrivalTime().compareTo(timeOfActivity-increment) == -1) {
			cust.setTableNo(table.getTableNo());
			table.setOccupied(1);
			cust.setSeatedTime(timeOfActivity + increment);
			cust.setSeated(true);
			
			
			cout << "\n\nallocating the table "<<
				(cust.getTableNo()+1)<<" for customer  : " << cust.getCustID() << endl;
			logFile << "\n\nallocating the table " <<
				(cust.getTableNo()+1) << " for customer  : " << cust.getCustID() << endl; 
				
		}
		
	}
	
	
}
//allocating the waitress
void RestaurantDemo::allocateWaitress(Customer& cust, Time actTime) {
	Time increment("00:01:00");
	if (cust.getIsWaitressAllocated() == true) {
		return;
	}
	for (int i = 0; i < waitresses.size(); i++) {
		if (waitresses[i].getAvailable() == true) {
			if (cust.getSeated() == true) {
				waitresses[i].setAvailable(false);
				cust.setWaitress(waitresses[i]);
				cust.setIsWaitressAllocated(true);
				cust.setServingTime(actTime + increment);

				break;
			}
		}
	}
	

}
//adding the customer to waiting list
void RestaurantDemo::addToWaitingList(Customer& cust) {
	waitingList.push_back(cust);

}
//vacating the table
void  RestaurantDemo::vacateTable(Customer& cust, int tableNo) {
	

	if (tableNo == -1) {
		return;
	}
	else {
		
		 if (cust.getIsWaitressAllocated() == true) {
			Time minSpent = getRandomTime(15, 10);
			int spentTime = restType.getCookingTime() + 
				cust.getWaitress().getServiceTime()*cust.getPartySize();
			Time temp(0, spentTime, 0);
			Time vacatingTime = cust.getServingTime() + temp;
			cust.setLeavingTime(vacatingTime);

			
		}

		
	}
	
}
//allocate table to the customers from waiting list
void RestaurantDemo::allocateFromWaitingList(int tableNo) {
	

	if (!waitingList.empty()) {
		
		for (int i = 0; i < customers.size(); i++) {
			if (waitingList[0].getCustID() == customers[i].getCustID()) {
				allocateTable(customers[i], tables[tableNo], clockTime);
				if (customers[i].getSeated() == true) {
					waitingList.erase(waitingList.begin());
				}
					
			}
		}

		
		
	}
}
//writing the resaturant parameters to the log file
void RestaurantDemo::writeIt() {
	logFile << "The name of the restaurant : " << name << "\n";
	logFile << "The level of business : " << levelOfBusiness << "\n";
	logFile << "The number of tables in the restaurant : " << numTables << "\n";
	logFile << "The type of the restaurant : " << restaurantType << "\n";
	logFile << "The size of the tables : " << tableSize << endl << endl;
	logFile << "The waitress information : " << endl;
	logFile << "number of Newbies level : " << numNewbies <<
		"  serving time of newbies : " << newbiesTime << endl;
	logFile << "number of Seasoned level : " << numSeasoned <<
		"   serving time of seasoned : " << seasonedTime << endl;
	logFile << "number of Professional level : " << numProfessional <<
		"  professionalTime:  " << professionalTime << endl;
	return;
}
//displays the final report
void RestaurantDemo::displayFinalReport() {
	//cout << "\n\n" << endl;
	//The values of the configuration parameters
	displayConfigParameters();
	//The average waiting time for parties
	displayAveWaitingTime();
	//The average number of parties waiting for a table
	displayAveWaitingParties();
	//The average turnaround time : the time from when the party arrives to when they leave the restaurant
	displayAveTurnAroundTime();

	finalReportLogFlag = true;
}
//displays the configuration parameters
void RestaurantDemo::displayConfigParameters() {
	cout << "\n\nThe name of the restaurant : " << name << "\n";
	cout << "The level of business : " << 
		lOfBusiness.getLevelString(levelOfBusiness) << "\n";
	cout << "The number of tables in the restaurant : " << numTables << "\n";
	cout << "The type of the restaurant : " << restType.getTypeString(restaurantType) << "\n";
	cout<<"The size of the tables : "<< tableSize << endl<<endl;
	cout << "The waitress information : " << endl;
	cout << "number of Newbies level : " << numNewbies <<
		"  serving time of newbies : " << newbiesTime << endl;
	cout << "number of Seasoned level : " << numSeasoned <<
		"   serving time of seasoned : " << seasonedTime << endl;
	cout << "number of Professional level : " << numProfessional <<
		"  professionalTime:  " << professionalTime << endl;
}
//displays average waiting time for the parties
void RestaurantDemo::displayAveWaitingTime() {
	Time total("00:00:00"),ave("00:00:00");
	int count = 0;
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i].getArrivalTime().compareTo(customers[i].getSeatedTime()) != 0) {
			if (customers[i].getSeated() == true) {
				total = total + (customers[i].getSeatedTime() - customers[i].getArrivalTime());
				count++;
			}
			
		}
	}
	
	if (count == 0) {
		cout << "There are no customers to process." << endl;
		if (finalReportLogFlag == false) {
			logFile << "There are no customers to process." << endl;
		}
	} 
	else{
		ave = ave.getAverage(total, count);
		cout << "\n\nThe average waiting time for parties :  " << ave << endl;
		if(finalReportLogFlag == false) {
			logFile << "\n\nThe average waiting time for parties :  " << ave << endl;
		}
		
	}
	
}
//The average number of parties waiting for a table
void RestaurantDemo::displayAveWaitingParties() {
	Time total("00:00:00"), ave("00:00:00"),incr("02:00:00");
	int totalParties = 0;
	
	for (int i = 0; i < customers.size(); i++) {
		if (customers[i].getArrivalTime().compareTo(customers[i].getSeatedTime()) != 0) {
			if (customers[i].getSeated() == true) {
				totalParties = totalParties + 1;
				
			}

		}
	}
	
	if (numTables == 0) {
		cout << "There is no tables in the restaurant." << endl;
		if (finalReportLogFlag == false) {
			logFile << "There is no tables in the restaurant." << endl;
		}
	}
	else {
		int average = TotalParties / numTables;
		cout << "\n\nThe average number of parties waiting for a table : "
			<< average << endl;
		if (finalReportLogFlag == false) {
			logFile << "\n\nThe average number of parties waiting for a table : "
				<< average << endl;
		}
	}
	
}
//The average turnaround time : the time from when the party arrives to when they leave the restaurant
void RestaurantDemo::displayAveTurnAroundTime() {
	Time total("00:00:00"), ave("00:00:00");
	int count = 0;
	for (int i = 0; i < customers.size(); i++) {
		
			if (customers[i].getLeft() == true) {
				total = total + (customers[i].getLeavingTime() - customers[i].getArrivalTime());
				count++;
			}

		
	}
	Time restRunTime = clockTime - restaurantOpenTime;
	cout << "\n\nThe restaurant was open for "  << 
		restRunTime << " hours. "<< endl;
	if (finalReportLogFlag == false) {
		
		logFile << "\n\nThe restaurant was open for " << restRunTime << " hours. " << endl;
	}
	if (count == 0) {
		cout << "There are no customers to process." << endl;
		if (finalReportLogFlag == false) {
			
			logFile << "There are no customers to process." << endl;
		}
	}
	else {
		ave = ave.getAverage(total, count);
		cout << "\n\nThe average turnaround time :  " << ave << endl;
		
		if (finalReportLogFlag == false) {
			logFile << "\n\nThe average turnaround time :  " << ave << endl;
		}
	}
	
}



