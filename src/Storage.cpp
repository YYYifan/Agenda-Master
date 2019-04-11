#include<iostream>
#include<string>
#include<fstream>
#include<list>
#include<functional>
#include"Storage.h"
#include<math.h>
using namespace std;
Storage* Storage::instance_ = NULL;
Storage* Storage::getInstance(void) {
	if (instance_ == NULL)
		instance_ = new Storage();
	return instance_;
}
Storage::Storage() {
	readFromFile("agenda.data");
}
bool Storage::readFromFile(const char *fpath) {
	if (fpath == NULL)
		return false;
	int i = 0, t;
	string ss = "", st = "";
	ifstream inFile;
	inFile.open(fpath);
	if (!inFile) {
		inFile.close();
		return false;
	}
	while (!inFile.eof()) {
		getline(inFile, ss, '\n');
		t = 0;
		for (i = 0; ss[i] != '"'; ++i) {}
		for (i = i + 1; ss[i] != '"'; ++i)
			st = st + ss[i];
		for (; ss[i] != ':'; ++i) {}
		for (i = i + 1; ss[i] != '}'; ++i)
			t = t*10 + (ss[i] - '0');
		if (st == "User")
			while (t--) {
				i = 0;
				string uu[4];
				getline(inFile, ss, '\n');
				User u; // {name:"wc3",password:"12345",email:"wc@qq.com",phone:"123456"}
				for (int k = 0; k < 4; k++) {
					for (i = i + 1; ss[i] != '"'; ++i) {}
					for (i = i + 1; ss[i] != '"'; ++i)
					uu[k] = uu[k] + ss[i];
				}
				u.setName(uu[0]);
				u.setPassword(uu[1]);
				u.setEmail(uu[2]);
				u.setPhone(uu[3]);
				userList_.push_back(u);
			}
		else if (st == "Meeting")
			while (t--) {
				i = 0;
				string mm[5];
				getline(inFile, ss, '\n');
				Meeting m;
				for (int k = 0; k < 5; k++) {
					for (i = i + 1; ss[i] != '"'; ++i) {}
					for (i = i + 1; ss[i] != '"'; ++i)
					mm[k] = mm[k] + ss[i];
				}
				m.setSponsor(mm[0]);
				m.setParticipator(mm[1]);
				m.setStartDate(Date::stringToDate(mm[2]));
				m.setEndDate(Date::stringToDate(mm[3]));
				m.setTitle(mm[4]);
				meetingList_.push_back(m);
			}
	}
	inFile.close();
	return true;
}
bool Storage::writeToFile(const char *fpath) {
	ofstream outFile;
	outFile.open(fpath, ios::out);
	if (!outFile) {
		outFile.close();
		return false;
	}
	list<User>::iterator iter;
	list<Meeting>::iterator it;
	string ss;
	int a = userList_.size(), b = meetingList_.size();
	if (a) {
		outFile << "{collection:\"User\",total:" << a << "}" << endl;
		for (iter = userList_.begin(); iter != userList_.end(); iter++) {
			outFile << "{name:\"" << (*iter).getName() << "\",password:\"" << (*iter).getPassword() << "\",email:\"" << (*iter).getEmail() << "\",phone:\"" << (*iter).getPhone() << "\"}" << endl;
		}
	} else {
		outFile << "{collection:\"User\",total:0}" << endl;
	}
	if (b) {
		outFile << "{collection:\"Meeting\",total:" << b << "}" << endl;
		for (it = meetingList_.begin(); it != meetingList_.end(); it++) {
			outFile << "{sponsor:\"" << (*it).getSponsor() << "\",participator:\"" << (*it).getParticipator() << "\",sdate:\"" << Date::dateToString((*it).getStartDate()) << "\",edate:\"" << Date::dateToString((*it).getEndDate()) << "\",title:\"" << (*it).getTitle() << "\"}" << endl;
		}
	} else {
		outFile << "{collection:\"Meeting\",total:0}" << endl;
	}
	outFile.close();
	return true;
}	
Storage::~Storage() {
	writeToFile("agenda.data");
	instance_ = NULL;
}
void Storage::createUser(const User& u) {
	list<User> lu;
	lu = queryUser([&](const User& user)->bool{
        	if (user.getName() == u.getName())
        		return true;
		return false;
        });
        if (lu.size() == 0)	
		userList_.push_back(u);
}
list<User> Storage::queryUser(function<bool(const User& u)> filter) {
	list<User> lu;
	list<User>::iterator iter;
	for (iter = userList_.begin(); iter != userList_.end(); iter++) {
		if (filter(*iter))
			lu.push_back(*iter);
	}
	return lu;
}
int Storage::updateUser(function<bool(const User& u)> filter, function<void(User&)> switcher) {
	int t = 0;
	list<User>::iterator iter;
	for (iter = userList_.begin(); iter != userList_.end(); iter++) {
		if (filter(*iter)) {
			switcher(*iter);
			t++;
		}
	}
	return t;
}
int Storage::deleteUser(function<bool(const User& u)> filter) {
	int k = 0;
	list<User>::iterator iter;
	for (iter = userList_.begin(); iter != userList_.end();) {
		if (filter(*iter)) {
			k++;
			list<User>::iterator temp = iter++;
			userList_.erase(temp);
		} else {
			iter++;
		}
	}
	return k;
}
void Storage::createMeeting(const Meeting& m) {
  	meetingList_.push_back(m);
}
list<Meeting> Storage::queryMeeting(function<bool(const Meeting& m)> filter) {
   	list<Meeting> lm;
	list<Meeting>::iterator iter;
	for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
		if (filter(*iter))
			lm.push_back(*iter);
	}
	return lm;
}
int Storage::updateMeeting(function<bool(const Meeting& m)> filter, function<void(Meeting&)> switcher) {
	int t = 0;
	list<Meeting>::iterator iter;
	for (iter = meetingList_.begin(); iter != meetingList_.end(); iter++) {
		if (filter(*iter)) {
			switcher(*iter);
			t++;
		}
	}
	return t;
}
int Storage::deleteMeeting(function<bool(const Meeting& m)> filter) {
	int k = 0;
	list<Meeting>::iterator iter;
	for (iter =meetingList_.begin(); iter != meetingList_.end();) {
		if (filter(*iter)) {
			k++;
			list<Meeting>::iterator temp = iter++;
			meetingList_.erase(temp);
		} else {
			iter++;
		}
	}
	return k;
}
bool Storage::sync(void) {
	return writeToFile("agenda.data");
}

