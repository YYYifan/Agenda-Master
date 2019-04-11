#include<iostream>
#include<string>
#include"Meeting.h"
using namespace std;
Meeting::Meeting() : startDate_(), endDate_() {
	sponsor_ = "";
	participator_ = "";
	title_ = "";
}
Meeting::Meeting(string sponsor, string participator, Date startTime, Date endTime, string title) {
	sponsor_ = sponsor;
	participator_ = participator;
	startDate_ = startTime;
	endDate_ = endTime;
	title_ = title;
}
string Meeting::getSponsor(void) const {
	return sponsor_;
}
void Meeting::setSponsor(std::string sponsor) {
	sponsor_ = sponsor;
}
string Meeting::getParticipator(void) const {
	return participator_;
}
void Meeting::setParticipator(string participator) {
	participator_ = participator;
}
Date Meeting::getStartDate(void) const {
	return startDate_;
}
void Meeting::setStartDate(Date startTime) {
	startDate_.setYear(startTime.getYear());
	startDate_.setMonth(startTime.getMonth());
	startDate_.setDay(startTime.getDay());
	startDate_.setHour(startTime.getHour());
	startDate_.setMinute(startTime.getMinute());
}
Date Meeting::getEndDate(void) const {
	return endDate_;
}
void Meeting::setEndDate(Date endTime) {
	endDate_.setYear(endTime.getYear());
	endDate_.setMonth(endTime.getMonth());
	endDate_.setDay(endTime.getDay());
	endDate_.setHour(endTime.getHour());
	endDate_.setMinute(endTime.getMinute());
}
string Meeting::getTitle(void) const {
	return title_;
}
void Meeting::setTitle(std::string title) {
	title_ = title;
}

