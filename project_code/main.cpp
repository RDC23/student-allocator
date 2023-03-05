#include <iostream>
#include "User.h"
#include "UI.h"
#include "Utils.h"



int main() {
	
	Database* db = new Database;  //the constructor manages to successfully load and map associations
	DatabaseManager dbm(db, 3);

	UserUI* ui = new StudentUI(db->getStudent("Kishan"), &dbm);
	ui->displayUI();


	while (true) {
		int option = 0;
		option = getValidInteger("\nEnter an option number: ");
		if (option > 0 && option <= ui->getNumOptions()) {
			ui->doSomething(option);
		}
		if (option == ui->getNumOptions()) {
			break;
		}
		
	}
	
	


}