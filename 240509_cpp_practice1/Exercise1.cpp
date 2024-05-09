#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //공백 split용

#include "Login_Func.h"

using namespace std;

int ConfirmPW(string input);
void NoticeLogin(bool nameCheck, bool pwCheck);
int CofirmTel(string input);

int main()
{
	string line, name, pw, tel, name_input, pw_input, tel_input;
	bool nameCheck, pwCheck;
	vector <string> memberVector;

	cout << "* 로그인 성공 시 전화번호 저장 *" << endl
		<< "( quit 입력 시 종료 )" << endl;

	ifstream member_file("member.txt");

	while (getline(member_file, line))
	{
		memberVector.push_back(line);
	}

	member_file.close();

	while (1)
	{
		nameCheck = false;
		pwCheck = false;

		cout << endl << "이름을 입력하세요: ";
		cin >> name_input;

		if (name_input == "quit")
		{
			return 0;
		}

		cout << "비번을 입력하세요: ";
		cin >> pw_input;

		while (ConfirmPW(pw_input) > 0)
		{
			cout << endl << "- 패스워드는 대소문자, 특수문자, 숫자를 모두 포함하고 6~17자리여야 합니다." << endl
				<< endl << "[재입력]" << endl
				<< "비번을 입력하세요: ";
			cin >> pw_input;
		}


		for (string line : memberVector)
		{
			stringstream ss(line);
			ss >> name >> pw;

			//cout << "확인용: " << name << " " << pw << endl;

			if (name_input == name)
			{
				nameCheck = true;

				if (pw_input == pw)
				{
					pwCheck = true;
					break;
				}
			}
		}

		NoticeLogin(nameCheck, pwCheck);

		// 로그인 성공 시
		if (nameCheck == true && pwCheck == true)
		{
			cout << endl << "전화번호를 입력해주세요: ";
			cin >> tel_input;

			while (CofirmTel(tel_input) > 0)
			{
				cout << endl << "[재입력]" << endl
					<< "전화번호를 입력해주세요: ";
				cin >> tel_input;
			}

			ifstream read_file("member_tel.txt");

			int type = 0;
			bool breakCheck = false;
			vector <string> telVector;

			if (read_file.is_open())
			{
				while (getline(read_file, line))
				{
					telVector.push_back(line);

					if (breakCheck == false)
					{
						stringstream ss(line);
						ss >> name >> tel;

						if (name == name_input) // member_tel.txt 파일 내 로그인 한 사용자 이름 존재
						{
							// 전화 번호 값 변경
							type = 1;
							breakCheck = true;
						}
						else // 사용자 이름 존재 x
						{
							// 사용자 이름 전화번호 추가
							type = 2;
						}
					}
				}
			}
			else
			{
				type = 2;
			}

			read_file.close();

			ofstream tel_file("member_tel.txt");

			switch (type)
			{
			case 1:
				for (int i = 0; i < telVector.size(); i++)
				{
					stringstream ss(telVector[i]);
					ss >> name >> tel;

					if (name == name_input) // 같은 줄
					{
						telVector[i] = name + " " + tel_input; // 전화번호만 수정
					}
				}
				break;
			case 2:
				telVector.push_back(name_input + " " + tel_input);
				break;
			}

			for (string line : telVector) // 파일에 입력
			{
				//cout << line << endl;
				tel_file << line << endl;
			}

			tel_file.close();
		}
	}
}

int ConfirmPW(string input)
{
	if (input.size() < 6 || input.size() > 17)
	{
		//cout << endl << "- 비밀번호는 6~17 자리입니다:)" << endl;
		return 1;
	}
	else if (checkPwCombi(input) == false)
	{
		//cout << "확인: " << checkPwCombi(input) << endl;
		return 2;
	}

	return 0;
}

void NoticeLogin(bool nameCheck, bool pwCheck)
{
	if (nameCheck == true && pwCheck == true)
	{
		cout << endl << "로그인 성공" << endl;
	}
	else
	{
		cout << endl << "로그인 실패" << endl;

		if (nameCheck == false)
		{
			cout << endl << "- 존재하지 않는 사용자 이름입니다:)" << endl;
		}
		else if (pwCheck == false)
		{
			cout << endl << "- 비밀번호가 일치하지 않습니다:)" << endl;
		}
	}
}

int CofirmTel(string input)
{
	vector <string> telNum;
	string num;
	stringstream ss(input);

	while (getline(ss, num, '-'))
	{
		telNum.push_back(num);
	}

	if (telNum.size() != 3)
	{
		return 1; // 전화번호 형식이 아님 xxx-xxxx-xxxx
	}
	else if (telNum[0] != "010")
	{
		return 2; // 010으로 시작하지 않음
	}
	else if (telNum[1].size() != 4 || telNum[2].size() != 4)
	{
		return 3; // 전화번호 자리수가 잘못됨
	}
	return 0;
}