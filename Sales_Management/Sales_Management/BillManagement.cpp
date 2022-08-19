#include "BillManagement.h"

using namespace std;
static bool checkChange = false;

BillManagement::BillManagement() {
	ReadFile();
	int option = 1;
	string title = "=== QUAN LI HOA DON ===";

	vector<string> listOption;
	listOption.push_back("1. Xem tat ca hoa don");
	listOption.push_back("2. Tim kiem hoa don");
	listOption.push_back("3. Chinh sua thong tin hoa don");
	listOption.push_back("4. Xoa hoa don");
	listOption.push_back("5. Quay lai");

	while (true) {
		option = bx->SelectOption(title, listOption, option);

		switch (option) {
		case 1:
			DisplayBill();
			system("pause");
			system("cls");
			break;

		case 2:
			SearchBill();
			system("pause");
			system("cls");
			break;

		case 3:
			EditInfoBill();
			system("cls");
			break;

		case 4:
			EraseBill();
			system("pause");
			system("cls");
			break;

		default:
			if (checkChange) {
				checkChange = false;
				ExitBillManagement();
			}
			return;
		}
	}
}

BillManagement::BillManagement(string employee) {
	ReadFile();
	Bill* bill = new Bill;
	if (bill->CreateBill(listEmployee, listProduct, listBill, employee)) {
		listBill.push_back(bill);
		system("cls");
		bx->gotoxy(0, 5);
		bill->Display();
		WriteFile();
	}
	else {
		bx->gotoxy(bx->whereX() + 47, bx->whereY());
		cout << "Da ngung tao hoa don" << endl;
	}
	delete bill;
	system("pause");
	system("cls");
}

void BillManagement::DisplayBill() {
	string title = "=== DANH SACH HOA DON ===";
	bx->gotoxy(45 + (40 - title.size()) / 2, 5);
	cout << title << endl;

	for (int i = 0; i < listBill.size(); i++) {
		bx->TextColorDarkBlue();
		if (i != 0) {
			bx->gotoxy(bx->whereX() + 40, bx->whereY());
			cout << "-----------------------------------------------" << endl << endl;
		}
		bx->gotoxy(57, bx->whereY());
		cout << "Hoa don thu " << i + 1 << ":" << endl << endl;
		bx->TextColorDarkWhite();
		listBill[i]->Display();
	}
}

void BillManagement::SearchBill() {
	string title = "=== TIM KIEM HOA DON ===";
	string iD;
	bx->gotoxy(44 + (40 - title.size()) / 2, 5);
	cout << title << endl;
	bx->gotoxy(bx->whereX() + 52, bx->whereY());
	cout << "Nhap ID can tim: ";
	getline(cin, iD);
	int size = listBill.size();
	int validID = 0;
	for (int i = 0; i < size; i++)
		if (listBill[i]->GetiDBill().find(iD) < 8) {
			bx->TextColorDarkBlue();
			bx->gotoxy(57, bx->whereY());
			cout << "Hoa don thu " << ++validID << ":" << endl;
			bx->TextColorDarkWhite();
			listBill[i]->Display();
			cout << endl;
		}
	bx->gotoxy(bx->whereX() + 44, bx->whereY());
	if (validID == 0) cout << "Khong co tim kiem phu hop" << endl;
}

void BillManagement::EditInfoBill() {
	string iDEdit;
	bx->gotoxy(bx->whereX() + 46, 5);
	cout << "Nhap ID hoa don can chinh sua: ";
	getline(cin, iDEdit);
	system("cls");

	for (int i = 0; i < listBill.size(); i++) {
		if (_stricmp(iDEdit.c_str(), listBill[i]->GetiDBill().c_str()) == 0) {
			int option = 1;
			string title = "=== CHINH SUA THONG TIN HOA DON CO ID " + listBill[i]->GetiDBill() + " ===";

			vector<string> listOption;
			while (true) {
				listOption.push_back("Ten NV: " + listBill[i]->GetName());
				listOption.push_back("Ngay lap: " + listBill[i]->GetCreationDate());
				listOption.push_back("Gio lap: " + listBill[i]->GetCreationTime());
				for (int j = 0; j < listBill[i]->GetListProduct().size(); j++) {
					listOption.push_back("Ten SP: " + listBill[i]->GetListProduct()[j]->GetName());
					listOption.push_back("So luong: " + to_string(listBill[i]->GetListProduct()[j]->GetAmount()));
				}
				listOption.push_back("Quay lai");

				option = bx->SelectOption(title, listOption, option);
				if (option == listOption.size())
					return;
				else if (option != 2 && option != 3)
					OptionEditInfoBill(option, listBill[i]);
				listOption.clear();	
			}
		}
	}
	bx->gotoxy(bx->whereX() + 52, bx->whereY());
	cout << "Khong co hoa don co ID nay." << endl;
	system("pause");
}

