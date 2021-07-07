/*
 *
 * 1. 문자형태의 숫자를 숫자형태로 저장
 * 2. 사칙연산 처리
 * 3. 괄호 처리
 * 3-1. 괄호 안의 괄호
 * 4. 실수 숫자 처리(소수점 입력)
 *
 * 테스트
3+2*4+5/2-4
(3+5)*4-(2+3)/2
7+(5+6*(7+8)/10)
7*(5+6*(7+8)/10)
7.2*(5.3+6.7*(7.5+8.1)/10.3)
(3.2+(82.4+61.2)/26.5)*(3+9)-2
(3.2+(3+82.4+61.2)/26.5)+3

* 잘못된 수식
(3.2+(3+82.4+61.2)/2
2+3+4+
7*(5+6*(7

 * 
 */

#include <stdio.h>
#include <math.h>

#define LEN 256

double ResOut(double num[], char oper[], int l);
int FindLen(char oper[], int *b);

int main()
{
	char str[LEN];
	double num[LEN];
	char oper[LEN];
	int len;
	int part1;
	int part2;
	int i, j, k, l,  digit, tmp;

	while (1)
	{
		// 수식을 입력 받고 숫자와 연산자 처리

		while (1)
		{
			printf("수식 입력 (q 입력시 중단) : ");
			scanf_s("%s", str, sizeof(str));

			if (str[0] == 'q')
				return 0;

			for (len = 0; str[len] != '\0'; len++)
				;

			for (i = 0; i < LEN; i++)
				num[i] = 0;

			for (i = 0, k = 0, l = 0, part1 = 0, part2 = 0; i < len; i++)
			{
				if (str[i] >= '0' && str[i] <= '9')   //문자형태의 숫자를 처리해 숫자형태로 num[k]에 저장
				{
					tmp = i;
					for (j = 0; str[i] >= '0' && str[i] <= '9'; j++, i++) //
						;
					digit = j - 1;
					for (i = tmp, j = 0; digit >= j; j++, i++)
						num[k] += pow(10, digit - j) * (int)(str[i] - '0');
					k++;
				}

				if (str[i] == '.')
				{
					k--;
					i++;
					for (j = 1; str[i] >= '0' && str[i] <= '9'; i++, j++)
						num[k] += pow(0.1, j) * (int)(str[i] - '0');
					k++;
				}

				switch (str[i])   //연산자 처리
				{
				case '+':
					oper[l] = '+';
					l++;
					break;
				case '-':
					oper[l] = '-';
					l++;
					break;
				case '*':
					oper[l] = '*';
					l++;
					break;
				case '/':
					oper[l] = '/';
					l++;
					break;
				case '{':
				case '(':
					oper[l] = '(';
					l++;
					part1++;
					break;
				case '}':
				case ')':
					oper[l] = ')';
					l++;
					part2++;
					break;
				}

				if (!((str[i] >= '0' && str[i] <= '9') || str[i] == '(' || str[i] == '.' || str[i] == '{' || str[i] == ')' || str[i] == '}' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/' || str[i] == '\0'))
				{
					printf("다른 기호가 들어갔습니다. 다시 입력하세요.\n");
					break;
				}
			}

			if ((k - 1) == (l - part1 - part2) && part1 == part2)	//숫자와 연산기호 개수 확인, 괄호 개수 확인
				break;
			else
				printf("잘못된 수식입니다. 다시 입력하세요.\n");

		}

		printf("답 : %lf\n", ResOut(num, oper, l));			//결과 출력
	}

	return 0;
}


double ResOut(double num[], char oper[], int l)		 //num, oper, l
{
	double res[LEN];
	double result = 0;
	int i, j, k, a, b;	//i는 연산자의 순서, a는 숫자의 순서, k는 괄호 안의 길이, b는 괄호의 개수

	res[0] = num[0];

		for (i = 0, j = 0, a = 0, k = 0; i < l ; i++, j++, a++)   //숫자와 연산자를 묶어서 덧셈만으로 결과 구하도록 처리
		{

			if (oper[i] == '(')
			{
				i++;
				k = FindLen(oper + i, &b);

				res[j] = ResOut(num + a, oper + i, k);
				a += k - b;
				i += k;


			}
			
			for (; oper[i] == '*' || oper[i] == '/'; i++, a++)   //연속된 곱셈 나눗셈 묶기
			{

				if (oper[i] == '*')
				{
					if (oper[i + 1] != '(')
						res[j] *= num[a + 1];
					else if (oper[i + 1] == '(')
					{
						i+=2;
						k = FindLen(oper + i, &b);
						res[j] *= ResOut(num + a + 1, oper + i, k);
						a += k - b + 1;
						i += k;

					}
				}
				else if (oper[i] == '/')
				{
					if (oper[i + 1] != '(')
						res[j] /= num[a + 1];
					else if (oper[i + 1] == '(')
					{
						i+=2;
						k = FindLen(oper + i, &b);
						res[j] /= ResOut(num + a + 1, oper + i, k);
						a += k - b + 1;
						i += k;

					}
				}
			}

			if (oper[i] == '+')
			{
				if (oper[i + 1] != '(')
					res[++j] = num[a + 1];
				else if (oper[i + 1] == '(')
				{
					i+=2;
					k = FindLen(oper + i, &b);
					res[++j] = ResOut(num + a + 1, oper + i, k);
					a += k - b + 1;
					i += k;

				}
			}
			else if (oper[i] == '-')
			{
				if (oper[i + 1] != '(')
					res[++j] = -num[a + 1];
				else if (oper[i + 1] == '(')
				{
					i+=2;
					k = FindLen(oper + i, &b);
					res[++j] = -ResOut(num + a + 1, oper + i, k);
					a += k - b + 1;
					i += k;

				}
			}

			j--;
		}

		for (i = 0; i < j + 1; i++)
			result += res[i];
	return result;
}

int FindLen(char oper[], int* b)
{
	int k, i, j;

	for (i = 0, j = 0, k = 0; i != j - 1; k++)	//괄호 안의 길이 구하기
	{
		if (oper[k] == '(')
			i++;
		else if (oper[k]==')')
			j++;
	}

	*b = i + j;

	return k-1;
}
