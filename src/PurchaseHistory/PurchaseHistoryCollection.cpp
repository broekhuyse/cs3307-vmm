#include "PurchaseHistoryCollection.h"
#include <cmath>
#include <iostream>
#include <string>

PurchaseHistoryCollection::PurchaseHistoryCollection() {
	
}

PurchaseHistoryCollection::~PurchaseHistoryCollection() {}

PurchaseHistory PurchaseHistoryCollection::getPurchaseHistory(int memberID, time_t date) {
	if(historyCollection.find(memberID) != historyCollection.end()) {
		std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
		
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(i->getRawTime() == date)
				return *i;
		}	
	}
	
	return PurchaseHistory();
}

std::vector<PurchaseHistory> PurchaseHistoryCollection::getHistoriesByID(int memberID) {
	if(historyCollection.find(memberID) != historyCollection.end())
		return historyCollection.at(memberID);
	
	return std::vector<PurchaseHistory>();
}

std::vector<PurchaseHistory> PurchaseHistoryCollection::getMemberHistoriesBefore(int memberID, time_t date) {
	if(historyCollection.find(memberID) == historyCollection.end())
		return std::vector<PurchaseHistory>();
		
	std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
	std::vector<PurchaseHistory> histList;
	
	for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
		if(difftime(i->getRawTime(), date) < 0)
			histList.push_back(*i);	
	}
	
	return histList;
}

std::vector<PurchaseHistory> PurchaseHistoryCollection::getMemberHistoriesAfter(int memberID, time_t date) {
	if(historyCollection.find(memberID) == historyCollection.end())
		return std::vector<PurchaseHistory>();
		
	std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
	std::vector<PurchaseHistory> histList;
	
	for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
		if(difftime(i->getRawTime(), date) > 0)
			histList.push_back(*i);	
	}
	
	return histList;
}

std::vector<PurchaseHistory> PurchaseHistoryCollection::getMemberHistoriesWithinDay(int memberID, time_t date) {
	if(historyCollection.find(memberID) == historyCollection.end())
		return std::vector<PurchaseHistory>();
		
	std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
	std::vector<PurchaseHistory> histList;
	
	for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
		// Check the difference in seconds, push anything within 86,400 seconds (24 hours)
		if(std::abs(difftime(i->getRawTime(), date)) <= 86400)
			histList.push_back(*i);	
	}
	
	return histList;
}

std::vector<PurchaseHistory> PurchaseHistoryCollection::getAllHistoriesBefore(time_t date) {
	std::vector<PurchaseHistory> histList;
	for(std::unordered_map<int, std::vector<PurchaseHistory>>::iterator it = historyCollection.begin(); it != historyCollection.end(); it++) {
	
		std::vector<PurchaseHistory> histories = it->second;
	
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(difftime(i->getRawTime(), date) < 0)
				histList.push_back(*i);
		}	
	}
	
	return histList;
}

std::vector<PurchaseHistory> PurchaseHistoryCollection::getAllHistoriesAfter(time_t date) {
	std::vector<PurchaseHistory> histList;
	for(std::unordered_map<int, std::vector<PurchaseHistory>>::iterator it = historyCollection.begin(); it != historyCollection.end(); it++) {
	
		std::vector<PurchaseHistory> histories = it->second;
	
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(difftime(i->getRawTime(), date) > 0)
				histList.push_back(*i);
		}	
	}
	
	return histList;
}

std::vector<PurchaseHistory> PurchaseHistoryCollection::getAllHistoriesWithinDay(time_t date) {
	std::vector<PurchaseHistory> histList;
	for(std::unordered_map<int, std::vector<PurchaseHistory>>::iterator it = historyCollection.begin(); it != historyCollection.end(); it++) {
	
		std::vector<PurchaseHistory> histories = it->second;
	
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			// Check the difference in seconds, push anything within 86,400 seconds (24 hours)
			if(std::abs(difftime(i->getRawTime(), date)) <= 86400)
				histList.push_back(*i);
		}
	}
	
	return histList;
}

void PurchaseHistoryCollection::addPurchaseHistory(PurchaseHistory history) {
	int memberID = history.getMemberID();
	
	// If empty, initialize new vector and place inside collection
	if(historyCollection.find(memberID) == historyCollection.end()) {
		std::vector<PurchaseHistory> histList (1, history);
		//historyCollection.insert(std::make_pair<int, std::vector<PurchaseHistory>>(memberID, histList));
		historyCollection.emplace(memberID, histList);
	}
	else {
		// Just add history to existing list
		historyCollection.at(memberID).push_back(history);
	}
}

int PurchaseHistoryCollection::deletePurchaseHistory(int memberID, time_t date) {
	if(historyCollection.find(memberID) != historyCollection.end()) {
		std::vector<PurchaseHistory> histories = historyCollection.at(memberID);
		
		for(std::vector<PurchaseHistory>::iterator i = histories.begin(); i != histories.end(); i++) {
			if(i->getRawTime() == date)
				histories.erase(i, i);
				return 0;
		}
	}
	
	return -1;
}

int PurchaseHistoryCollection::deleteAllHistoriesByMember(int memberID) {
	if(historyCollection.find(memberID) != historyCollection.end()) {
		historyCollection.erase(memberID);
		return 0;
	}	
	
	return -1;
}

void PurchaseHistoryCollection::saveToDatabase() {
	
}
