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

    for (int i = 0; i < 1; i++)
    {
        cout << "----------------- Account Creation -----------------" << endl;
        interface.createAccountPrompt();
    }
    while (true)
    {
        cout << "----------------- Login -----------------" << endl;
        interface.loginPrompt();
    }
}