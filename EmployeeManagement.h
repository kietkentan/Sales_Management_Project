#pragma once
#include "Employee.h"
#include <fstream>
#include "Box_Draw.h"

class EmployeeManagement {
private:
	Box_Draw* bx = new Box_Draw;
	vector <Employee*> listEmployee;

public:
	EmployeeManagement();
	EmployeeManagement(string employee);
	void DisplayEmployee();
	void SearchEmployee();
	void EditInfoEmployee();
	void OptionEditInfoEmployee(int option, Employee* employee);
	void EraseEmployee();
	void ExitEmployeeManagement();
	void ReadFile();
	void WriteFile();
};