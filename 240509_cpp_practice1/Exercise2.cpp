#include <iostream>

using namespace std;

struct Rectangle
{
	float width = 0;
	float height = 0;
};

int main()
{
	Rectangle rec;

	cout << "����, ���� ���̸� �Է��ϼ���: ";
	cin >> rec.width >> rec.height;

	cout << "���̴�.. " << rec.width * rec.height << endl;

	return 0;
}