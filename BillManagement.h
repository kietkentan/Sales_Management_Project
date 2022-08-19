#pragma once
#include "Bill.h"
#include <fstream>
#include "Box_Draw.h"

class BillManagement {
private:
	Box_Draw* bx = new Box_Draw;
	fstream fileProduct, fileEmployee, fileBill;

	vector <Bill*> listBill;
	vector <Employee*> listEmployee;
	vector <Product*> listProduct;

public:
	BillManagement();
	BillManagement(string employee);
	void DisplayBill();
	void SearchBill();
	void EditInfoBill();
	void OptionEditInfoBill(int option, Bill* bill);
	void EraseBill();
	void ExitBillManagement();
	void ReadFile();
	void WriteFile();
};
