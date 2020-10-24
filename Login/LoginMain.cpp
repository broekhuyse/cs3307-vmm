#include <iostream>
#include "Login.h"
#include "LoginCollection.h"
#include "LoginInterface.h"

using namespace std;

int main()
{
    LoginCollection collection;
    Login login(collection);
    LoginInterface interface(login);

    cout << "----------------- Account Creation -----------------" << endl;
    interface.createAccountPrompt();

    cout << "----------------- Login -----------------" << endl;
    interface.loginPrompt();
}