#include <iostream>
using namespace std;

class Account {
private:
	string user;
	string passWord;

public:
	void SetUserName(string data);
	string GetUserName();
	void SetPassWord(string data);
	string GetPassWord();
};