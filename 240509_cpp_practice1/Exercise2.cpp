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

	cout << "가로, 세로 길이를 입력하세요: ";
	cin >> rec.width >> rec.height;

	cout << "넓이는.. " << rec.width * rec.height << endl;

	return 0;
}