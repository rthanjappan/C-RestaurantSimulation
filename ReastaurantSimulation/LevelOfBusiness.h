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
using namespace std;
#pragma once
#ifndef LEVELOFBUSINESS_H
#define LEVELOFBUSINESS_H
class LevelOfBusiness {
	static int nLevels;//number of levels
	static int levels[3];//levels ids
public:
	//accessors for fields
	int getLevel() {
		return level;
	}
	
	string getLevelString(int value) {
		if (value >= 0 && value < numLevels) {
			return sLevels[value];
		}
		return "";
	}
	//sets the level of the restaurant
	void setLevel(int lev) {
		if (lev < 0 || lev>=numLevels) {
			string str = "Invalid type of restaurant. ";
			str.append(to_string(lev));
			str.append("  is given");
			cout << str;
			return;
		}
		level = lev;
		
	}
	//calculates the number of occupied tables
	int calcOccupiedTables(int numTables) {
		if (level == 0) {
			occupied = (int)(numTables * 0.5);

		}
		else if (level = 1) {
			occupied = (int)(numTables * 0.75);
		}
		else if (level = 2) {
			occupied = (int)numTables;
		}
		else {
			string str = "Invalid level of business. ";
			str.append(to_string(level));
			str.append("  is given");
			throw str;
		}
		return occupied;
	}
	//calculates the party sizes
	int calcPartySizes(int numTables) {
		if (level == 0) {
			totalPartiesOccupied = (int)(calcOccupiedTables(numTables)*0.75);
		}
		else if (level = 1) {
			totalPartiesOccupied = (int)(calcOccupiedTables(numTables)*0.50);
		}
		else if (level = 2) {
			totalPartiesOccupied = (int)(calcOccupiedTables(numTables)*0.75);
		}
		else {
			string str = "Invalid level of business. ";
			str.append(to_string(level));
			str.append("  is given");
			throw str;
		}
		return occupied;
	}
	//checks whether a level is valid level
	static bool isValidLevel(int value) {
		for (int i = 0; i < nLevels; i++) {
			if (levels[i] == value) {
				return true;
			}

		}
		return false;
	}
private:
	int numLevels = 3;
	int level;
	string sLevel;
    
	string sLevels[3] = { "slow","busy","slammed" };
	int occupied;
	int totalPartiesOccupied;
};

#endif // !LEVELOFBUSINESS_H