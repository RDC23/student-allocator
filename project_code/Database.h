#pragma once
#include "Project.h"
#include "User.h"
#include <fstream>
#include "AllocationStrategy.h"

class Database {

public:
	Database(); //load in from csv and then construct the associations for each object
	virtual ~Database(); //implement logic to save all data to csv then free all pointer data
	void loadDBfromCSV();
	Student* getStudent(std::string name);
	Supervisor* getSupervisor(std::string name);
	Project* getProject(std::string name);
	std::vector<Project>& getProjects();
	std::vector<Supervisor>& getSupervisors();
	Admin* getAdmin();

private:	
	Database(const Database&); //prevent multiple instances being created due to copy construction
	std::vector<Student> studentDB;
	std::vector<Supervisor> supervisorDB;
	std::vector<Project> projectDB;
	Admin systemAdmin;
};

