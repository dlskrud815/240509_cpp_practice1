#pragma once
#include <iostream>
#include <vector>

using namespace std;

class BankService
{
private:
	string branchId, address;
	int customerNum=0, activeAccountNum=0;
	vector <string> customerId; //해당 지점에서 관리 중인 고객 아이디 목록

public:
	void OpenNewAccount();
	void ManageCustomerInfo();
	void ManageBranchInfo();
	void CheckCustomerInfo();
	void CheckBranchInfo();
};