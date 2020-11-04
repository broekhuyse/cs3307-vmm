#include <iostream>
#include "Login.h"
#include "LoginCollection.h"
#include "LoginInterface.h"
#include "UserDBConversion.h"

using namespace std;

int main()
{
	LoginCollection collection;
	UserDBConversion converter;

	//load collection from file
	collection.setCollection(converter.FileToLoginCollection());

    Login login(collection);
    LoginInterface interface(&login);
	
	
    for (int i = 0; i < 1; i++)
    {
        cout << "----------------- Account Creation -----------------" << endl;
        interface.createAccountPrompt();
		
    }
	
    
    cout << "----------------- Login -----------------" << endl;
	interface.loginPrompt();
	
    

	//save collection to file
	auto test = login.getLoginCollection().getMap();
	converter.LoginCollectionToFile(test);

	return 0; 
}