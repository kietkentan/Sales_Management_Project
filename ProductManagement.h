#pragma once
#include "Product.h"
#include <fstream>
#include "Box_Draw.h"

class ProductManagement {
private:
	fstream filein;
	Box_Draw* bx = new Box_Draw;
	vector <Product*> listProduct;

public:
	ProductManagement();
	void DisplayProduct();
	void SearchProduct();
	void EditInfoProduct();
	void OptionEditInfoProduct(int option, Product* product);
	void EraseProduct();
	void ExitProductManagement();
	void ReadFile();
	void WriteFile();
};