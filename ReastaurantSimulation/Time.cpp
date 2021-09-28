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

//calculating the time difference
Time  Time::operator  -  (const Time &right) {
	Time temp, start;
	start.seconds = right.seconds;
	start.minutes = right.minutes;
	start.hours = right.hours;
	
	//get time in total seconds
	int seconds1 = hours * 60 * 60 +minutes * 60 + seconds;
	int seconds2 = right.hours * 60 * 60 + right.minutes * 60 + right.seconds;

	int totalSeconds = seconds1 - seconds2;
	if (compareTo(right) == -1) {
		totalSeconds = totalSeconds + 86400;
	}
	//extract time in Hours, Minutes and Seconds
	Time t3;
	t3.minutes = totalSeconds / 60;
	t3.hours = t3.minutes / 60;
	t3.minutes = t3.minutes % 60;
	t3.seconds = totalSeconds % 60;
	
	temp = t3;
	return temp;
}
//overload +
Time Time::operator  +  (const Time &right) {
	Time temp;
	//adding the entered times
	temp.seconds = seconds + right.seconds;
	temp.minutes = minutes+ right.minutes + (temp.seconds / 60);
	temp.hours = hours + right.hours + (temp.minutes / 60);
	temp.minutes = temp.minutes % 60;
	temp.seconds = temp.seconds % 60;

	temp.hours = temp.hours % 24;
	return temp;
}


bool Time::operator ==  (const Time &right)//overload ==
	{
		if ((hours == right.hours) &&
			(minutes == right.minutes) &&
			(seconds == right.seconds))
			return true;
		else
			return false;
			
		
	}
int Time::compareTo(Time right)//if 2 times are equal returns 0
	//if first time is greater than second time returns 1
	//if first time is less than second time returns -1
{
	Time t1 = *this, t2 = right;
	if (*this == right) {
		return 0;
	}
	else {
		int seconds1 = t1.hours * 60 * 60 + t1.minutes * 60 + t1.seconds;
		int seconds2 = t2.hours * 60 * 60 + t2.minutes * 60 + t2.seconds;
		int totalSeconds = seconds1 - seconds2;
		if (totalSeconds > 0) {
			return 1;
		}
		else {
			return -1;
		}
	}
}