#include "StringCalculator.h"

void ResOut(std::stack<float>& num, std::stack<oper>& op)
//num stack�� top�� �� ���ڸ� �����Ͽ� num�� push
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
//�Է� ���� ���ڿ��� ���ڴ� num�� push, �����ڴ� op�� push�Ͽ� ����� ��´�
{
	while (!num.empty())
		num.pop();
	while (!op.empty())
		op.pop();

	for (int i = 0; i < str.length(); i++)
	{
		if (str.at(i) >= '0' && str.at(i) <= '9')   //���������� ���ڸ� �������·� num�� push
		{
			int j, tmp = i;	//���� ����
			for (j = 0; (str[i] >= '0' && str[i] <= '9') || str[i] == '.'; j++, i++);
			//���� ��
			num.push(stof(str.substr(tmp, j)));	//���ڿ��� �Ǽ��� �ٲ� num�� push
		}

		switch (str[i])   //������ ó��
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
	while (!op.empty())	//�����ڰ� �� ������ ����
		ResOut(num, op);
}
