#ifndef SETUP_INTERFACE_H
#define SETUP_INTERFACE_H

#include <string>
#include <Login.h>

class SetupInterface {
	private:
		Login *login;
	public:
		SetupInterface();
		SetupInterface(Login *login);
		void SetupPrompt();
	}

#endif
