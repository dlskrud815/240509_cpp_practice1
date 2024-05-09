#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> //���� split��

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

	cout << "* �α��� ���� �� ��ȭ��ȣ ���� *" << endl
		<< "( quit �Է� �� ���� )" << endl;

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

		cout << endl << "�̸��� �Է��ϼ���: ";
		cin >> name_input;

		if (name_input == "quit")
		{
			return 0;
		}

		cout << "����� �Է��ϼ���: ";
		cin >> pw_input;

		while (ConfirmPW(pw_input) > 0)
		{
			cout << endl << "- �н������ ��ҹ���, Ư������, ���ڸ� ��� �����ϰ� 6~17�ڸ����� �մϴ�." << endl
				<< endl << "[���Է�]" << endl
				<< "����� �Է��ϼ���: ";
			cin >> pw_input;
		}


		for (string line : memberVector)
		{
			stringstream ss(line);
			ss >> name >> pw;

			//cout << "Ȯ�ο�: " << name << " " << pw << endl;

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

		// �α��� ���� ��
		if (nameCheck == true && pwCheck == true)
		{
			cout << endl << "��ȭ��ȣ�� �Է����ּ���: ";
			cin >> tel_input;

			while (CofirmTel(tel_input) > 0)
			{
				cout << endl << "[���Է�]" << endl
					<< "��ȭ��ȣ�� �Է����ּ���: ";
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

						if (name == name_input) // member_tel.txt ���� �� �α��� �� ����� �̸� ����
						{
							// ��ȭ ��ȣ �� ����
							type = 1;
							breakCheck = true;
						}
						else // ����� �̸� ���� x
						{
							// ����� �̸� ��ȭ��ȣ �߰�
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

					if (name == name_input) // ���� ��
					{
						telVector[i] = name + " " + tel_input; // ��ȭ��ȣ�� ����
					}
				}
				break;
			case 2:
				telVector.push_back(name_input + " " + tel_input);
				break;
			}

			for (string line : telVector) // ���Ͽ� �Է�
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
		//cout << endl << "- ��й�ȣ�� 6~17 �ڸ��Դϴ�:)" << endl;
		return 1;
	}
	else if (checkPwCombi(input) == false)
	{
		//cout << "Ȯ��: " << checkPwCombi(input) << endl;
		return 2;
	}

	return 0;
}

void NoticeLogin(bool nameCheck, bool pwCheck)
{
	if (nameCheck == true && pwCheck == true)
	{
		cout << endl << "�α��� ����" << endl;
	}
	else
	{
		cout << endl << "�α��� ����" << endl;

		if (nameCheck == false)
		{
			cout << endl << "- �������� �ʴ� ����� �̸��Դϴ�:)" << endl;
		}
		else if (pwCheck == false)
		{
			cout << endl << "- ��й�ȣ�� ��ġ���� �ʽ��ϴ�:)" << endl;
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
		return 1; // ��ȭ��ȣ ������ �ƴ� xxx-xxxx-xxxx
	}
	else if (telNum[0] != "010")
	{
		return 2; // 010���� �������� ����
	}
	else if (telNum[1].size() != 4 || telNum[2].size() != 4)
	{
		return 3; // ��ȭ��ȣ �ڸ����� �߸���
	}
	return 0;
}