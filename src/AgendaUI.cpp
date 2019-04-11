#include<iostream>
#include"AgendaUI.h"
#include<string>
#include<iomanip>
using namespace std;
AgendaUI::AgendaUI() {
	userName_ = "";
	userPassword_ = "";
}
void AgendaUI::OperationLoop(void) {
	startAgenda();
	string s;
	while ((s = getOperation()) != "q") {
		bool flag = executeOperation(s);
		if (flag == false&&userName_ == "")
			cout << "Agenda : ~$ ";
		else if (flag == false&&userName_ != "")
			cout << "Agenda@" << userName_ << "# ";
	}
	quitAgenda();
	return;
}
void AgendaUI::startAgenda(void) {
	agendaService_.startAgenda();
	cout << "----------------------- Agenda -----------------------\n";
	cout << "Action :\n";
	cout << "l  - log in Agenda by user name and password\n";
	cout << "r  - register an Agenda account\n";
	cout << "q  - quit Agenda\n";
	cout << "------------------------------------------------------\n\n";
	cout << "Agenda : ~$ ";
}
string AgendaUI::AgendaUI::getOperation() {
	string op;
	cin >> op;
	return op;
}
bool AgendaUI::executeOperation(string op) {
	if (op == "l") {
		userLogIn();
		return true;
	} else if (op =="r") {
		userRegister();
		return true;
	} else if (op == "q") {
		quitAgenda();
		return true;
	} else if (op == "o") {
		userLogOut();
		return true;
	} else if (op == "dc") {
		deleteUser();
		return true;
	} else if (op == "lu") {
		listAllUsers();
		return true;
	} else if (op == "cm") {
		createMeeting();
		return true;
	} else if (op == "la") {
		listAllMeetings();
		return true;
	} else if (op == "las") {
		listAllSponsorMeetings();
		return true;
	} else if (op == "lap") {
		listAllParticipateMeetings();
		return true;
	} else if (op == "qm") {
		queryMeetingByTitle();
		return true;
	} else if (op == "qt") {
		queryMeetingByTimeInterval();
		return true;
	} else if (op == "dm") {
		deleteMeetingByTitle();
		return true;
	} else if (op == "da") {
		deleteAllMeetings();
		return true;
	} else {
		return false;
	}
}
void AgendaUI::userLogIn(void) {
	cout << "[log in] [user name] [password]\n";
	cout << "[log in] ";
	cin >> userName_ >> userPassword_;
	cout << endl;
	if (agendaService_.userLogIn(userName_, userPassword_)) {
		cout << "succeed!" << endl;
		cout << "----------------------- Agenda -----------------------\n";
		cout << "Action :\n";
		cout << "o  -log out Agenda\n";
		cout << "dc  - delete Agenda account\n";
		cout << "lu  - list All Agenda user\n";
		cout << "cm  - creat a meeting\n";
		cout << "la  - list all meetings\n";
		cout << "las  - list all sponsor meetings\n";
		cout << "lap  - list all participator meetings\n";
		cout << "qm  - query meeting by title\n";
		cout << "qt  - query meeting by time interval\n";
		cout << "dm  - delete meeting by title\n";
		cout << "da  - delete all meetings\n";
		cout << "-----------------------------------------------------\n\n";
		cout << "Agenda@" << userName_ << " : # ";
	 } else {
		cout << "[error] log in fail!" << endl;
		startAgenda();
	}
}
void AgendaUI::userRegister(void) {
	string email_, phone_;
	cout << "[register] [user name] [password] [email] [phone]\n";
	cout << "[register] ";
	cin >> userName_ >> userPassword_ >> email_ >> phone_;
	cout << endl;
	if (agendaService_.userRegister(userName_, userPassword_, email_, phone_)) {
		cout << "succeed!" << endl;
		cout << "----------------------- Agenda -----------------------\n";
		cout << "Action :\n";
		cout << "o  -log out Agenda\n";
		cout << "dc  - delete Agenda account\n";
		cout << "lu  - list All Agenda user\n";
		cout << "cm  - creat a meeting\n";
		cout << "la  - list all meetings\n";
		cout << "las  - list all sponsor meetings\n";
		cout << "lap  - list all participator meetings\n";
		cout << "qm  - query meeting by title\n";
		cout << "qt  - query meeting by time interval\n";
		cout << "dm  - delete meeting by title\n";
		cout << "da  - delete all meetings\n";
		cout << "-----------------------------------------------------\n\n";
		cout << "Agenda@" << userName_ << " : # ";
	 } else {
		cout << "[error] register fail!" << endl;
		startAgenda();
	}
}
void AgendaUI::quitAgenda(void) {
	agendaService_.quitAgenda();
}
void AgendaUI::userLogOut(void) {
	cout << "Log out succeed!" << endl;
	startAgenda();
}
void AgendaUI::deleteUser(void) {
	cout << "[delete agenda account] succeed!\n";
	agendaService_.deleteUser(userName_, userPassword_);
	userLogOut();
}
void AgendaUI::listAllUsers(void) {
	cout << "[list all users]\n\n";
	cout << "name    email            phone\n";
	list<User> lu = agendaService_.listAllUsers();
	list<User>::iterator iter;
	for (iter = lu.begin(); iter != lu.end(); iter++) {
		cout << setiosflags(ios::left) << setw(8) << (*iter).getName();
		cout << setiosflags(ios::left) << setw(17) << (*iter).getEmail();
		cout << setiosflags(ios::left) << setw(11) << (*iter).getPhone() << endl;
	}
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::createMeeting(void) {
	string title, participator, stime, etime;
	cout << "[create meeting] [title] [participator] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]\n";
	cout << "[create meeting] ";
	cin >> title >> participator >> stime >> etime;
	cout << endl;
	if (agendaService_.createMeeting(userName_, title, participator, stime, etime))
		cout << "[create meeting] succeed!\n";
	else
		cout << "[error] create meeting fail!\n";
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::listAllMeetings(void) {
	cout << "[list all meetings]\n\n";
	list<Meeting> lm = agendaService_.listAllMeetings(userName_);
	printMeetings(lm);
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::listAllSponsorMeetings(void) {
	cout << "[list all sponsor meetings]\n\n";
	list<Meeting> lm = agendaService_.listAllSponsorMeetings(userName_);
	printMeetings(lm);
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::listAllParticipateMeetings(void) {
	cout << "[list all participate meetings]\n\n";
	list<Meeting> lm = agendaService_.listAllParticipateMeetings(userName_);
	printMeetings(lm);
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::queryMeetingByTitle(void) {
	string title;
	cout << "[query meeting] [title]:\n";
	cout << "[query meeting] ";
	cin >> title;
	cout << endl << endl;
	cout << "sponsor             " << "participator        " << "start time               " << "end time       " << endl;
	list<Meeting> lm = agendaService_.meetingQuery(userName_, title);
	list<Meeting>::iterator iter;
	for (iter = lm.begin(); iter != lm.end(); iter++) {
		cout << setiosflags(ios::left) << setw(20) << (*iter).getSponsor();
		cout << setiosflags(ios::left) << setw(20) << (*iter).getParticipator();
		cout << setiosflags(ios::left) << setw(25) << Date::dateToString((*iter).getStartDate());
		cout << setiosflags(ios::left) << setw(15) << Date::dateToString((*iter).getEndDate()) << endl;
	}
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::queryMeetingByTimeInterval(void) {
	string stime, etime;
	cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]:\n";
	cout << "[query meetings] ";
	cin >> stime >> etime;
	cout << endl << endl;
	cout << "[query meetings]\n";
	list<Meeting> lm = agendaService_.meetingQuery(userName_, stime, etime);
	printMeetings(lm);
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::deleteMeetingByTitle(void) {
	cout << "[delete meeting] [title]\n";
	string title;
	cout << "[delete meeting] ";
	cin >> title;
	cout << endl << endl;
	if (agendaService_.deleteMeeting(userName_, title))
		cout << "[delete meeting] succeed!\n";
	else
		cout << "[error] delete meeting fail!\n";
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::deleteAllMeetings(void) {
	cout << "[delete all meetings] succeed!\n";
	agendaService_.deleteAllMeetings(userName_);
	cout << "Agenda@" << userName_ << " : # ";
}
void AgendaUI::printMeetings(list<Meeting> meetings) {
	list<Meeting>::iterator iter;
	cout << "title               " << "sponsor             " << "participator        " << "start time               " << "end time       " << endl;
	for (iter = meetings.begin(); iter != meetings.end(); iter++) {
		cout << setiosflags(ios::left) << setw(20) << (*iter).getTitle();
		cout << setiosflags(ios::left) << setw(20) << (*iter).getSponsor();
		cout << setiosflags(ios::left) << setw(20) << (*iter).getParticipator();
		cout << setiosflags(ios::left) << setw(25) << Date::dateToString((*iter).getStartDate());
		cout << setiosflags(ios::left) << setw(15) << Date::dateToString((*iter).getEndDate()) << endl;
	}
}

