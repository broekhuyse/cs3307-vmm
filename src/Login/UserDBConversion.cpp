#include "UserDBConversion.h"
#include <string>
#include <fstream>
#include <sstream>
#include "member.h"
#include "LoginCollection.h"
#include <iostream>


UserDBConversion::UserDBConversion() {

};


/*
* Name: LoginCollectionToFile
* Description: Writes the LoginCollection to Output File
* Param: map of type : std::unordered_map<std::string, std::pair<std::string, Member>>
* Return: Void
*/
void UserDBConversion::LoginCollectionToFile(std::unordered_map<std::string, std::pair<std::string, Member>>& map) {

	//open output file
	std::ofstream userFile;
	userFile.open("userDB.txt"); 

	//create iterator for unordered_map 
	std::unordered_map<std::string, std::pair<std::string, Member>>::iterator it = map.begin();

	//iterate through unordered_map and output everything 
	for (std::unordered_map<std::string, std::pair<std::string, Member>>::iterator it = map.begin(); it != map.end(); ++it) {

		userFile << it->second.second.getfname() << "," << it->second.second.getlname() << "," << it->second.second.getisadmin() << "," << it->second.second.getID() << ","
			<< it->second.second.getMembershipType() << "," << it->second.second.getCurrency() <<","<< it->first << "," << it->second.first <<" "<< std::endl;

	}

};


/*
* Name: FileToLoginCollection
* Description: Fills LoginCollection from input file
* Param: map of type: std::unordered_map<std::string, std::pair<std::string, Member>>
* Return: Void
*/
std::unordered_map<std::string, std::pair<std::string, Member>> UserDBConversion::FileToLoginCollection() {
	
	std::string tPass, tUserName = "0"; 
	std::string line;
	std::ifstream file("UserDB.txt");
	std::unordered_map<std::string, std::pair<std::string, Member>> map;
	if (file.is_open()) {


		while (getline(file, line)) {

			std::string tFName, tLName, tMembershipType, tUser, tPass;
			bool tIsAdmin = 0;
			int tmemberID = 0;
			float tcurrency = 0;
			int counter = 1;
			//convert line to c string to process
			const char* start = line.c_str(); 
			bool inString = false;
			//cstring allows for this for loop because cstring terminated with null char
			for (const char* p = start; *p; p++) { 

				//left this in from assignment one where we needed to parse strings within quotes that contained commas as well. might remodel this later because we dont need this functionality
				if (*p == '"') { 
					inString = !inString;
				}
				// if ',' is reached and we are not instring, save the token up until that point
				//sliding window algorithm. "start" stays at start of word and p iterates forward until it finds a "," token saved as chars between start and p, then start will be updated to p+1 and process continues
				else if (*p == ',' && !inString) { 
					std::string token = std::string(start, p - start);
					std::stringstream conversion(token);

					//switch is used to save the correct data as the line is parsed, counter used to know where we are in the line (know the positions of data we want from the .csv )
					switch (counter) { 
					case (1):
						tFName = token;
						break;

					case (2):
						tLName = token;
						break;

					case (3):
						conversion >> tIsAdmin;
						break;

					case (4):
						conversion >> tmemberID;
						break;

					case (5):
						tMembershipType = token;
						break;

					case (6):
						conversion >> tcurrency;
						break;

					case (7):
						tUser = token;
						break;

					default:
						break;

					}
					//start pointer is only updated to p+1 when a word is found
					start = p + 1;
					counter++;
				}

			}
			//save final token since the for loop will end before saving the last token
			// have to remove the last char of the string because it is terminated by a null char which will affect comparisons
			//for whatever reason last line of the file doesnt have terminator so there MUST be a newline in the file after the last line
			std::string t = std::string(start);
			tPass = t.substr(0, t.size() - 1);
			//std::cout << "in userdbconversion: " << tPass << std::endl;

			//input all information from line into map 
			
			map[tUser].first = tPass;
			map[tUser].second = Member(tFName, tLName, tIsAdmin, tmemberID, tMembershipType, tcurrency);

		}
		

		



	}
	

	return map;
	
};