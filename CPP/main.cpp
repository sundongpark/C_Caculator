#include <iostream>
#include <string>
#include <stack>
#include "StringCalculator.h"

int main()
{
	std::string str;
	std::stack<float> num;
	std::stack<oper> op;

	while(true)	// ������ �Է� �ް� ���ڿ� ������ ó��
	{
		std::cout << "���� �Է� (q �Է½� �ߴ�) : ";
		std::cin >> str;

		if (str.at(0) == 'q')
			break;
		else
			StringIn(num, op, str);

		std::cout << "��: " << num.top() << std::endl;	//��� ���
	}

	return 0;
}
