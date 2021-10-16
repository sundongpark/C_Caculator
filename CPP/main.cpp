#include <iostream>
#include <string>
#include <stack>
#include "StringCalculator.h"

int main()
{
	std::string str;
	std::stack<float> num;
	std::stack<oper> op;

	while(true)	// 수식을 입력 받고 숫자와 연산자 처리
	{
		std::cout << "수식 입력 (q 입력시 중단) : ";
		std::cin >> str;

		if (str.at(0) == 'q')
			break;
		else
			StringIn(num, op, str);

		std::cout << "답: " << num.top() << std::endl;	//결과 출력
	}

	return 0;
}
