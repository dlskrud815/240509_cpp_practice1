#include <iostream>

#include "CustomerService.h"
#include "BankService.h"


int main()
{
	//고객단에서 사용 가능한 서비스와 그에 필요한 필드 정보
	CustomerService customerService;
	//은행단에서 사용 가능한 서비스와 그에 따라 접근 가능한 필드 정보
	BankService bankService;

	customerService.CheckAccount();
	customerService.TransferAccount();

	bankService.CheckBranchInfo();
	bankService.CheckCustomerInfo();
	bankService.ManageBranchInfo();
	bankService.ManageCustomerInfo();
	bankService.OpenNewAccount();
}