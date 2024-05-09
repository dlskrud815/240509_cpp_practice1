#include <iostream>

#include "CustomerService.h"
#include "BankService.h"


int main()
{
	CustomerService customerService;
	BankService bankService;

	customerService.CheckAccount();
	customerService.TransferAccount();

	bankService.CheckBranchInfo();
	bankService.CheckCustomerInfo();
	bankService.ManageBranchInfo();
	bankService.ManageCustomerInfo();
	bankService.OpenNewAccount();
}