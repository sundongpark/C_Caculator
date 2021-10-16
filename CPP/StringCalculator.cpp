#include "StringCalculator.h"

void ResOut(std::stack<float>& num, std::stack<oper>& op)
//num stack의 top의 두 숫자를 연산하여 num에 push
{
	float num1, num2, result;
	char oper;

	num2 = num.top();
	num.pop();
	num1 = num.top();
	num.pop();

	oper = op.top().o;
	op.pop();

	if (oper == '+')
		result = num1 + num2;
	else if (oper == '-')
		result = num1 - num2;
	else if (oper == '*')
		result = num1 * num2;
	else if (oper == '/')
		result = num1 / num2;

	num.push(result);
}
void StringIn(std::stack<float>& num, std::stack<oper>& op, std::string& str)
//입력 받은 문자열을 숫자는 num에 push, 연산자는 op에 push하여 결과를 얻는다
{
	while (!num.empty())
		num.pop();
	while (!op.empty())
		op.pop();

	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) >= '0' && str.at(i) <= '9')   //문자형태의 숫자를 숫자형태로 num에 push
		{
			int j, tmp = i;	//숫자 시작
			for (j = 0; (str[i] >= '0' && str[i] <= '9') || str[i] == '.'; j++, i++);
			//숫자 끝
			num.push(stof(str.substr(tmp, j)));	//문자열을 실수로 바꿔 num에 push
		}

		switch (str[i])   //연산자 처리
		{
			int prior;
		case '+':
		case '-':
			prior = 2;
			while (!op.empty() && prior >= op.top().p)
				ResOut(num, op);
			op.push({ str.at(i), prior });
			break;
		case '*':
		case '/':
			prior = 1;
			while (!op.empty() && prior >= op.top().p)
				ResOut(num, op);
			op.push({ str.at(i), prior });
			break;

		case '{':
		case '(':
			op.push({ '(' , 3 });
			break;
		case '}':
		case ')':
			while (op.top().o != '(')
				ResOut(num, op);
			op.pop();

			break;
		}
	}
	while (!op.empty())	//연산자가 빌 때까지 연산
		ResOut(num, op);
}
