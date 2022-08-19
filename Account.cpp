#include "Account.h"

void Account::SetUserName(string data) {
    user = data;
}

string Account::GetUserName() {
    return user;
}

void Account::SetPassWord(string data) {
    passWord = data;
}

string Account::GetPassWord() {
    return passWord;
}