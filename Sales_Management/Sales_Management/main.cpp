/*
	Create by Le Tuan Kiet (4/2022)
	User employee is Id and passcode is 111111
	User management is admin1 or andmin2, passcode is 123456
*/

#include "ProductManagement.h"
#include "EmployeeManagement.h"
#include "BillManagement.h"
#include "MD5.h"

using namespace std;

string employee = "";

Box_Draw* bx = new Box_Draw;

bool LoginManagementSession() {
	MD5* md5 = new MD5;
	string userName, passWord;
	char ch;

	system("cls");
	bx->gotoxy(bx->whereX(), 5);

	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap tai khoan: ";
	getline(cin, userName);
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap mat khau: ";
	do {
		ch = _getch();
		if (ch == 8) {
			if (!(passWord.empty())) {
				passWord.pop_back();
				bx->gotoxy(bx->whereX() - 1, bx->whereY());
				cout << ' ';
				bx->gotoxy(bx->whereX() - 1, bx->whereY());
			}
		}
		else if (ch >= ' ' && ch <= '~') {
			passWord.push_back(ch);
			cout << '*';
		}
	} while (ch != 13);
	cout << endl;

	if (md5->md5(userName, passWord)) {
		system("cls");
		return true;
	}
	bx->gotoxy(bx->whereX() + 40, bx->whereY());
	cout << "Tai khoan hoac mat khau khong dung" << endl;
	system("pause");
	system("cls");
	return false;
}

bool LoginEmployeeSession() {
	fstream fileinEmployee;
	vector <string> listUser;
	int size;
	string tempUser;
	char ch;

	fileinEmployee.open("EMPLOYEE.TXT", ios::in);
	fileinEmployee >> size;
	getline(fileinEmployee, tempUser);
	for (int i = 0; i < size; i++) {
		getline(fileinEmployee, tempUser, ','); listUser.push_back(tempUser);
		getline(fileinEmployee, tempUser);
	}

	fileinEmployee.close();

	if (employee != "")
		for (string user : listUser)
			if (user == employee)
				return true;

	string userName, passWord;
	system("cls");
	bx->gotoxy(bx->whereX(), 5);

	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap tai khoan: ";
	getline(cin, userName);
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap mat khau: ";
	do {
		ch = _getch();
		if (ch == 8) {
			if (!(passWord.empty())) {
				passWord.pop_back();
				bx->gotoxy(bx->whereX() - 1, bx->whereY());
				cout << ' ';
				bx->gotoxy(bx->whereX() - 1, bx->whereY());
			}
		}
		else if (ch >= ' ' && ch <= '~') {
			passWord.push_back(ch);
			cout << '*'; 
		}
	} while (ch != 13);
	cout << endl;

	for (string user : listUser)
		if (user == userName && passWord == "111111") {
			employee = userName;
			system("cls");
			return true;
		}
	bx->gotoxy(bx->whereX() + 40, bx->whereY());
	cout << "Tai khoan hoac mat khau khong dung" << endl;
	system("pause");
	system("cls");
	return false;
}

void MenuManagement() {
	int option = 1;
	string title = "== CHUONG TRINH QUAN LI ==";

	vector<string> listOption;

	listOption.push_back("1. Quan li nhan vien");
	listOption.push_back("2. Quan li san pham");
	listOption.push_back("3. Quan li hoa don");
	listOption.push_back("4. Quay lai");
	while (true) {
		option = bx->SelectOption(title, listOption, option);
		EmployeeManagement* employeeManagement;
		ProductManagement* productManagement;
		BillManagement* billManagement;

		switch (option) {
		case 1:
			employeeManagement = new EmployeeManagement;
			delete employeeManagement;
			break;

		case 2:
			productManagement = new ProductManagement;
			delete productManagement;
			break;

		case 3:
			billManagement = new BillManagement;
			delete billManagement;
			break;

		default:
			return;
		}
	}
}

void MenuEmployee() {
	int option = 1;
	string title = "== CHUONG TRINH NHAN VIEN ==";

	vector<string> listOption;
	listOption.push_back("1. Xem thong tin ca nhan");
	listOption.push_back("2. Tao hoa don moi");
	listOption.push_back("3. Doi ca nhan vien");
	listOption.push_back("4. Tan ca nhan vien");
	listOption.push_back("5. Quay lai");

	vector<string> listOptionYesNo;
	listOptionYesNo.push_back("Co");
	listOptionYesNo.push_back("Khong");

	while (true) {
		option = bx->SelectOption(title, listOption, option);
		EmployeeManagement* employeeManagement;
		BillManagement* billManagement;

		switch (option) {
		case 1:
			employeeManagement = new EmployeeManagement(employee);
			delete employeeManagement;
			break;

		case 2:
			billManagement = new BillManagement(employee);
			delete billManagement;
			break;

		case 3:
			if (bx->SelectOption("DOI CA HAY KHONG?", listOptionYesNo, 1) == 1) {
				employee = "";
				if (LoginEmployeeSession())
					break;
				else return;
			}
			break;

		case 4:
			if (bx->SelectOption("TAN CA HAY KHONG?", listOptionYesNo, 1) == 1)
				employee = "";

		default:
			return;
		}
	}
}

void Start() {
	int option = 1;
	string title = "== CHUONG TRINH QUAN LI ==";

	vector<string> listOption;
	listOption.push_back("1. Trang danh cho quan li");
	listOption.push_back("2. Trang danh cho nhan vien");
	listOption.push_back("3. Thoat");
	do {
		option = bx->SelectOption(title, listOption, option);
		switch (option) {
		case 1:
			if (LoginManagementSession())
				MenuManagement();
			break;

		case 2:
			if (LoginEmployeeSession())
				MenuEmployee();
			break;

		default:
			exit(0);
		}
	} while (true);
}

void main() {
	Start();
}