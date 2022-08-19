#include "EmployeeManagement.h"

using namespace std;
static bool checkChange = false;

EmployeeManagement::EmployeeManagement() {
	int option = 1;
	string title = "=== QUAN LI NHAN VIEN ===";

	vector <string> listOption;
	listOption.push_back("1. Nhap thong tin nhan vien moi");
	listOption.push_back("2. Xem tat ca nhan vien");
	listOption.push_back("3. Tim kiem nhan vien");
	listOption.push_back("4. Chinh sua thong tin nhan vien");
	listOption.push_back("5. Xoa nhan vien qua ID");
	listOption.push_back("6. Quay lai");
	ReadFile();

	while (true) {
		option = bx->SelectOption(title, listOption, option);
		Employee* tempEmployee = new Employee;

		switch (option) {
		case 1:
			tempEmployee->InPut();
			listEmployee.push_back(tempEmployee);
			listEmployee.back()->Display();
			system("pause");
			system("cls");
			break;

		case 2:
			DisplayEmployee();
			system("pause");
			system("cls");
			break;

		case 3:
			SearchEmployee();
			system("pause");
			system("cls");
			break;

		case 4:
			EditInfoEmployee();
			system("cls");
			break;

		case 5:
			EraseEmployee();
			system("pause");
			system("cls");
			break;

		default:
			if (checkChange) {
				checkChange = false;
				ExitEmployeeManagement();
			}
			return;
		}
		delete tempEmployee;
	}
}

EmployeeManagement::EmployeeManagement(string employee) {
	ReadFile();
	string title = "=== THONG TIN NHAN VIEN ===";
	bx->gotoxy(44 + (40 - title.size()) / 2, 5);
	cout << title << endl;

	for (Employee *empl : listEmployee) {
		if (empl->GetiDEmployee() == employee) {
			empl->Display();
			break;
		}
	}
	system("pause");
	system("cls");
}

void EmployeeManagement::DisplayEmployee() {
	string title = "=== DANH SACH NHAN VIEN ===";
	bx->gotoxy(44 + (40 - title.size()) / 2, 5);
	cout << title << endl;

	for (int i = 0; i < listEmployee.size(); i++) {
		bx->TextColorDarkBlue();
		if (i != 0) {
			bx->gotoxy(bx->whereX() + 45, bx->whereY());
			cout << "------------------------------------- " << endl << endl;
		}
		bx->gotoxy(55, bx->whereY());
		cout << "Nhan vien thu " << i + 1 << ":" << endl;
		bx->TextColorDarkWhite();
		listEmployee[i]->Display();
	}
}

void EmployeeManagement::SearchEmployee() {
	string title = "=== TIM KIEM NHAN VIEN ===";
	string iDSearch;
	bx->gotoxy(44 + (40 - title.size()) / 2, 5);
	cout << title << endl;
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap ID can tim: ";
	getline(cin, iDSearch);
	const int NUMEMPLOYEE = listEmployee.size();
	int validID = 0;
	for (int i = 0; i < NUMEMPLOYEE; i++)
		if (listEmployee[i]->GetiDEmployee().find(iDSearch) < 5) {
			bx->TextColorDarkBlue();
			bx->gotoxy(55, bx->whereY());
			cout << "Nhan vien thu " << ++validID << ":" << endl;
			bx->TextColorDarkWhite();
			listEmployee[i]->Display();
			cout << endl;
		}
	bx->gotoxy(bx->whereX() + 44, bx->whereY());
	if (validID == 0) cout << "Khong co tim kiem phu hop" << endl;
}

void EmployeeManagement::EditInfoEmployee() {
	string iDEdit;
	bx->gotoxy(bx->whereX() + 45, 5);
	cout << "Nhap ID nhan vien can chinh sua: ";
	getline(cin, iDEdit);
	for (int i = 0; i < listEmployee.size(); i++) {
		if (listEmployee[i]->GetiDEmployee() == iDEdit) {
			int option = 1;
			string title = "=== CHINH SUA THONG TIN NHAN VIEN CO ID " + listEmployee[i]->GetiDEmployee() + " ===";

			vector<string> listOption;
			while (true) {
				listOption.push_back("Ten: " + listEmployee[i]->GetName());
				listOption.push_back("Gioi Tinh: " + listEmployee[i]->GetGender());
				listOption.push_back("Dia chi: " + listEmployee[i]->GetAddress());
				listOption.push_back("So dien thoai: " + listEmployee[i]->GetPhoneNumber());
				listOption.push_back("Ngay sinh: " + listEmployee[i]->GetBirthday());
				listOption.push_back("Quay lai");
				option = bx->SelectOption(title, listOption, option);
				if (option == listOption.size())
					return;
				OptionEditInfoEmployee(option, listEmployee[i]);
				system("cls");
				listOption.clear();
			}
		}
	}
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Khong co nhan vien co ID nay." << endl;
	system("pause");
}

