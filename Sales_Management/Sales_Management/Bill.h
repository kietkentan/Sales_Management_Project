#pragma once
#include <iostream>
#include <ctime>
#include <string.h>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include "Box_Draw.h"
#include "Employee.h"
#include "Product.h"

using namespace std;

class Bill :public Employee {
private:
	string iD;
	string creationDate;
	string creationTime;
	int VAT;
	int totalPayment;
	vector <Product*> selectProductList;
	Box_Draw* box = new Box_Draw;

public:
	bool CreateBill (vector <Employee*> listEmployee, vector <Product*> listProduct, vector <Bill*> listBill, string iDEmployee);
	void Display();
	string getCurrentDate();
	string getCurrentTime();

	Bill();
	~Bill();

	bool CheckiDBill();
	int CheckiDEmployee(string data, vector <Employee*> listEmployee);
	int CheckiDProduct(string data, vector <Product*> listProduct);

	void SetiDBill(string data);
	string GetiDBill();
	void SetCreationDate(string data);
	string GetCreationDate();
	void SetCreationTime(string data);
	string GetCreationTime();
	void SetVAT(int data);
	int GetVAT();
	void SetTotalPayment(int data);
	int GetTotalPayment();
	void SetListProduct(vector <Product*> product);
	vector <Product*> GetListProduct();
};