#include <unordered_map>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <ctime>
#include "PurchaseHistory.h"
#include "PurchaseHistoryCollection.h"

using namespace std;

int main() {
	// PurchaseHistory tests
	
	// Products
	Product p1 = Product("P1", "Cat", "ID1", 23.0, 10, 0.4);
	Product p2 = Product("P2", "Cat", "ID2", 230.0, 150, 0.0);
	Product p3 = Product("P3", "Catt", "ID3", 10.0, 23, 0.0);
	Product p4 = Product("P4", "no", "empty", 0.1, 200, 0.2);
	Product p5 = p1;	// Equal to p1
	Product p6 = p2;	// Equal to p2
	
	// Orders
	Order o1 = Order(p1, 0, 1);
	Order o2 = Order(p2, 0, 2);
	Order o3 = Order(p3, 0, 3);
	Order o4 = Order(p4, 0, 4);
	Order o5 = Order(p5, 0, 5);
	Order o6 = Order(p6, 0, 6);
	
	// Order Lists
	std::list<Order> ol1;
	std::list<Order> ol2;
	std::list<Order> ol3; 
	std::list<Order> ol4;
	
	ol1.push_back(o1);
	ol1.push_back(o2);
	ol2 = ol1;
	ol1.push_back(o3);
	ol1.push_back(o4);
	ol3 = ol1;
	ol1.push_back(o5);
	ol1.push_back(o6);
	ol4 = ol1;
	ol1.erase(ol1.begin()++);
	ol1.erase(ol1.begin()++);
	
	// Default memberIDs
	int id1 = 234231;
	int id2 = 33333332;
	int id3 = 9083783;
	int id4 = 664;
	int id5 = 7275;
	int id6 = 0026;
	
	// Get time
	time_t rawTime = time(NULL);
	
	// Create PurchaseHistories
	PurchaseHistory ph1 = PurchaseHistory(ol2, id1, rawTime);
	PurchaseHistory ph2 = PurchaseHistory(ol2, id2, rawTime);
	PurchaseHistory ph3 = PurchaseHistory(ol3, id3, rawTime);
	
	// Check Creation + Time
	cout << "PH creation testing \n";
	cout << ph1.printHistory() << ph1.getTime() << "\n";
	cout << ph2.printHistory() << ph2.getMemberID() << "\n";
	cout << ph3.printHistory() << ph3.getTime() << "\n";
	
	// Create PurchaseHistoryCollection and additional PurchaseHistories
	PurchaseHistoryCollection h  = PurchaseHistoryCollection();
	
	time_t greaterTime = rawTime + 100;
	time_t lesserTime = rawTime - 100;
	
	PurchaseHistory ph4 = PurchaseHistory(ol4, id1, greaterTime);
	PurchaseHistory ph5 = PurchaseHistory(ol4, id1, lesserTime);
	PurchaseHistory ph6 = PurchaseHistory(ol1, id6, lesserTime);
	PurchaseHistory ph7 = PurchaseHistory(ol3, id4, greaterTime);
	PurchaseHistory ph8 = PurchaseHistory(ol2, id4, rawTime);
	
	// Add all PurchaseHistories
	h.addPurchaseHistory(ph1);
	h.addPurchaseHistory(ph2);
	h.addPurchaseHistory(ph3);
	h.addPurchaseHistory(ph4);
	h.addPurchaseHistory(ph5);
	h.addPurchaseHistory(ph6);
	h.addPurchaseHistory(ph7);
	h.addPurchaseHistory(ph8);
	
	// GetByID testing
	cout << "PHC testing for id1\n" << "Should contain ol2, ol4, ol4 \n";
	std::vector<PurchaseHistory> t = h.getHistoriesByID(id1);
	for(auto i = t.begin(); i != t.end(); i++) {
		cout << i->printHistory() << "\n";
	}
	cout << "PHC testing for id6\nShould only contain ol1\n";
	t = h.getHistoriesByID(id6);
	for(auto i = t.begin(); i != t.end(); i++) {
		cout << i->printHistory() << "\n";
	}
	cout << "PHC testing for id5\nShould contain nothing (returns empty list) \n";
	t = h.getHistoriesByID(id5);
	for(auto i = t.begin(); i != t.end(); i++) {
		cout << i->printHistory() << "\n";
	}
	
	// GetByDate (Before, After, WithinDay) testing
	cout << "PHC testing for HistoriesBefore()\nShould contain ol4, ol1 \n";
	t = h.getAllHistoriesBefore(rawTime);
	for(auto i = t.begin(); i != t.end(); i++) {
		cout << i->printHistory() << "\n";
	}
	cout << "PHC testing for MemberHistoriesAfter()\nShould only contain ol3 \n";
	t = h.getMemberHistoriesAfter(id4, rawTime);
	for(auto i = t.begin(); i != t.end(); i++) {
		cout << i->printHistory() << "\n";
	}
	cout << "PHC testing for AllHistoriesWithinDay()\nShould contain everything (ol2, ol2, ol3, ol4, ol4, ol1, ol3, ol2) - random order, check number of order lists instead\n";
	t = h.getAllHistoriesWithinDay(lesserTime);
	for(auto i = t.begin(); i != t.end(); i++) {
		cout << i->printHistory() << "\n";
	}
	
	// Single deletion testing
	cout << "PHC testing for single PH retrieval for id6\nPH should be ol1\n";
	cout << h.getPurchaseHistory(id6, lesserTime).printHistory() << "\nMemberID(Should be " << id6 << ") = " << h.getPurchaseHistory(id6, lesserTime).getMemberID() << "\n";
	cout << "PHC testing for single PH deletion\nAttempting to delete id6\n;";
	int result = h.deletePurchaseHistory(id6, lesserTime);
	cout << "Del success return (Should be 0)\n" << result << "\n";
	result = h.deletePurchaseHistory(id6, lesserTime);
	cout << "Del fail return (Should be -1)\n" << result << "\n";
	PurchaseHistory temp = h.getPurchaseHistory(id6, lesserTime);
	cout << "Retrieved PH from id6, should be empty and id=0\n" << temp.printHistory() << "\nMemberID(Should be 0) = " << temp.getMemberID() << "\n";
	
	// Mass deletion testing
	cout << "\nPHC testing for MemberID based deletion\nAttempting to delete ALL id1\n";
	result = h.deleteAllHistoriesByMember(id1);
	cout << "Del success return (Should be 0)\n" << result << "\n";
	result = h.deleteAllHistoriesByMember(id1);
	cout << "Del fail return (Should be -1)\n" << result << "\n";
	cout << "PHC testing for id1\nShould contain nothing (returns empty list) \n";
	t = h.getHistoriesByID(id1);
	for(auto i = t.begin(); i != t.end(); i++) {
		cout << i->printHistory() << "\n";
	}
	cout << "\n\n----Test End----\n";
}

