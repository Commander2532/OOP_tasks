#pragma once

#include <string>
#include <stdlib.h>
#include <windows.h>

class Order
{
public:
	
	std::string customer_;
	std::string item_;
	int	quantity_;
	int unitPrice_;
	int sortValue_;

	Order(void) {};
	void addEntry(const char* customer, const char* item, int quantity, int unitPrice);
	void printDataToFile(HANDLE hFile);
	~Order(void) {};
};

void sortByItem(Order *entry);
void sortByQuantity(Order *entry);
void sortByPrice(Order *entry);