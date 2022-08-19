#pragma once
#include <iostream>
#include "Box_Draw.h"

using namespace std;

class Product {
private:
	string iD;
	string name;
	int price;
	int amount;
	string latestImportDate;

	Box_Draw* box = new Box_Draw;

public:
	void InPut();
	void Display();
	int TotalPrice();

	Product();
	~Product();

	bool CheckiD();
	bool CheckPrice();
	bool CheckAmount();

	void SetiDProduct(string data);
	string GetiDProduct();
	void SetName(string data);
	string GetName();
	void SetPrice(int data);
	int GetPrice();
	void SetAmount(int data);
	int GetAmount();
	void SetLatestImportDate(string data);
	string GetLatestImportDate();
};
