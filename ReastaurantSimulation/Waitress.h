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

#include "Time.h"
#include "Table.h"
using namespace std;
#pragma once
#ifndef WAITRESS_H
#define WAITRESS_H
class Waitress {

public:
	//constructor with arguments
	Waitress(int id,int lev) {
		waitressID = id;
		level = lev;
		available = true;

		
	}
	//default constructor
	Waitress() {
		waitressID = -1;
		level = 0;
		available = true;
	}
	//accessors and mutators for the fields
	void setWaitressID(int value) {
		waitressID = value;
	}
	int getSkillLevel() {
		return level;
	}
	int setSkillLevel(int lev) {


		if (lev >= numTypesOfWaitresses) {
			return -1;
		}
		level = lev;
		return 0;
	}
	int getServiceTime() {

		return waitressTime[level];
	}
	int setServiceTime(int lev, int time) {
		if (lev >= numTypesOfWaitresses) {
			return -1;
		}
		waitressTime[level] = time;
		return 0;
	}
	void setAvailable(bool value) {
		available = value;
	}
	int getWaitressID() {
		return waitressID;
	}
	bool getAvailable() {
		return available;
	}
	
	string getLevelString() const {
		
		
		return sLevel[level];
	}
	bool operator ==  (const Waitress &right)//overload ==
	{
		Waitress w = right;
		if (getWaitressID()	== w.getWaitressID())
			return true;
		else
			return false;


	}
private:
	int waitressID;
	int level;
	int numTypesOfWaitresses = 3;
	string sLevel[3] = {"newbies","seasoned","professional" };
	int waitressTime[3] = {6,4,2};
	bool available;
};
#endif // !WAITRESS_H
