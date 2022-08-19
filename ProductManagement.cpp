#include "ProductManagement.h"

using namespace std;
static bool checkChange = false;

ProductManagement::ProductManagement() {
	int option = 1;
	string title = "=== QUAN LI SAN PHAM ===";

	vector<string> listOption;
	listOption.push_back("1. Nhap thong tin san pham moi");
	listOption.push_back("2. Xem tat ca san pham");
	listOption.push_back("3. Tim kiem san pham");
	listOption.push_back("4. Chinh sua thong tin san pham");
	listOption.push_back("5. Xoa san pham qua ID");
	listOption.push_back("6. Quay lai");
	ReadFile();

	while (true) {
		option = bx->SelectOption(title, listOption, option);
		Product* tempProduct = new Product;
		switch (option) {
		case 1:
			tempProduct->InPut();
			listProduct.push_back(tempProduct);
			listProduct.back()->Display();
			system("pause");
			system("cls");
			break;
		case 2:
			DisplayProduct();
			system("pause");
			system("cls");
			break;
		case 3:
			SearchProduct();
			system("pause");
			system("cls");
			break;
		case 4:
			EditInfoProduct();
			system("cls");
			break;
		case 5:
			EraseProduct();
			system("pause");
			system("cls");
			break;
		default:
			if (checkChange) {
				checkChange = false;
				ExitProductManagement();
			}
			return;
		}
		delete tempProduct;
	}
}

void ProductManagement::DisplayProduct() {
	string title = "=== DANH SACH SAN PHAM ===";
	bx->gotoxy(44 + (40 - title.size()) / 2, 5);
	cout << title << endl;
	string nvx;
	int totalPrice = 0;

	for (int i = 0; i < listProduct.size(); i++) {
		bx->TextColorDarkBlue();
		if (i != 0) {
			bx->gotoxy(bx->whereX() + 45, bx->whereY());
			cout << "------------------------------------- " << endl << endl;
		}
		bx->gotoxy(56, bx->whereY());
		cout << "San pham thu " << i + 1 << ":" << endl;
		bx->TextColorDarkWhite();
		listProduct[i]->Display();
		totalPrice += listProduct[i]->TotalPrice();
	}
	bx->gotoxy(bx->whereX() + 42, bx->whereY());
	cout << "Tong gia tat ca san pham trong kho: " << totalPrice << endl;
}

void ProductManagement::SearchProduct()
{
	string title = "=== TIM KIEM SAN PHAM ===";
	string iD;
	bx->gotoxy(44 + (40 - title.size()) / 2, 5);
	cout << title << endl;
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap ID can tim: ";
	getline(cin, iD);

	const int NUMPRODUCT = listProduct.size();
	int validID = 0;
	for (int i = 0; i < NUMPRODUCT; i++)
		if (listProduct[i]->GetiDProduct().find(iD) < 7) {
			bx->TextColorDarkBlue();
			bx->gotoxy(56, bx->whereY());
			cout << "San pham thu " << ++validID << ":" << endl;
			bx->TextColorDarkWhite();
			listProduct[i]->Display();
			cout << endl;
		}
	bx->gotoxy(bx->whereX() + 44, bx->whereY());
	if (validID == 0) cout << "Khong co tim kiem phu hop" << endl;
}

void ProductManagement::EditInfoProduct() {
	string iD;
	bx->gotoxy(bx->whereX() + 45, 5);
	cout << "Nhap ID nhan vien can chinh sua: ";
	getline(cin, iD);
	for (int i = 0; i < listProduct.size(); i++) {
		if (listProduct[i]->GetiDProduct() == iD) {
			int option = 1;
			string title = "=== CHINH SUA THONG TIN SAN PHAM CO ID " + listProduct[i]->GetiDProduct() + " ===";

			vector<string> listOption;
			while (true) {
				listOption.push_back("Ten: " + listProduct[i]->GetName());
				listOption.push_back("Gia: " + to_string(listProduct[i]->GetPrice()));
				listOption.push_back("So luong: " + to_string(listProduct[i]->GetAmount()));
				listOption.push_back("Ngay nhap: " + listProduct[i]->GetLatestImportDate());
				listOption.push_back("Quay lai");
				option = bx->SelectOption(title, listOption, option);
				if (option == listOption.size()) 
					return;
				OptionEditInfoProduct(option, listProduct[i]);
				system("cls");
				listOption.clear();
			}
		}
	}
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Khong co san pham co ID nay." << endl;
	system("pause");
}

