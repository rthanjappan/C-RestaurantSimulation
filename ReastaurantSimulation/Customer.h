
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
#include "Time.h"
#include "Waitress.h"


using namespace std;

#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H
class Customer {
	static int STARTID;
public :
	//default constructor
	Customer(){
		custID = STARTID++;
		name = "";
		arrivalTime.setTime("00:00:00");
		partySize = 0;

		seatedTime.setTime("00:00:00");
		servingTime.setTime("00:00:00");
		leavingTime.setTime("00:00:00");

		waitress = Waitress();
		isWaitressAllocated = false;
		tableNo = -1;
		left = false;
	}
	//constructor with arguments
	Customer(string n, Time arrTime, int pSize) {
		custID = STARTID++;
		name = n;
		arrivalTime = arrTime;
		partySize = pSize;

		seatedTime.setTime("00:00:00");
		servingTime.setTime("00:00:00");
		leavingTime.setTime("00:00:00");

		waitress = Waitress();
		isWaitressAllocated = false;
		tableNo = -1;
		left = false;
		

	}
	//resets starting customer ID
	static void resetCUSTID(){
		STARTID = 1001;
	}
	//sets the customer ID
	void setCustomerID(int id) {
		custID = id;
	}
	//sets the name
	void setName(string n) {
		name = n;
	}
	//sets the arrival time
	void setArrivalTime(Time aTime) {
		arrivalTime = aTime;
	}
	//sets the party size
	void setPartySize(int value) {
		partySize = value;
	}
	//sets the seated time
	void setSeatedTime(Time value) {
		seatedTime = value;
	}
	//sets the leaving time
	void setLeavingTime(Time value) {
		leavingTime = value;
	}
	//sets the serving time
	void setServingTime(Time value) {
		servingTime = value;
	}
	//sets the table number
	void setTableNo(int value) {
		tableNo = value;
	}
	//sets whether customer is seated
	void setSeated(bool value) {
		seated = value;
	}
	//sets whether the customer has left the restaurant
	void setLeft(bool value) {
		left = value;
	}
	//allocates the waitress
	void setWaitress(Waitress value) {
		waitress = value;
	}
	//accessor for waitress
	Waitress getWaitress() const {
		return waitress;
	}
	//sets whether the waitress is allocated
	void setIsWaitressAllocated(bool value) {
		isWaitressAllocated = value;
	}
	bool getIsWaitressAllocated() const {
		return isWaitressAllocated;
	}
	//accessors for the fields
	int getCustID() {
		return custID;
	}
	string getName() {
		return name;
	}
	Time getArrivalTime() {
		return arrivalTime;
	}
	int getPartySize() {
		return partySize;
	}
	
	Time getSeatedTime() {
		return seatedTime;
	}
	Time getLeavingTime() {
		return leavingTime;
	}
	Time getServingTime() {
		return servingTime;
	}
	int getTableNo() {
		return tableNo;
	}
	bool getSeated() {
		return seated;
	}
	bool getLeft() {
		return left;
	}

	
	//overload cout’s << operator 
	friend ostream &operator << (ostream &strm, const Customer &obj) {
		string str;
		strm << "Customer ID : " << obj.custID <<
			" Name : " << obj.name <<
			" Arrival Time : " << obj.arrivalTime <<
			" Seated Time : " << obj.seatedTime <<
			" Serving Time : " << obj.servingTime <<
			" LeavingTime : " << obj.leavingTime <<
			" Party Size : " << obj.partySize <<
			" Table No : " << obj.tableNo<<
		  " waitressType : " << ((Waitress)obj.getWaitress()).getLevelString();

		return strm;
	}
private :
	int custID;
	string name;
	
	Time arrivalTime;
	Time seatedTime;
	Time servingTime;
	Time leavingTime;
	int partySize;
	
	int tableNo;
	int waitressType;
	Waitress waitress;
	bool isWaitressAllocated;
	bool seated;
	bool left;
};
#endif // !CUSTOMER_H