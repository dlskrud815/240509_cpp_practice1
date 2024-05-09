#pragma once
#include <iostream>
#include <vector>

using namespace std;

class BankService
{
private:
	string branchId, address;
	int customerNum=0, activeAccountNum=0;
	vector <string> v_customerId; //�ش� �������� ���� ���� �� ���̵� ���

public:
	void OpenNewAccount();
	void ManageCustomerInfo();
	void ManageBranchInfo();
	void CheckCustomerInfo();
	void CheckBranchInfo();
};