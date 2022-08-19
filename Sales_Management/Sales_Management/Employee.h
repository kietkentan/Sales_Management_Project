#pragma once
#include <iostream>
#include "Box_Draw.h"

using namespace std;

class Employee {
private:
	string iD;
	string name;
	string gender;
	string address;
	string phoneNumber;
	string birthday;
	int salary;

	Box_Draw* box = new Box_Draw;

public:
	void InPut();
	void Display();

	Employee();
	~Employee();

	bool CheckID();
	bool CheckName();
	bool CheckPhoneNumber();
	bool CheckGender();

	void SetiDEmployee(string data);
	string GetiDEmployee();
	void SetName(string data);
	string GetName();
	void SetGender(string data);
	string GetGender();
	void SetAddress(string data);
	string GetAddress();
	void SetPhoneNumber(string data);
	string GetPhoneNumber();
	void SetBirthday(string data);
	string GetBirthday();
	void SetSalary(int data);
	int GetSalary();
};