#include <iostream>
#include "User.h"
#include "UI.h"
#include "Utils.h"
#include "DatabaseManager.h"



int main() {
	std::cout << "\033[48;5;24m"; // Set background color to a dark blue
	std::cout << "\033[38;5;231m"; // Set text color to a light grey

	//create the core data structures
	Database* db = new Database;  
	DatabaseManager dbm(db, 2);
	UserUI* ui = nullptr;
	
	//get the user in the database
	User* login_user =  dbm.authenticateAndFindUser();

	//create the correct UI using dynamic cast (runtime polymorphic type checking)
	if (Student* user = dynamic_cast<Student*>(login_user)) {
		ui = new StudentUI(user, &dbm);
	}
	else if (Supervisor* user = dynamic_cast<Supervisor*>(login_user)) {
		ui = new SupervisorUI(user, &dbm);
	}
	else if (Admin* user = dynamic_cast<Admin*>(login_user)) {
		ui = new AdminUI(user, &dbm, db);
	}

	else {
		std::cout << "Failed to initialise the interface. Shutting down." << std::endl;
		return 1;
	}

	//display the interface and main loop

	while (true) {
		clearScreen();
		ui->displayUI();
		int option = 0;
		option = getValidInteger("\nEnter an option number: ");
		if (option > 0 && option <= ui->getNumOptions()) {
			ui->doSomething(option);
		}
		if (option == ui->getNumOptions()) {
			break;
		}
		
	}
	
	
	std:: cout << "\033[2J\033[1;1H";

}