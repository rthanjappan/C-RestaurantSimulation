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
#ifndef RESTAURANTTYPE_H
#define RESTAURANTTYPE_H
class RestaurantType {
	
public:
	static int types[];//type ids
	static int numTypes;//number of types of restaurants
	//default constructor
	RestaurantType() {
		setType(0);
	}
	//constructoer with arguments
	RestaurantType(int t) {
		if (t >= 0 && t < numTypes) {
			setType(t);
		}
		
	}
	//accessors for fields
	int getType() {
		return type;
	}
	int getCookingTime() {
		return cookingTime[type];
	}
	void setType(int t) {
		if (t < 0 || t>=numTypes) {
			string str = "Invalid type of restaurant. ";
			str.append(to_string(t));
			str.append("  is given");
			cout << str;
			return;
		}
		type = t;
	}
	//checking whether a type is a valid restaurant type
	static bool isValidRestType(int value) {
		for (int i = 0; i < numTypes; i++) {
			if (types[i] == value) {
				return true;
			}

		}
		return false;
	}
	string getTypeString(int value) {
		if (value >= 0 && value < numTypes) {
			return sTypes[value];
		}
		return "";
	}
private:
	int type=-1;
	string sTypes[3] = { "Menu tiers","bistro","gourmet" };
	int cookingTime[3] = { 5,10,15 };//cooking time of the restaurant types
	
};

#endif // !RESTAURANTTYPE_H