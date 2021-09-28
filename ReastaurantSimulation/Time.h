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
using namespace std;

#pragma once
#ifndef TIME_H
#define TIME_H

class Time {
public:
	//default constructor
	Time() {
		seconds = 0;
		minutes = 0;
		hours = 0;
	}
	//constructor with arguments
	Time(int h, int m, int s) {
		setSeconds(s);
		setMinutes(m);
		setHours(h);
	}
	//copy constructor
	Time(const Time& obj) {
		hours = obj.hours;
		minutes = obj.minutes;
		seconds = obj.seconds;

	}
	//constructs  Time object from a string 
	Time(string str) {
		if (setTime(str) == -1) {
			cout << "Error : invalid time string.";
		
		}
	}
	bool setHours(int h) {
		if (h < 0 || h>24) {
			//throw "Invalid  Hours value.";
			return false;
		}
		hours = h;
		return true;
	}
	bool setMinutes(int m) {
		if (m < 0 || m>59) {
			//throw "Invalid  Minutes value.";
			return false;
		}
		minutes = m;
		return true;
	}
	bool setSeconds(int s) {
		if (s < 0 || s>59) {
			// throw "Invalid  Seconds value.";
			return false;
		}
		seconds = s;
		return true;
	}
	int setTime( string str) {
		vector<string> tokens;
		tokenize(str, ':', tokens);
		if (tokens.size() != 3) {
						
			return -1;

		}
		for (int i = 0; i < tokens.size(); i++) {
			if (tokens[i].length() != 2) {
				
				return -1;
			}
			
		}
		int h, m, s;
			try {
				 h = stoi(tokens[0]);
				  m = stoi(tokens[1]);
				  s = stoi(tokens[2]);
				  if (h < 0 || h>24) {
					  //throw "Invalid  Hours value.";
					  return -1;
				  }
				  if (m < 0 || m>59) {
					  //throw "Invalid  Minutes value.";
					  return -1;
				  }
				  if (s < 0 || s>59) {
					 // throw "Invalid  Seconds value.";
					  return -1;
				  }

				  hours = h;
				  minutes = m;
				  seconds = s;
			}
			catch (invalid_argument e) {
				cout <<e.what()<< endl;
				return -1;
			}
			
			
			return 0;
		
	}
	Time getAverage(Time time, int total) {
		
		int ave;
		//get time in total seconds
		int totalSeconds = time.hours * 60 * 60 + time.minutes * 60 + time.seconds;
		//cout <<"Total seconds :"<< totalSeconds<<endl;

		ave = totalSeconds / total;
		//cout << "Ave seconds :" << ave << endl;

		Time t3;
		t3.minutes = ave / 60;
		t3.hours = t3.minutes / 60;
		t3.minutes = t3.minutes % 60;
		t3.seconds = ave % 60;

		return t3;
	}
	//tokenizing the strings
	void tokenize(string& s, char delim, vector<string>& tokens) {
		int tokenStart = 0;

		int delimPosition = s.find(delim);

		while (delimPosition != string::npos) {
			string tok = s.substr(tokenStart, delimPosition - tokenStart);

			tokens.push_back(tok);

			delimPosition++;
			tokenStart = delimPosition;

			delimPosition = s.find(delim, delimPosition);

			if (delimPosition == string::npos) {
				string tok = s.substr(tokenStart, delimPosition - tokenStart);

				tokens.push_back(tok);

			}
		}

	}
	
	//overloaded operator functions
	Time operator  +  (const Time &);//overload +
	Time operator  -  (const Time &);//overload -
	bool operator ==  (const Time &);//overload -

	int compareTo(Time);//if 2 times are equal returns 0
	//if first time is greater than second time returns 1
	//if first time is less than second time returns -1

	//overload cout’s << operator and cin’s >> operator
	friend ostream &operator << (ostream &strm, const Time &obj) {
		string str;
		if (abs(obj.hours) < 10) {
			str.append(to_string(0));
			str.append(to_string(obj.hours));
		}
		else {
			str.append(to_string(obj.hours));
		}
		str.append(":");
		if (abs(obj.minutes) < 10) {
			str.append(to_string(0));
			str.append(to_string(obj.minutes));
		}
		else {
			str.append(to_string(obj.minutes));
		}
		str.append(":");
		if (abs(obj.seconds) < 10) {
			str.append(to_string(0));
			str.append(to_string(obj.seconds));
		}
		else {
			str.append(to_string(obj.seconds));
		}
		
		strm << str;
		return strm;
	}
	friend istream &operator >> (istream &strm, Time &obj) {
		//Prompt user for the time string
		string timeStr;
		//cout << "Please enter the time(hh:mm:ss) :  ";
		strm >> timeStr;
		bool flag = false;
		while (!flag) {
			try {
				if (obj.setTime(timeStr) == -1) {
					cout << "\nInvalid format for time.";
				}
				else {
					
					flag = true;
					break;
				}
			}
			catch (string s) {
				cout << s << endl;
			}
			catch (invalid_argument e) {
				cout << e.what()<<endl;
			}
			cout << "\nPlease enter the time(hh:mm:ss) :  ";
			strm >> timeStr;
		}
		

		return strm;

	}
	string to_TimeString() {
		string str;
		if (abs(hours) < 10) {
			str.append(to_string(0));
			str.append(to_string(hours));
		}
		else {
			str.append(to_string(hours));
		}
		str.append(":");
		if (abs(minutes) < 10) {
			str.append(to_string(0));
			str.append(to_string(minutes));
		}
		else {
			str.append(to_string(minutes));
		}
		str.append(":");
		if (abs(seconds) < 10) {
			str.append(to_string(0));
			str.append(to_string(seconds));
		}
		else {
			str.append(to_string(seconds));
		}
		return str;
	}
private :
	
	int seconds;
	int minutes;
	int hours;
};
#endif // !TIME_H