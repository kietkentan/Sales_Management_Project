#include "Bill.h"

bool Bill::CreateBill(vector <Employee*> listEmployee, vector <Product*> listProduct, vector <Bill*> listBill, string iDEmployee) {
	string temp;
	
	box->gotoxy(box->whereX() + 44, box->whereY());
	cout << setw(10) << left << "ID" << setw(32) << left << "Ten san pham" << setw(5) << right << "SL" << endl;
	for (int i = 0; i < listProduct.size(); i++) {
		box->gotoxy(box->whereX() + 44, box->whereY());
		cout << setw(10) << left << listProduct[i]->GetiDProduct() << setw(32) << left << listProduct[i]->GetName() << setw(5) << right << listProduct[i]->GetAmount() << endl;
	}
	fflush(stdin);
	box->gotoxy(box->whereX(), box->whereY() + 3);
	iD = listBill.back()->GetiDBill();
	do {
		iD = to_string(atoi(iD.c_str()) + 1);
		if (CheckiDBill())
			break;
	} while (true);

	creationDate = getCurrentDate();
	creationTime = getCurrentTime();

	for (int i = 0; i < listEmployee.size(); i++) {
		if (listEmployee[i]->GetiDEmployee() == iDEmployee) {
			SetiDEmployee(iDEmployee);
			SetName(listEmployee[i]->GetName());
		}
	}

	do {
		Product* product = new Product;
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap ID san pham: ";
		getline(cin, temp);
		if (_stricmp(temp.c_str(), "end") == 0) {
			return true;
		}
		else if (_stricmp(temp.c_str(), "exit") == 0) {
			return false;
		}

		int numberProduct = CheckiDProduct(temp, listProduct);
		if (numberProduct >= 0) {
			product->SetiDProduct(temp);
			product->SetName(listProduct[numberProduct]->GetName());

			do {
				box->gotoxy(box->whereX() + 51, box->whereY());
				cout << "Nhap so luong: ";
				getline(cin, temp);
				fflush(stdin);
				bool checkNum = true;
				for (int i = 0; i < temp.size(); i++) {
					if (!isdigit(temp[i])) {
						checkNum = false;
						break;
					}
				}
				int tempi = 0;
				if (checkNum) 
					tempi = atoi(temp.c_str());
				if (tempi == 0) {
					box->gotoxy(box->whereX() + 48, box->whereY());
					box->TextColorDarkBlue();
					cout << "So luong khong dung." << endl;
					box->TextColorDarkWhite();
				}
				else if (listProduct[numberProduct]->GetAmount() >= tempi) {
					product->SetAmount(tempi);
					listProduct[numberProduct]->SetAmount(listProduct[numberProduct]->GetAmount() - tempi);
					product->SetPrice(listProduct[numberProduct]->GetPrice());
					selectProductList.push_back(product);
					totalPayment += product->GetPrice() * tempi;
					VAT += product->GetPrice() * tempi / 20;
					break;
				}
				else {
					box->gotoxy(box->whereX() + 49, box->whereY());
					box->TextColorDarkBlue();
					cout << "So luong khong du." << endl;
					box->TextColorDarkWhite();
				}
			} while (true);
			cin.ignore();
		}
		else {
			box->gotoxy(box->whereX() + 49, box->whereY());
			box->TextColorDarkBlue();
			cout << "Khong co san pham nay." << endl;
			box->TextColorDarkWhite();
		}
	} while (true);
}

void Bill::Display() {
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << setw(17) << left << "ID:" << setw(30) << right << iD << endl;
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << setw(17) << left << "Ten nhan vien:" << setw(30) << right << GetName() << endl;
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << setw(17) << left << "Thoi gian:" << setw(13) << left << creationDate << setw(17) << right << creationTime << endl;
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << "-----------------------------------------------" << endl;
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << setw(32) << left << "Ten san pham" << setw(4) << left << "SL" << setw(11) << right << "Gia" << endl;
	int n = selectProductList.size();
	for (int i = 0; i < n; i++) {
		box->gotoxy(box->whereX() + 40, box->whereY());
		cout << setw(32) << left << selectProductList[i]->GetName() << setw(4) << left << selectProductList[i]->GetAmount() 
			<< setw(11) << right << selectProductList[i]->GetPrice() << endl;
	}
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << setw(5) << left << "VAT:" << setw(42) << right << VAT << endl;
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << setw(47) << right << "-------------" << endl;
	box->gotoxy(box->whereX() + 40, box->whereY());
	cout << setw(15) << left << "Tien phai tra:" << setw(32) << right << totalPayment + VAT << endl;
}

string Bill::getCurrentDate() {
	time_t tStart = time(NULL);
	struct tm tmStart;

	localtime_s(&tmStart, &tStart);

	return to_string(tmStart.tm_mday) + "/" + to_string(tmStart.tm_mon + 1) + "/" + to_string(tmStart.tm_year + 1900);
}

string Bill::getCurrentTime() {
	time_t tStart = time(NULL);
	struct tm tmStart;

	localtime_s(&tmStart, &tStart);

	return to_string(tmStart.tm_hour) + ":" + to_string(tmStart.tm_min) + ":" + to_string(tmStart.tm_sec);
}

Bill::Bill() {}
Bill::~Bill() {}

bool Bill::CheckiDBill() {
	if (iD == "\0") 
		return false;

	int lengthID = iD.length();
	if (lengthID > 8)
		return false;
	else {
		int m = 8 - lengthID;
		for (int i = 0; i < lengthID; i++)
			if (!isdigit(iD[i])) 
				return false;
		for (int i = 0; i < m; i++)
			SetiDBill('0' + iD);
	}
	return true;
}

int Bill::CheckiDEmployee(string data, vector <Employee*> listEmployee) {
	if (data == "\0") return -1;
	else {
		int n = listEmployee.size();
		for (int i = 0; i < n; i++)
			if (_stricmp(data.c_str(), listEmployee[i]->GetiDEmployee().c_str()) == 0) 
				return i;
		return -2;
	}
}

int Bill::CheckiDProduct(string data, vector <Product*> listProduct) {
	int n = listProduct.size();
	char* b = new char[8];
	for (int i = 0; i < n; i++) {
		strcpy_s(b, 8, listProduct[i]->GetiDProduct().c_str());
		if (_stricmp(data.c_str(), b) == 0) 
			return i;
	}
	return -1;
}

void Bill::SetiDBill(string data) {
	iD = data;
}

string Bill::GetiDBill() {
	return iD;
}

void Bill::SetCreationDate(string data) {
	creationDate = data;
}

string Bill::GetCreationDate() {
	return creationDate;
}

void Bill::SetCreationTime(string data) {
	creationTime = data;
}

string Bill::GetCreationTime() {
	return creationTime;
}

void Bill::SetVAT(int data) {
	VAT = data;
}

int Bill::GetVAT() {
	return VAT;
}

void Bill::SetTotalPayment(int data) {
	totalPayment = data;
}

int Bill::GetTotalPayment() {
	return totalPayment;
}

void Bill::SetListProduct(vector <Product*> product) {
	selectProductList = product;
}

vector <Product*> Bill::GetListProduct() {
	return selectProductList;
}