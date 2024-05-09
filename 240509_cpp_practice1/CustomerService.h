#pragma once
#include <iostream>

using namespace std;

class CustomerService
{
private:
	string id, name, accountNum, phoneNum, mngBranchId;

public:
	void CheckAccount();
	void TransferAccount();
};