void ProductManagement::OptionEditInfoProduct(int option, Product* product) {
	string temp;
	int tempi;
	bx->gotoxy(0, 6);

	switch (option) {
	case 1:
		bx->gotoxy(bx->whereX() + 51, bx->whereY());
		cout << "Nhap ten: ";
		getline(cin, temp);
		if (temp == "\0") 
			return;
		product->SetName(temp);
		checkChange = true;
		break;
	case 2:
		do {
			bx->gotoxy(bx->whereX() + 51, bx->whereY());
			cout << "Nhap gia: ";
			cin >> tempi;
			product->SetPrice(tempi);
			if (product->CheckPrice()) {
				checkChange = true;
				return;
			}
			else {
				bx->gotoxy(bx->whereX() + 37, bx->whereY());
				bx->TextColorDarkBlue();
				cout << "Gia phai la so duong." << endl;
				bx->TextColorDarkWhite();
			}
		} while (true);
		break;
	case 3:
		do {
			bx->gotoxy(bx->whereX() + 51, bx->whereY());
			cout << "Nhap so luong: ";
			cin >> tempi;
			product->SetAmount(tempi);
			if (product->CheckAmount()) {
				checkChange = true;
				break;
			}
			else {
				bx->gotoxy(bx->whereX() + 35, bx->whereY());
				bx->TextColorDarkBlue();
				cout << "So luong phai la so duong." << endl;
				bx->TextColorDarkWhite();
			}
		} while (true);
		break;
	case 4:
		bx->gotoxy(bx->whereX() + 51, bx->whereY());
		cout << "Nhap ngay nhap hang: ";
		if (temp == "\0") 
			return;
		getline(cin, temp);
		product->SetLatestImportDate(temp);
		checkChange = true;
		break;
	default:
		break;
	}
}

void ProductManagement::EraseProduct() {
	string iD;
	int option = 1;
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Nhap ID san pham can xoa: ";
	getline(cin, iD);
	for (int i = 0; i < listProduct.size(); i++) {
		if (listProduct[i]->GetiDProduct() == iD) {
			string title = "=== XOA SAN PHAM CO ID " + listProduct[i]->GetiDProduct() + "? ===";

			vector<string> listOption;
			listOption.push_back("Co");
			listOption.push_back("Quay lai");
			option = bx->SelectOption(title, listOption, option);
			if (option == listOption.size()) 
				return;

			listProduct.erase(listProduct.begin() + i);
			bx->gotoxy(bx->whereX() + 45, bx->whereY() + 5);
			cout << "Da xoa san pham co iD: " << iD << endl;
			checkChange = true;
			return;
		}
	}
	bx->gotoxy(bx->whereX() + 45, bx->whereY());
	cout << "Khong co san pham co ID nay" << endl;
	system("pause");
}

void ProductManagement::ExitProductManagement() {
	int option = 1;
	string title = "=== CO LUU THAY DOI KHONG? ===";

	vector<string> listOption;

	listOption.push_back("Co");
	listOption.push_back("Khong");
	option = bx->SelectOption(title, listOption, option);
	if (option == listOption.size() - 1)
		WriteFile();
	listOption.clear();
	listProduct.clear();
}

void ProductManagement::ReadFile() {
	filein.open("PRODUCT.TXT", ios::in);
	if (!filein.fail()) {
		int size;
		string temp;
		int tempi;

		filein >> size;
		getline(filein, temp);
		Product* product = new Product[size];
		for (int i = 0; i < size; i++) {
			getline(filein, temp, ','); product[i].SetiDProduct(temp);
			getline(filein, temp, ','); product[i].SetName(temp);
			filein >> tempi; product[i].SetPrice(tempi);
			getline(filein, temp, ',');
			filein >> tempi; product[i].SetAmount(tempi);
			getline(filein, temp, ',');
			getline(filein, temp); product[i].SetLatestImportDate(temp);
			listProduct.push_back(&product[i]);
		}
	}
	filein.close();
}

void ProductManagement::WriteFile() {
	filein.open("PRODUCT.TXT", ios::out);
	int size = listProduct.size();
	filein << size << endl;
	for (int i = 0; i < size; i++)
		filein << listProduct[i]->GetiDProduct() + "," << listProduct[i]->GetName() + "," << listProduct[i]->GetPrice() 
		<< "," << listProduct[i]->GetAmount() << "," << listProduct[i]->GetLatestImportDate() << endl;
	filein.close();
}
