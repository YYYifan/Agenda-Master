All:Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o Agenda.cpp
	g++ -std=c++11 -o All Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o Agenda.cpp
Date.o: Date.h Date.cpp 
	g++  Date.cpp -std=c++11 -c
User.o: User.h User.cpp
	g++  User.cpp -std=c++11 -c
Meeting.o: Meeting.h Meeting.cpp
	g++  Meeting.cpp -std=c++11 -c
Storage.o: Storage.h Storage.cpp
	g++  Storage.cpp -std=c++11 -c
AgendaService.o: AgendaService.h AgendaService.cpp
	g++  AgendaService.cpp -std=c++11 -c
AgendaUI.o: AgendaUI.h AgendaUI.cpp
	g++ AgendaUI.cpp -std=c++11 -c
clean:
	rm Date.o User.o Meeting.o Storage.o AgendaService.o AgendaUI.o All

