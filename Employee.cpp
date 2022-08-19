#include <string.h>
#include <iomanip>
#include "Employee.h"

using namespace std;

void Employee::InPut() {
	fflush(stdin);
	box->gotoxy(0, 5);
	do {
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap ID (Bat buoc): ";
		getline(cin, iD);
		if (CheckID()) 
			break;
		box->gotoxy(box->whereX() + 29, box->whereY());
		box->TextColorDarkBlue();
		cout << "ID phai bat dau bang chu cai (a -> z, A -> Z) va 4 chu so (0 - 9)." << endl;
		box->TextColorDarkWhite();

	} while (true);

	do {
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap ten: ";
		getline(cin, name);
		if (CheckName()) 
			break;
		box->gotoxy(box->whereX() + 37, box->whereY());
		box->TextColorDarkBlue();
		cout << "Ten phai viet bang chu cai a->z, A-Z hoac bo trong." << endl;
		box->TextColorDarkWhite();
	} while (true);

	do {
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap gioi tinh: ";
		getline(cin, gender);
		if (CheckGender()) 
			break;
		box->gotoxy(box->whereX() + 36, box->whereY());
		box->TextColorDarkBlue();
		cout << "Gioi tinh la nam hoac nu (khong phan biet hoa, thuong)." << endl;
		box->TextColorDarkWhite();
	} while (true);

	box->gotoxy(box->whereX() + 51, box->whereY());
	cout << "Nhap dia chi: ";
	getline(cin, address);
	address.erase(remove(address.begin(), address.end(), ','), address.end());

	do {
		box->gotoxy(box->whereX() + 51, box->whereY());
		cout << "Nhap so dien thoai: ";
		getline(cin, phoneNumber);
		if (CheckPhoneNumber()) 
			break;
		box->gotoxy(box->whereX() + 30, box->whereY());
		box->TextColorDarkBlue();
		cout << "So dien thoai phai bat dau bang 0 va co 10 chu so, hoac bo trong." << endl;
		box->TextColorDarkWhite();
	} while (true);

	box->gotoxy(box->whereX() + 51, box->whereY());
	cout << "Nhap ngay sinh:  ";
	getline(cin, birthday);
	box->gotoxy(box->whereX() + 51, box->whereY());
	cout << "Nhap luong:  ";
	cin >> salary;
}

void Employee::Display() {
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "ID:" << setw(20) << right << iD << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "Ten:" << setw(20) << right << name << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "Gioi tinh:" << setw(20) << right << gender << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "Dia chi:" << setw(20) << right << address << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "So dien thoai:" << setw(20) << right << phoneNumber << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "Ngay sinh:" << setw(20) << right << birthday << endl;
	box->gotoxy(box->whereX() + 45, box->whereY());
	cout << setw(17) << left << "Luong:" << setw(20) << right << salary << endl;
}

Employee::Employee() {}
Employee::~Employee() {}

bool Employee::CheckID() {
	if (iD == "\0") 
		return false;

	if ((iD.front() >= 65 && iD.front() <= 90) || (iD.front() >= 97 && iD.front() <= 122))
		if (iD.length() == 5) {
			for (int i = 1; i < iD.length(); i++)
				if (!isdigit(iD[i])) 
					return false;
			return true;
		}
	return false;
}

bool Employee::CheckName() {
	if (name == "\0") 
		return true;

	string tempName = name;
	tempName.erase(remove(tempName.begin(), tempName.end(), ' '), tempName.end());
	if (tempName == "\0") {
		name = tempName;
		return true;
	}
	else {
		for (int i = 0; i < name.length(); i++)
			if (!(name[i] == 32 || (name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122)))
				return false;
	}
	return true;
}

bool Employee::CheckPhoneNumber() {
	phoneNumber.erase(remove(phoneNumber.begin(), phoneNumber.end(), ' '), phoneNumber.end());
	if (phoneNumber == "\0") 
		return true;

	else if (phoneNumber.front() == '0' && phoneNumber.length() == 10) {
		for (int i = 0; i < 10; i++) {
			if (!isdigit(phoneNumber[i]))
				return false;
			return true;
		}
	}
	return false;
}

bool Employee::CheckGender() {
	gender.erase(remove(gender.begin(), gender.end(), ' '), gender.end());
	gender.erase(remove(gender.begin(), gender.end(), ','), gender.end());
	if (gender == "\0") 
		return true;

	else
		if (gender.size() == 2) {
			char a[] = "nu";
			char* b = new char[3];
			strcpy_s(b, 3, gender.c_str());
			if (_stricmp(a, b) == 0) 
				return true;
		}
		else if (gender.size() == 3) {
			char a[] = "nam";
			char* b = new char[4];
			strcpy_s(b, 4, gender.c_str());
			if (_stricmp(a, b) == 0) 
				return true;
		}
	return false;
}

void Employee::SetiDEmployee(string data) {
	iD = data;
}

string Employee::GetiDEmployee() {
	return iD;
}

void Employee::SetName(string data) {
	name = data;
}

string Employee::GetName() {
	return name;
}

void Employee::SetGender(string data) {
	gender = data;
}

string Employee::GetGender() {
	return gender;
}

void Employee::SetAddress(string data) {
	address = data;
}

string Employee::GetAddress() {
	return address;
}

void Employee::SetPhoneNumber(string data) {
	phoneNumber = data;
}

string Employee::GetPhoneNumber() {
	return phoneNumber;
}

void Employee::SetBirthday(string data) {
	birthday = data;
}

string Employee::GetBirthday() {
	return birthday;
}

void Employee::SetSalary(int data) {
	salary = data;
}

int Employee::GetSalary() {
	return salary;
}