void BillManagement::OptionEditInfoBill(int option, Bill* bill) {
	string temp;
	int tempi;
	bool checknv;

	if (option == 4 + bill->GetListProduct().size() * 2)
		return;
	bx->gotoxy(0, 6);

	if (option == 1) {
		checknv = true;
		do {
			bx->gotoxy(bx->whereX() + 51, bx->whereY());
			cout << "Nhap ID nhan vien: ";
			getline(cin, temp);
			system("cls");
			int numberEmployee = bill->CheckiDEmployee(temp, listEmployee);
			if (temp == "\0")
				return;

			if (numberEmployee == -1) {
				checknv = false;
				goto endnhapten;
			}
			else if (numberEmployee == -2) 
				goto nhapidnv;
			else if (numberEmployee >= 0) {
				bill->SetiDEmployee(temp);
				bill->SetName(listEmployee[numberEmployee]->GetName());
				return;
			}
		nhapidnv:;
			bx->gotoxy(bx->whereX() + 51, bx->whereY());
			bx->TextColorDarkBlue();
			cout << "Khong co nhan vien nay." << endl;
			bx->TextColorDarkWhite();
		endnhapten:;
		} while (checknv); 
		system("cls");
	}
	else {
		bool checksp;
		int optionProduct = option - 3;
		if (!(optionProduct & 1)) {
			optionProduct = optionProduct / 2 - 1;
			string iDProduct = bill->GetListProduct()[optionProduct]->GetiDProduct();
			int numberProduct = bill->CheckiDProduct(iDProduct, listProduct);

			if (numberProduct >= 0) {
				int amountInStock = listProduct[numberProduct]->GetAmount();
				int amountInBill = bill->GetListProduct()[optionProduct]->GetAmount();
			nhapsoluong:;
				bx->gotoxy(bx->whereX() + 51, bx->whereY());
				cout << "Nhap so luong: ";
				cin >> tempi;
				system("cls");
				if (tempi <= 0) {
					listProduct[numberProduct]->SetAmount(amountInStock + amountInBill);
					bill->SetTotalPayment(bill->GetTotalPayment() - amountInBill * bill->GetListProduct()[optionProduct]->GetPrice());
					bill->SetVAT(bill->GetVAT() - amountInBill * bill->GetListProduct()[optionProduct]->GetPrice() / 20);
					vector <Product*> product;
					bill->GetListProduct().swap(product);
					product.erase(product.begin() + optionProduct);
					bill->SetListProduct(product);
					cin.ignore();
					checkChange = true;
					return;
				}
				if (amountInStock + amountInBill >= tempi) {
					listProduct[numberProduct]->SetAmount(amountInStock + amountInBill - tempi);
					bill->GetListProduct()[optionProduct]->SetAmount(tempi);
					bill->SetTotalPayment(bill->GetTotalPayment() - (amountInBill - tempi) * bill->GetListProduct()[optionProduct]->GetPrice());
					bill->SetVAT(bill->GetVAT() - (amountInBill - tempi) * bill->GetListProduct()[optionProduct]->GetPrice() / 20);
					cin.ignore();
					checkChange = true;
					return;
				}
				else {
					bx->gotoxy(bx->whereX() + 49, bx->whereY());
					bx->TextColorDarkBlue();
					cout << "So luong khong du." << endl;
					bx->TextColorDarkWhite();
					goto nhapsoluong;
				}
				cin.ignore();
			}
		}
		else {
			optionProduct = (optionProduct - 1) / 2;
			checksp = true;
			do {
				bx->gotoxy(bx->whereX() + 51, bx->whereY());
				cout << "Nhap ID san pham: ";
				getline(cin, temp);
				int numberProduct = bill->CheckiDProduct(temp, listProduct);
				if (numberProduct < 0) {
					if (numberProduct == -1) {
						checksp = false;
						continue;
					}
					if (temp == "\0") {
						checksp = false;
						continue;
					}
					else if (numberProduct == -2) 
						goto nhapidsp;
				}
				else if (numberProduct >= 0) {
					string iDProduct = bill->GetListProduct()[optionProduct]->GetiDProduct();
					int numberProduct = bill->CheckiDProduct(iDProduct, listProduct);
					listProduct[numberProduct]->SetAmount(listProduct[numberProduct]->GetAmount() + bill->GetListProduct()[optionProduct]->GetAmount());
					bill->SetTotalPayment(bill->GetTotalPayment() - bill->GetListProduct()[optionProduct]->GetPrice() * bill->GetListProduct()[optionProduct]->GetAmount());
					bill->SetVAT(bill->GetVAT() - bill->GetListProduct()[optionProduct]->GetPrice() * bill->GetListProduct()[optionProduct]->GetAmount() / 20);
					bill->GetListProduct()[optionProduct]->SetiDProduct(listProduct[numberProduct]->GetiDProduct());
					bill->GetListProduct()[optionProduct]->SetName(listProduct[numberProduct]->GetName());
				nhapsoluongsp:;
					bx->gotoxy(bx->whereX() + 51, bx->whereY());
					cout << "Nhap so luong: ";
					cin >> tempi;
					if (tempi == 0) {
						bx->gotoxy(bx->whereX() + 48, bx->whereY());
						bx->TextColorDarkBlue();
						cout << "So luong khong dung." << endl;
						bx->TextColorDarkWhite();
						goto nhapsoluongsp;
					}
					if (listProduct[numberProduct]->GetAmount() >= tempi) {
						bill->GetListProduct()[optionProduct]->SetAmount(tempi);
						listProduct[numberProduct]->SetAmount(listProduct[numberProduct]->GetAmount() - tempi);
						bill->GetListProduct()[optionProduct]->SetPrice(listProduct[numberProduct]->GetPrice());
						bill->SetTotalPayment(bill->GetTotalPayment() + bill->GetListProduct()[optionProduct]->GetPrice() * tempi);
						bill->SetVAT(bill->GetVAT() + bill->GetListProduct()[optionProduct]->GetPrice() * tempi / 20);
						checkChange = true;
					}
					else {
						bx->gotoxy(bx->whereX() + 49, bx->whereY());
						bx->TextColorDarkBlue();
						cout << "So luong khong du." << endl;
						bx->TextColorDarkWhite();
						goto nhapsoluongsp;
					}
					cin.ignore();
					system("cls");
					return;
				}
			nhapidsp:;
				bx->gotoxy(bx->whereX() + 51, bx->whereY());
				bx->TextColorDarkBlue();
				cout << "Khong co san pham nay." << endl;
				bx->TextColorDarkWhite();
			} while (checksp);
		}
	}
}

