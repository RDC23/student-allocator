#pragma once
#include <string>
#include <utility> //for std::pair
#include <vector>
#include "User.h"
#include "DatabaseManager.h" //provide interfaces with access to the database

//Each UI need access to:
//	1) the object it provides a UI for so it can manipulate its attributes based on user input
//	2) the DatabaseManager wrapper which provides controlled access to the database should modification be necessary be classes


//Abstract base class to allow polymorphic UI use in main (rather than writing 3 seperate programs)
class UserUI {

public:
	UserUI(DatabaseManager& dbm);
	virtual void displayUI() = 0;
	virtual int getNumOptions() = 0;
	virtual std::string getOptionName() = 0;
	virtual void doSomething() = 0;

protected:
	DatabaseManager dbm; //all interfaces need controlled access to the database view all projects for example

};

class StudentUI : public UserUI {

public:
	StudentUI(Student* myStudent, DatabaseManager& dbm); //call parent contructor and pass the database parameter
	void displayUI() override;  //custom message + iterate through options vector and display choices with number
	int getNumOptions() override; //allows main to handle user input (check option is in valid range without hardcoding this
	std::string getOptionName() override;
	void doSomething() override; //handles user choice via switch case and calls appropriate function to do action (functions below)
	void addProjectToPreferences();
	void removeProject();
	void viewMyProjects();
	void findOutMoreProject();
	void reOrderProjects();

private:
	Student* myStudent{ nullptr }; //allows UI to act on the student object and call appropriate getters/setters

	std::vector<std::pair<std::string, int>> options = { //add more options as required
		{"Select a project", 1},
		{"Remove a project from my choices", 2},
		{"View my project preferences", 3},
		{"Find out more about a project", 4},
		{"Re-order my project preferences", 5},
		{"Check my assigned project", 6},
		{"Exit application", 7}
	};

};

class SupervisorUI : public UserUI { 

public:
	SupervisorUI(Supervisor* mySupervisor, DatabaseManager& dbm); //call parent constructor
	void displayUI() override;
	int getNumOptions() override;
	std::string getOptionName() override;
	void doSomething() override;
	void showProjectsOversee();
	void editProjectMetadata();
	
private:
	Supervisor* mySupervisor{ nullptr };

	std::vector<std::pair<std::string, int>> options = {
		{"Show projects I am overseeing", 1},
		{"Edit a project metadata", 2}
	};

};

class AdminUI : public UserUI {

public:
	AdminUI(Admin* admin, DatabaseManager& dbm); //call parent constructor
	void displayUI() override;
	int getNumOptions() override;
	std::string getOptionName() override;
	void doSomething() override;
	void automaticAllocate();
	void swapAllocationStrategy();
	void editStudent();
	void editStaff();
	void editProject();

private:
	Admin* myAdmin{ nullptr };

	std::vector<std::pair<std::string, int>> options = {
		{"Perform automatic allocation", 1},
		{"Swap allocation strategy", 2},
		{"Edit a student's data", 3},
		{"Edit a staff member's data", 4},
		{"Edit a project's data", 5}
	};


};