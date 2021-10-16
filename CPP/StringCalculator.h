#pragma once
#include <string>
#include <stack>

struct oper	//연산자와 우선순위
{
	char o;
	int p;
};

void ResOut(std::stack<float>& num, std::stack<oper>& op);
//num stack의 top의 두 숫자를 연산하여 num에 push
void StringIn(std::stack<float>& num, std::stack<oper>& op, std::string& str);
//입력 받은 문자열을 숫자는 num에 push, 연산자는 op에 push하여 결과를 얻는다