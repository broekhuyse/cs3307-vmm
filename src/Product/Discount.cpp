#include "Discount.h"
using namespace std;

Discount::Discount()
{
}

Discount::Discount(string product, float amount, int day, int month, int year){
    this->productID = product;
    this->amount = amount;
    this->endDate = tm();
    endDate.tm_mday = day;
    endDate.tm_mon = month;
    endDate.tm_year = year;
}

Discount::~Discount()
{
}

string Discount::getProductID(){
    return productID;
}

float Discount::getAmount(){
    return amount;
}

bool Discount::checkDate(){
    return false;
}