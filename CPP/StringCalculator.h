#pragma once
#include <string>
#include <stack>

struct oper	//�����ڿ� �켱����
{
	char o;
	int p;
};

void ResOut(std::stack<float>& num, std::stack<oper>& op);
//num stack�� top�� �� ���ڸ� �����Ͽ� num�� push
void StringIn(std::stack<float>& num, std::stack<oper>& op, std::string& str);
//�Է� ���� ���ڿ��� ���ڴ� num�� push, �����ڴ� op�� push�Ͽ� ����� ��´