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

using namespace std;

#pragma once
#ifndef TABLE_H
#define TABLE_H
class Table {

public:
	//default constructor
	Table() {
		tableNo = -1;
		occupied = false;
		
	}
	//accessors and mutators for the fields
	void setTableNo(int no) {
		tableNo = no;
	}
	
	void setOccupied(bool value) {
		occupied = value;
	}
	
	
	int getTableNo() {
		return tableNo;
	}
	
	bool getOccupied() {
		return occupied;
	}
	//checks whether the table is available
	bool isAvailable() {
		if (occupied==false) {
			return true;
		}
		else {
			return false;
		}
	}
	//overload cout’s << operator and cin’s >> operator
	friend ostream &operator << (ostream &strm, const Table &obj) {
		
		strm <<"Table No : "<<obj.tableNo
			<< "    occupied  : " << obj.occupied;

		return strm;
	}
	
	
private:
	int tableNo;
	bool occupied;
};

#endif // !TABLE_H