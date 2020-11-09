#include "Member.h"
#include "SetupInterface.h"
#include <iostream>
#include <sstream>

using namespace std;

SetupInterface::SetupInterface(){
	
}

SetupInterface::SetupInterface(Login *login){
	this->login = login;
}

void SetupInterface::SetupPrompt() {
	int result = -1;
	string firstName, lastName, username, password;
	
	while (result < 0){
		cout << "WELCOME TO YOUR BRAND NEW VIRTUAL VENDING MACHINE\n" << endl;
		cout << "Please Follow The Upcoming Instructions To Setup Your First Account" << endl;
		
		cout << "Please Enter Your First Name: " << endl;
		getline(cin, firstName);
		
		cout << "Please Enter Your Last Name: " << endl;
		getline(cin, lastName);
		
		cout << "Please Enter A Username: " << endl;
		getline(cin, username);
		
		cout << "Please Enter A Password (Must be longer than 8 characters and contain an uppercase, lowercase, a number and a special symbol): " << endl;
		getline(cin, password);
		
		cout << "As the first member, your account will be designated as an admin account" << endl;
		
		result = login->createAccount(username, password, firstName, lastName, true, "temp");
		if(result == -1){
			cout << "Username already exists." << endl;
		}
		
		else if(result == -2){
			cout << "Password is not secure enough." << endl;
		}
		
		else {
			cout << "Your setup is complete!" << endl;
		}
		
		if(result < 0) {
			string redoInput;
			int redo;
			cout << "Input 0 to try again or 1 to exit" << endl;
			while(getline(cin, redoInput); {
				stringstream stream(redoInput);
				if(stream >> redo){
					if(stream.eof() && (redo == 0 || redo == 1)) {
						if(redo == 0) {
							result = -1;
						}
						else {
							result = 0;
						}
						break;
					}
				}
				
				cout << "Invalid Input" << endl;
			}
		}
	}
}
