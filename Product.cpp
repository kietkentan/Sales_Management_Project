#include <string>
#include <iomanip>
#include "Product.h"

using namespace std;

void Product::InPut() {
	fflush(stdin);
	box->gotoxy(0, 5);
	do {
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap ID (Bat buoc): ";
		getline(cin, iD);
		if (CheckiD()) 
			break;
		cout << endl;
		box->gotoxy(box->whereX() + 29, box->whereY());
		box->TextColorDarkBlue();
		cout << "ID phai bat dau bang chu cai (a -> z, A -> Z) va 6 chu so (0 - 9)." << endl;
		box->TextColorDarkWhite();
	} while (true);
	box->gotoxy(box->whereX() + 51, box->whereY());
	cout << "Nhap ten: ";
	getline(cin, name);

	do {
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap gia: ";
		cin >> price;
		if (CheckPrice()) 
			break;
		cout << endl;
		box->gotoxy(box->whereX() + 39, box->whereY());
		box->TextColorDarkBlue();
		cout << "Gia phai la so duong." << endl;
		box->TextColorDarkWhite();
	} while (true);

	do {
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap so luong: ";
		cin >> amount;
		if (CheckAmount()) 
			break;
		cout << endl;
		box->gotoxy(box->whereX() + 30, box->whereY());
		box->TextColorDarkBlue();
		cout << "So luong phai la so duong." << endl;
		box->TextColorDarkWhite();
	} while (true);
	box->gotoxy(box->whereX() + 51, box->whereY());
	cout << "Nhap ngay nhap hang:  ";
	cin.ignore();
	getline(cin, latestImportDate);
}

void Product::Display() {
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "ID:" << setw(20) << right << iD << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(4) << left << "Ten:" << setw(33) << right << name << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "Gia:" << setw(20) << right << price << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "So luong:" << setw(20) << right << amount << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "Ngay nhap hang:" << setw(20) << right << latestImportDate << endl;
}

int Product::TotalPrice() {
	return price * amount;
}

Product::Product() {}
Product::~Product() {}

bool Product::CheckiD() {
	if (iD == "\0") return false;
	if ((iD.front() >= 65 && iD.front() <= 90) || (iD.front() >= 97 && iD.front() <= 122))
		if (iD.length() == 7) {
			for (int i = 1; i < iD.length(); i++)
				if (!isdigit(iD[i])) return false;
			return true;
		}
	return false;
}

bool Product::CheckPrice() {
	if (price <= 0) return false;
	return true;
}

bool Product::CheckAmount() {
	if (amount < 0) return false;
	return true;
}

void Product::SetiDProduct(string data) {
	iD = data;
}

string Product::GetiDProduct() {
	return iD;
}

void Product::SetName(string data) {
	name = data;
}

string Product::GetName() {
	return name;
}

void Product::SetPrice(int data) {
	price = data;
}

int Product::GetPrice() {
	return price;
}

void Product::SetAmount(int data) {
	amount = data;
}

int Product::GetAmount() {
	return amount;
}

void Product::SetLatestImportDate(string data) {
	latestImportDate = data;
}

string Product::GetLatestImportDate() {
	return latestImportDate;
}