void BillManagement::EraseBill() {
	string a;
	int option = 1;
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap ID hoa don can xoa: ";
	getline(cin, a);
	for (int i = 0; i < listBill.size(); i++) {
		if (listBill[i]->GetiDBill() == a) {
			string title = "=== XOA HOA DON CO ID " + listBill[i]->GetiDBill() + "? ===";

			vector<string> listOption;
			listOption.push_back("Co");
			listOption.push_back("Quay lai");
			option = bx->SelectOption(title, listOption, option);
			if (option == listOption.size()) 
				return;

		Xoa:;
			listBill.erase(listBill.begin() + i);
			bx->gotoxy(bx->whereX() + 45, bx->whereY() + 5);
			cout << "Da xoa hoa don co iD: " << a << endl;
			checkChange = true;
			return;
		}
	}
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Khong co hoa don co ID nay" << endl;
}

void BillManagement::ExitBillManagement() {
	int option = 1;
	string title = "=== CO LUU THAY DOI KHONG? ===";

	vector<string> listOption;

	while (true) {
		listOption.push_back("Co");
		listOption.push_back("Khong");
		option = bx->SelectOption(title, listOption, option);
		if (option == listOption.size() - 1) 
			WriteFile();
		listOption.clear();
		listBill.clear();
		listEmployee.clear();
		listProduct.clear();
		break;
	}
}