void EmployeeManagement::OptionEditInfoEmployee(int option, Employee* employee) {
	string temp;
	bx->gotoxy(0, 6);

	switch (option) {
	case 1:
		do {
			bx->gotoxy(bx->whereX() + 51, bx->whereY());
			cout << "Nhap ten: ";
			getline(cin, temp);
			if (temp == "\0") 
				return;
			employee->SetName(temp);
			if (employee->CheckName()) {
				checkChange = true;
				break;
			}
			else {
				bx->gotoxy(bx->whereX() + 24, bx->whereY());
				bx->TextColorDarkBlue();
				cout << "Ten phai viet bang chu cai a->z, A - Z hoac bo trong de quay lai." << endl;
				bx->TextColorDarkWhite();
			}
		} while (true);
		break;
	case 2:
		do {
			bx->gotoxy(bx->whereX() + 51, bx->whereY());
			cout << "Nhap gioi tinh: ";
			getline(cin, temp);
			if (temp == "\0")
				return;
			employee->SetGender(temp);
			if (employee->CheckGender()) {
				checkChange = true;
				break;
			}
			else {
				bx->gotoxy(bx->whereX() + 17, bx->whereY());
				bx->TextColorDarkBlue();
				cout << "Gioi tinh la nam hoac nu (khong phan biet hoa, thuong) hoac bo trong de quay lai." << endl;
				bx->TextColorDarkWhite();
			}
		} while (true);
		break;
	case 3:
		bx->gotoxy(bx->whereX() + 51, bx->whereY());
		cout << "Nhap dia chi: ";
		getline(cin, temp);
		if (temp == "\0") 
			return;
		employee->SetAddress(temp);
		checkChange = true;
		break;
	case 4:
		do {
			bx->gotoxy(bx->whereX() + 51, bx->whereY());
			cout << "Nhap so dien thoai: ";
			getline(cin, temp);
			if (temp == "\0") 
				return;
			employee->SetPhoneNumber(temp);
			if (employee->CheckPhoneNumber()) {
				checkChange = true;
				break;
			}
			else {
				bx->gotoxy(bx->whereX() + 24, bx->whereY());
				bx->TextColorDarkBlue();
				cout << "So dien thoai phai bat dau bang 0 va co 10 chu so hoac bo trong de quay lai." << endl;
				bx->TextColorDarkWhite();
			}
		} while (true);
		break;
	case 5:
		bx->gotoxy(bx->whereX() + 51, bx->whereY());
		cout << "Nhap ngay sinh: ";
		getline(cin, temp);
		if (temp == "\0")
			return;
		employee->SetBirthday(temp);
		checkChange = true;
		break;
	default:
		break;
	}
}

void EmployeeManagement::EraseEmployee() {
	string iDErase;
	int option = 1;
	bx->gotoxy(bx->whereX() + 50, bx->whereY());
	cout << "Nhap ID nhan vien can xoa: ";
	getline(cin, iDErase);
	for (int i = 0; i < listEmployee.size(); i++) {
		if (listEmployee[i]->GetiDEmployee() == iDErase) {
			string title = "=== XOA NHAN VIEN CO ID " + listEmployee[i]->GetiDEmployee() + "? ===";

			vector<string> listOption;
			listOption.push_back("Co");
			listOption.push_back("Quay lai");
			option = bx->SelectOption(title, listOption, option);
			if (option == listOption.size())
				return;

			listEmployee.erase(listEmployee.begin() + i);
			bx->gotoxy(bx->whereX() + 45, bx->whereY() + 5);
			cout << "Da xoa nhan vien co iD: " << iDErase << endl;
			checkChange = true;

			return;
		}
	}
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Khong co nhan vien co ID nay" << endl;
}

void EmployeeManagement::ExitEmployeeManagement() {
	int option = 1;
	string title = "=== CO LUU THAY DOI KHONG? ===";

	vector<string> listOption;

	listOption.push_back("Co");
	listOption.push_back("Khong");
	option = bx->SelectOption(title, listOption, option);
	if (option == listOption.size() - 1)
		WriteFile();
	listOption.clear();
	listEmployee.clear();
}

void EmployeeManagement::ReadFile() {
	fstream filein;
	filein.open("EMPLOYEE.TXT", ios::in);
	if (!filein.fail()) {
		int size;
		string temp;
		int tempNum;

		filein >> size;
		getline(filein, temp);
		Employee* employee = new Employee[size];
		for (int i = 0; i < size; i++) {
			getline(filein, temp, ','); employee[i].SetiDEmployee(temp);
			getline(filein, temp, ','); employee[i].SetName(temp);
			getline(filein, temp, ','); employee[i].SetGender(temp);
			getline(filein, temp, ','); employee[i].SetAddress(temp);
			getline(filein, temp, ','); employee[i].SetPhoneNumber(temp);
			getline(filein, temp, ','); employee[i].SetBirthday(temp);
			filein >> tempNum; employee[i].SetSalary(tempNum);
			listEmployee.push_back(&employee[i]);
			getline(filein, temp);
		}
	}
	filein.close();
}

void EmployeeManagement::WriteFile() {
	fstream fileout;
	fileout.open("EMPLOYEE.TXT", ios::out);
	int size = listEmployee.size();
	fileout << size << endl;
	for (int i = 0; i < size; i++)
		fileout << listEmployee[i]->GetiDEmployee() + "," << listEmployee[i]->GetName() + "," << listEmployee[i]->GetGender() + ","
		<< listEmployee[i]->GetAddress() + "," << listEmployee[i]->GetPhoneNumber() + "," << listEmployee[i]->GetBirthday() + ","
		<< listEmployee[i]->GetSalary() << endl;
	fileout.close();
}