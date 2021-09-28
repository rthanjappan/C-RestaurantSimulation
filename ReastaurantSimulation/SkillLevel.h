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

using namespace std;
#pragma once
#ifndef SKILLLEVEL_H
#define SKILLLEVEL_H
class SkillLevel {

public:
	//accessors and mutators for the fields
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
private:
	int level;
	int numTypesOfWaitresses = 3;
	string sLevel[3] = { "newbies","seasoned","professional" };
	int waitressTime[3] = { 6,4,2 };//service time of waitresses

};
#endif // !SKILLLEVEL_H
