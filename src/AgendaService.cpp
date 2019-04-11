#include<iostream>
#include<string>
#include"AgendaService.h"
using namespace std;
AgendaService::AgendaService() {
	storage_ = NULL;
}
AgendaService::~AgendaService() {
	delete storage_;
	storage_ = NULL;
}
bool AgendaService::userLogIn(string userName, string password) {
	list<User> lu;
	lu = storage_->queryUser([&](const User& user)->bool{
        	if (user.getName() == userName&&user.getPassword() == password)
        		return true;
		return false;
        });
	if (lu.size())
		return true;
	else
		return false;
}
bool AgendaService::userRegister(string userName, string password, string email, string phone) {
	list<User> lu;
	lu = storage_->queryUser([&](const User& user)->bool{
        	if (user.getName() == userName)
        		return true;
		return false;
        });
	if (lu.size()) {
		return false;
	} else {
		User u(userName, password, email, phone);
		storage_->createUser(u);
		return true;
	}
}
bool AgendaService::deleteUser(string userName, string password) {
	int i = storage_->deleteUser([&](const User& user)->bool{
        	if (user.getName() == userName&&user.getPassword() == password)
        		return true;
		return false;
        });
	if (i) {
		deleteAllMeetings(userName);
		return true;
	} else {
		return false;
	}
}
list<User> AgendaService::listAllUsers(void) {
	list<User> lu;
	lu = storage_->queryUser([&](const User& user)->bool{
		if (user.getName() != ""&&user.getPassword() != "")
			return true;
		return false;
	});
	return lu;
}
bool AgendaService::createMeeting(string userName, string title, string participator, string startDate, std::string endDate) {
	Date sDate, eDate;
	sDate = Date::stringToDate(startDate);
	eDate = Date::stringToDate(endDate);
	if ((!Date::isValid(sDate)) || (!Date::isValid(eDate)))
		return false;
	if (sDate >= eDate)
		return false;
	Meeting m(userName, participator, sDate, eDate, title);
	list<Meeting> lm;
	lm = meetingQuery(userName, title);
	if (lm.size())
		return false;
	lm = meetingQuery(participator, title);
	if (lm.size())
		return false;
	lm = storage_->queryMeeting([&](const Meeting& meeting)->bool{
        	if ((meeting.getSponsor() == userName||meeting.getParticipator() == userName)&&((meeting.getStartDate() >= sDate&&meeting.getStartDate() < eDate)||(meeting.getEndDate() > sDate&&meeting.getEndDate() <= eDate))||(meeting.getStartDate() <= sDate&&meeting.getEndDate() >= eDate))
        		return true;
		return false;
        });
	if (lm.size())
		return false;
	lm = storage_->queryMeeting([&](const Meeting& meeting)->bool{
        	if ((meeting.getSponsor() == participator||meeting.getParticipator() == participator)&&((meeting.getStartDate() >= sDate&&meeting.getStartDate() < eDate)||(meeting.getEndDate() > sDate&&meeting.getEndDate() <= eDate))||(meeting.getStartDate() <= sDate&&meeting.getEndDate() >= eDate))
        		return true;
		return false;
        });
	if (lm.size())
		return false;
	list<User> lu, lp;
	lu = storage_->queryUser([&](const User& user)->bool{
		if (user.getName() == userName)
			return true;
		return false;
	});
	lp = storage_->queryUser([&](const User& user)->bool{
		if (user.getName() == participator)
			return true;
		return false;
	});
	if (lu.size() == 0||lp.size() == 0)
		return false;
	storage_->createMeeting(m);
	return true;
}
list<Meeting> AgendaService::meetingQuery(string userName, string title) {
	list<Meeting> lm;
	lm = storage_->queryMeeting([&](const Meeting& meeting)->bool{
        	if ((meeting.getSponsor() == userName||meeting.getParticipator() == userName)&&meeting.getTitle() == title)
        		return true;
		return false;
        });
	return lm;
}
list<Meeting> AgendaService::meetingQuery(string userName, string startDate, string endDate) {
	Date sDate, eDate;
	sDate = Date::stringToDate(startDate);
	eDate = Date::stringToDate(endDate);
	list<Meeting> lm;
	if ((!Date::isValid(sDate))||(!Date::isValid(eDate)))
		return lm;
	if (sDate >= eDate)	return lm;
	lm = storage_->queryMeeting([&](const Meeting& meeting)->bool{
        	if ((meeting.getSponsor() == userName||meeting.getParticipator() == userName)&&(((meeting.getStartDate() >= sDate&&meeting.getStartDate() <= eDate)||(meeting.getEndDate() >= sDate&&meeting.getEndDate() <= eDate))||(meeting.getStartDate() <= sDate&&meeting.getEndDate() >= eDate)))
        		return true;
		return false;
        });
	return lm;
}
list<Meeting> AgendaService::listAllMeetings(string userName) {
	list<Meeting> lm;
	lm = storage_->queryMeeting([&](const Meeting& meeting)->bool{
        	if (meeting.getSponsor() == userName||meeting.getParticipator() == userName)
        		return true;
		return false;
        });
	return lm;
}
list<Meeting> AgendaService::listAllSponsorMeetings(string userName) {
	list<Meeting> lm;
	lm = storage_->queryMeeting([&](const Meeting& meeting)->bool{
        	if (meeting.getSponsor() == userName)
        		return true;
		return false;
        });
	return lm;
}
list<Meeting> AgendaService::listAllParticipateMeetings(string userName) {
	list<Meeting> lm;
	lm = storage_->queryMeeting([&](const Meeting& meeting)->bool{
        	if (meeting.getParticipator() == userName)
        		return true;
		return false;
        });
	return lm;
}
bool AgendaService::deleteMeeting(string userName, string title) {
	int i = storage_->deleteMeeting([&](const Meeting& meeting)->bool{
        	if ((meeting.getSponsor() == userName)&&meeting.getTitle() == title)
        		return true;
		return false;
        });
	if (i)
		return true;
	else
		return false;
}
bool AgendaService::deleteAllMeetings(string userName) {
	int i = storage_->deleteMeeting([&](const Meeting& meeting)->bool{
        	if (meeting.getSponsor() == userName)
        		return true;
		return false;
        });
	if (i)
		return true;
	else
		return false;
}
void AgendaService::startAgenda(void) {
	storage_ = Storage::getInstance();
}
void AgendaService::quitAgenda(void) {
	storage_->sync();
}