void BillManagement::ReadFile() {
	fileProduct.open("PRODUCT.TXT", ios::in);
	fileEmployee.open("EMPLOYEE.TXT", ios::in);
	fileBill.open("BILL.TXT", ios::in);
	int size;
	string temp;
	int tempi;

	if (!fileProduct.fail()) {
		fileProduct >> size;
		getline(fileProduct, temp);
		Product* product = new Product[size];
		for (int i = 0; i < size; i++) {
			getline(fileProduct, temp, ','); product[i].SetiDProduct(temp);
			getline(fileProduct, temp, ','); product[i].SetName(temp);
			fileProduct >> tempi; product[i].SetPrice(tempi);
			getline(fileProduct, temp, ',');
			fileProduct >> tempi; product[i].SetAmount(tempi);
			getline(fileProduct, temp, ',');
			getline(fileProduct, temp); product[i].SetLatestImportDate(temp);
			listProduct.push_back(&product[i]);
		}
	}
	if (!fileEmployee.fail()) {
		fileEmployee >> size;
		getline(fileEmployee, temp);
		Employee* employee = new Employee[size];
		for (int i = 0; i < size; i++) {
			getline(fileEmployee, temp, ','); employee[i].SetiDEmployee(temp);
			getline(fileEmployee, temp, ','); employee[i].SetName(temp);
			getline(fileEmployee, temp, ','); employee[i].SetGender(temp);
			getline(fileEmployee, temp, ','); employee[i].SetAddress(temp);
			getline(fileEmployee, temp, ','); employee[i].SetPhoneNumber(temp);
			getline(fileEmployee, temp); employee[i].SetBirthday(temp);
			listEmployee.push_back(&employee[i]);
		}
	}
	if (!fileBill.fail()) {
		fileBill >> size;
		getline(fileBill, temp);
		Bill* bill = new Bill[size];
		for (int i = 0; i < size; i++) {
			getline(fileBill, temp, ','); bill[i].SetiDBill(temp);
			getline(fileBill, temp, ',');	bill[i].SetiDEmployee(temp);
			getline(fileBill, temp, ','); bill[i].SetName(temp);
			getline(fileBill, temp, ','); bill[i].SetCreationDate(temp);
			getline(fileBill, temp, ','); bill[i].SetCreationTime(temp);
			fileBill >> tempi; bill[i].SetVAT(tempi);
			getline(fileBill, temp, ',');
			fileBill >> tempi; bill[i].SetTotalPayment(tempi);
			getline(fileBill, temp, ',');
			int nsp;
			fileBill >> nsp;
			getline(fileBill, temp);
			vector <Product*> selectProductList;
			for (int j = 0; j < nsp; j++) {
				Product* product = new Product;
				getline(fileBill, temp, ','); product->SetiDProduct(temp);
				getline(fileBill, temp, ','); product->SetName(temp);
				fileBill >> tempi; product->SetAmount(tempi);
				getline(fileBill, temp, ',');
				fileBill >> tempi; product->SetPrice(tempi);
				getline(fileBill, temp);
				selectProductList.push_back(product);
			}
			bill[i].SetListProduct(selectProductList);
			listBill.push_back(&bill[i]);
		}
	}
	fileProduct.close();
	fileEmployee.close();
	fileBill.close();
}

void BillManagement::WriteFile() {
	fileProduct.open("PRODUCT.TXT", ios::out);
	fileBill.open("BILL.TXT", ios::out);
	int size = listProduct.size();
	fileProduct << size << endl;
	for (int i = 0; i < size; i++) {
		fileProduct << listProduct[i]->GetiDProduct() + "," << listProduct[i]->GetName() + "," << listProduct[i]->GetPrice() << ","
			<< listProduct[i]->GetAmount() << "," << listProduct[i]->GetLatestImportDate() << endl;
	}
	size = listBill.size();
	fileBill << size << endl;
	for (int i = 0; i < size; i++) {
		fileBill << listBill[i]->GetiDBill() + "," << listBill[i]->GetiDEmployee() + "," << listBill[i]->GetName() + ","
			<< listBill[i]->GetCreationDate() + "," << listBill[i]->GetCreationTime() + "," << listBill[i]->GetVAT() << ","
			<< listBill[i]->GetTotalPayment() << ",";
		int m = listBill[i]->GetListProduct().size();
		fileBill << m << endl;
		for (int j = 0; j < m; j++) {
			fileBill << listBill[i]->GetListProduct()[j]->GetiDProduct() + "," << listBill[i]->GetListProduct()[j]->GetName() + ","
				<< listBill[i]->GetListProduct()[j]->GetAmount() << "," << listBill[i]->GetListProduct()[j]->GetPrice() << endl;
		}
	}

	fileProduct.close();
	fileBill.close();
}

