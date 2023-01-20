#include "main.h"

void Order::addEntry(const char* customer, const char* item, int quantity, int unitPrice)
{
	this->customer_ = customer;
	this->item_ = item;
	this->quantity_ = quantity;
	this->unitPrice_ = unitPrice;
}

void Order::printDataToFile(HANDLE hFile)
{
	std::string raw_data, str1, str2;
	str1 = std::to_string(quantity_);
	str2 = std::to_string(unitPrice_);
	raw_data.clear();
	raw_data += "������: " + customer_ + "\r\n�����: " + item_ + "\r\n����������: " + str1 + "\r\n���� �� ��: " + str2 + "\r\n\r\n";
	WriteFile(hFile, raw_data.c_str(), raw_data.length(), NULL, NULL);
}

int main(void)
{
	Order entry[12];

	entry[ 0].addEntry( "���������� 1",  "�����",	 3000, 10  );
	entry[ 1].addEntry( "���������� 2",  "����",	 250,  12  );
	entry[ 2].addEntry( "���������� 3",  "�����",	 1600, 8   );
	entry[ 3].addEntry( "���������� 4",  "�����",	 5900, 16  );
	entry[ 4].addEntry( "���������� 5",  "������",	 640,  60  );
	entry[ 5].addEntry( "���������� 6",  "�����",	 500,  23  );
	entry[ 6].addEntry( "���������� 7",  "������",	 200,  117 );
	entry[ 7].addEntry( "���������� 8",  "�����",	 4100, 9   );
	entry[ 8].addEntry( "���������� 9",  "��������", 880,  42  );
	entry[ 9].addEntry( "���������� 10", "����",	 2300, 18  );
	entry[10].addEntry( "���������� 11", "��������", 15,   60  );
	entry[11].addEntry( "���������� 12", "�����",	 158,  55  );

	HANDLE hOut1 = CreateFile("output_item.txt",     GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hOut2 = CreateFile("output_quantity.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	HANDLE hOut3 = CreateFile("output_price.txt",	 GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ((hOut1 != INVALID_HANDLE_VALUE) && (hOut2 != INVALID_HANDLE_VALUE) && (hOut3 != INVALID_HANDLE_VALUE))
	{
		sortByItem(entry);
		for (int i = 0; i < 12; i++)
			entry[i].printDataToFile(hOut1);

		sortByQuantity(entry);
		for (int i = 0; i < 12; i++)
			entry[i].printDataToFile(hOut2);

		sortByPrice(entry);
		for (int i = 0; i < 12; i++)
			entry[i].printDataToFile(hOut3);
	}
	else return -1;
}

void sortByItem(Order *entry)
{
	for (int i = 0; i < 12; i++)
	{
		int max = i;
		for (int j = i + 1; j < 12; j++)
			if (strcmp(entry[max].item_.c_str(), entry[j].item_.c_str()) > 0)
				max = j;
		Order temp = entry[i];
		entry[i] = entry[max];
		entry[max] = temp;
	}
}

void sortByQuantity(Order *entry)
{
	for (int i = 0; i < 12; i++)
	{
		int max = i;
		for (int j = i + 1; j < 12; j++)
			if (entry[max].quantity_ > entry[j].quantity_)
				max = j;
		Order temp = entry[i];
		entry[i] = entry[max];
		entry[max] = temp;
	}
}

void sortByPrice(Order *entry)
{
	for (int i = 0; i < 12; i++)
	{
		int max = i;
		for (int j = i + 1; j < 12; j++)
			if (entry[max].unitPrice_ > entry[j].unitPrice_)
				max = j;
		Order temp = entry[i];
		entry[i] = entry[max];
		entry[max] = temp;
	}
}
