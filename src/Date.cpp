#include<iostream>
#include"Date.h"
#include<string>
#include<math.h>
#include<sstream>
using namespace std;
Date::Date() {
	year_ = 0;
	month_ = 0;
	day_ = 0;
	hour_ = 0;
	minute_ = 0;
}
Date::Date(int y, int m, int d, int h, int mi) {
	year_ = y;
	month_ = m;
	day_ = d;
	hour_ = h;
	minute_ = mi;
}
int Date::getYear(void) const {
	return year_;
}
void Date::setYear(int year) {
	year_ = year;
}
int Date::getMonth(void) const {
	return month_;
}
void Date::setMonth(int month) {
	month_ = month;
}
int Date::getDay(void) const {
	return day_;
}
void Date::setDay(int day) {
	day_ = day;
}
int Date::getHour(void) const {
	return hour_;
}
void Date::setHour(int hour) {
	hour_ = hour;
}
int Date::getMinute(void) const {
	return minute_;
}
void Date::setMinute(int minute) {
	minute_ = minute;
}
bool Date::isValid(Date date) {
	if (date.getHour() < 0 || date.getHour() > 23 || date.getMinute() < 0 || date.getMinute() > 59)
    		return false;
  	if (date.getMonth() <= 0 || date.getDay() <= 0 || date.getYear() <= 0||date.getYear() > 9999)
    		return false;
  	if (date.getMonth() == 1) {
    		if (date.getDay() > 31) {
      			return false;
    		}
  	}
  	if (date.getMonth() == 2) {
    		if ((date.getYear() % 4 == 0 && date.getYear() % 100 != 0) || date.getYear() % 400 == 0) {
      			if (date.getDay() > 29)
        			return false;
    		} else {
      			if (date.getDay() > 28)
        			return false;
    		}
  	}
	if (date.getMonth() == 4||date.getMonth() == 6||date.getMonth() == 9||date.getMonth() == 11)
		if (date.getMonth() > 30)
			return false;
	if (date.getMonth() == 3||date.getMonth() == 5||date.getMonth() == 7||date.getMonth() == 8||date.getMonth() == 10||date.getMonth() == 12)
		if (date.getMonth() > 31)
			return false;
	if (date.getMonth() > 12)
		return false;
	return true;
}	
Date Date::stringToDate(string dateString) {
	Date date; // 2014-07-04/14:57
  	int num, n[17], i;
  	for (i = 0; i < 16; ++i)
    		n[i] = dateString[i] - '0';
  	n[i] = '\0';
  	num = n[0] * 1000 + n[1] * 100 + n[2] * 10 + n[3];
  	date.setYear(num);
  	num  = n[5] * 10 + n[6];
  	date.setMonth(num);
  	num = n[8] * 10 + n[9];
  	date.setDay(num);
  	num = n[11] * 10 + n[12];
  	date.setHour(num);
  	num = n[14] * 10 + n[15];
  	date.setMinute(num);
  	return date;
}
string Date::dateToString(Date date) {
	string ss;
  	int n = date.getYear();
	ss = "0000-00-00/00:00";
  	ss[3] = n % 10 + '0';
  	ss[2] = (n % 100 - n % 10) / 10 + '0';
  	ss[1] = (n % 1000 - n % 100) / 100 + '0';
  	ss[0] = (n - n % 1000) / 1000 + '0';
  	n = date.getMonth();
  	ss[5] = (n - n % 10) / 10 + '0';
  	ss[6] = n % 10 + '0';
  	n = date.getDay();
  	ss[8] = (n - n % 10) / 10 + '0';
  	ss[9] = n % 10 + '0';
  	n = date.getHour();
  	ss[11] = (n - n % 10) / 10 + '0';
  	ss[12] = n % 10 + '0';
  	n = date.getMinute();
  	ss[14] = (n - n % 10) / 10 + '0';
  	ss[15] = n % 10 + '0';
  	return ss;
}
Date& Date::operator=(const Date& date) {
	year_ = date.getYear();
	month_ = date.getMonth();
	day_ = date.getDay();
	hour_ = date.getHour();
	minute_ = date.getMinute();
	return *this;
}
bool Date::operator==(const Date& date) const {
	if (year_ == date.getYear()&&month_ == date.getMonth()&&day_ == date.getDay()&&hour_ == date.getHour()&&minute_ == date.getMinute())
		return true;
	return false;
}
bool Date::operator>(const Date& date) const {
	if (year_ > date.getYear())
		return true;
	if (year_ < date.getYear())
		return false;
	if (month_ > date.getMonth())
		return true;
	if (month_ < date.getMonth())
		return false;
	if (day_ > date.getDay())
		return true;
	if (day_ < date.getDay())
		return false;
	if (hour_ > date.getHour())
		return true;
	if (hour_ < date.getHour())
		return false;
	if (minute_ > date.getMinute())
		return true;
	if (minute_ < date.getMinute())
		return false;
	return false;
}
bool Date::operator<(const Date& date) const {
	if (year_ < date.getYear())
		return true;
	if (year_ > date.getYear())
		return false;
	if (month_ > date.getMonth())
		return true;
	if (month_ > date.getMonth())
		return false;
	if (day_ < date.getDay())
		return true;
	if (day_ > date.getDay())
		return false;
	if (hour_ < date.getHour())
		return true;
	if (hour_ > date.getHour())
		return false;
	if (minute_ < date.getMinute())
		return true;
	if (minute_ > date.getMinute())
		return false;
	return false;
}
bool Date::operator>=(const Date& date) const {
	return (*this) > date||(*this) == date;
}
bool Date::operator<=(const Date& date) const {
	return (*this) < date||(*this) == date;
}

