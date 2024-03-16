#pragma once
//#ifndef STACK_H
//#define STACK_H
#define Max_size 10000
#define tra template <typename T>

#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <string>
#include <algorithm>
#include "Stack.h"

using namespace std;

template <typename T>
class Stack
{
private:
	T* line;
	const int max_size = 10000;
	int top;
public:
	Stack();
	Stack(int len);
	Stack(const Stack<T>& s2);
	~Stack();

	bool empty();
	bool full();

	void push(const T& el);
	void pop();
	const T& get();
	int r_top();

	void print_stack();
	void print_stack_as_a_line();

	int bracket();
	Stack<T> postfix_form();
	double calculation(const Stack<T>& st);

	Stack operator = (const Stack<T>& st)
	{
		top = st.top;
		if (st.line)
		{
			top = st.top;
			line = new T[max_size + 1];
			for (int i = 0; i <= top; i++)
			{
				line[i] = st.line[i];
			}
		}
		else line = 0;
		return *this;
	}

	//friend ostream& operator<<(ostream& ofstr, const Stack<T>& b2);
	//friend istream& operator>>(istream& ifstr, Stack<T>& b2);
	//friend bool operator == (T, char);
	// T pop() с возвращением;
	//string stack_to_line(const Stack<T>& s2);
	//Stack(const char* s);
};


tra
Stack<T>::Stack()
{
	//max_size = Max_size;
	top = -1;
	line = new T[max_size];
}

tra
Stack<T>::Stack(int len)
{
	//max_size = Max_size;
	top = -1;
	line = new T[max_size];
}

tra
Stack<T>::Stack(const Stack& s2)
{
	if (s2.line)
	{
		top = s2.top;
		line = new T[max_size + 1];
		for (int i = 0; i <= top; i++)
		{
			line[i] = s2.line[i];
		}
	}
	else line = 0;
}

tra
Stack<T> :: ~Stack()
{
	delete[]line;
}

tra
bool Stack<T>::empty()
{
	return top == -1;
}

tra
bool Stack<T>::full()
{
	return top == max_size - 1;
}

tra
void Stack<T>::push(const T& el)
{
	if (full())
	{
		cout << "Нечего брать из стека\n";
		exit(EXIT_FAILURE);
	}
	line[++top] = el;
}

tra
const T& Stack<T> ::get()
{
	if (empty())
	{
		cout << "Нечего брать из стека\n";
		cout << "Неверно написанный пример \n";
		exit(EXIT_FAILURE);
	}
	else return line[top];
}

tra
void Stack<T>::pop()
{
	if (empty())
	{
		cout << "Нечего вынимать из стека\n";
		exit(EXIT_FAILURE);
	}
	//cout << get() << "\n";
	line[top] = NULL;
	line[top--];
}

tra
int Stack<T> ::r_top()
{
	return top;
}

tra
void Stack<T>::print_stack()
{
	for (int i = top; i >= 0; i--)
	{
		cout << line[i] << endl;
	}
}

tra
void Stack<T>::print_stack_as_a_line()
{
	for (int i = top; i >= 0; i--)
	{
		cout << line[i] << " ";
	}
	cout << endl;
}

tra
int Stack<T>::bracket()
{
	/*Stack <char*> heeelp;
	//char b[2] = { '(', '\0' };
	//char b = '(';
	//char *a = NULL;
	//a = &b;
	//heeelp.push(a);
	//heeelp.line[r_top()] == line[i]
	auto sss = line[i];
	max<char>(line[i],ss) == min<char>(sss, ss)*/

	Stack<int> bra;
	double n[10001];
	int fl = 0, counter = 0;
	string s = "(";
	string s1 = ")";
	for (int i = top; i >= 0; i--)
	{
		if (line[i] == s1)
		{
			bra.push(i);
		}
		if (line[i] == s)
		{
			if (bra.empty() == false)
			{
				n[fl] = i;
				n[fl + 1] = bra.get();
				bra.pop();
				fl = fl + 2;
			}
			else
			{
				cout << i << " нет пары\n";
				counter++;
			}
		}
	}

	for (int i = 0; i < fl; i++)
	{
		cout << n[i] << " ";
		if (i % 2 != 0) cout << endl;
	}
	while (!bra.empty())
	{
		cout << bra.get() << " нет пары\n";
		bra.pop();
	}
	counter += bra.r_top() + 1;
	return counter;
}

int prior(string t)
{
	if (t == "(") return 0;
	if (t == ")") return 1;
	if (t == "+" || t == "-") return 2;
	if (t == "*" || t == "/") return 3;
}

bool checkD(string input_string, double& result)
{
	/*char* end;
	result = strtod(input_string.c_str(), &end);
	if (end == inputString.c_str() || *end != '\0') return false;
	return true;*/

	bool fl = true;
	try
	{
		double value = stod(input_string);
		//std::cout << "Converted string to a value of " << value << std::endl;
	}
	catch (const std::invalid_argument&)
	{
		//std::cerr << "No conversion could be performed" << std::endl;
		fl = false;
	}
	catch (const std::out_of_range&)
	{
		//std::cerr << "Could not convert string to double, value falls out of range" << std::endl;
		fl = false;
	}
	return fl;

}

tra
Stack<T> Stack<T> ::postfix_form()
{
	Stack <char*> ans;
	Stack <char*> help;
	char* s;
	double resalt;
	for (int i = 0; i <= top; i++)
	{
		s = line[i];
		if (checkD(s, resalt))
		{
			ans.push(s);
		}
		else
		{
			if (help.empty() || prior(s) == 0 || (!help.empty() && prior(s) > prior(help.line[help.top]))) help.push(s);
			else
			{
				if ((prior(s) == 1)) {
					while (!help.empty() && prior(help.line[help.top]) != 0)
					{
						ans.push(help.get());
						help.pop();
					}
					help.pop();
				}
				else
				{
					while (!help.empty() && prior(s) <= prior(help.line[help.top]) != 0)
					{
						ans.push(help.get());
						help.pop();
					}
					help.push(s);
				}
			}
		}
	}
	if (!help.empty())
	{
		while (!help.empty())
		{
			ans.push(help.get());
			help.pop();
		}
	}
	Stack <char*> ans2;
	for (int i = ans.top; i >= 0; i--)
	{
		if (prior(ans.line[i]) != 0 && prior(ans.line[i]) != 1) ans2.push(ans.line[i]);
	}
	//ans2.print_stack_as_a_line();
	return ans2;
}

double operation(double o1, double o2, string s)
{
	if (s == "+") return o2 + o1;
	if (s == "-") return o2 - o1;
	if (s == "*") return o2 * o1;
	if (s == "/" && o1 != 0)return o2 / o1;
	else
	{
		cout << "Нельзя делить на ноль\n";
		return (0);
	}
}

tra
double Stack<T> ::calculation(const Stack<T>& st)
{
	Stack <double> help;
	double anss = 0, resalt, op1, op2;
	string s;
	Stack <char*> ans;
	for (int i = st.top; i >= 0; i--)
	{
		ans.push(st.line[i]);
	}
	for (int i = 0; i <= ans.top; i++)
	{
		s = ans.line[i];
		if (checkD(s, resalt))
		{
			help.push(stod(s));
		}
		else
		{
			if (!help.empty())
			{
				op1 = help.get();
				help.pop();
				if (!help.empty())
				{
					op2 = help.get();
					help.pop();
					op2 = operation(op1, op2, s);
					help.push(op2);
				}
			}
			else
			{
				cout << "Стек пуст";
				return (0);
			}
		}
	}
	anss = help.get();
	return anss;
}
// ( ) ( ( ) ) 
// ) ) ) ( )
// -9,5 - 0,5 + 75 * ( 0,1 + 0,1 )
// 8 * ( 2 + 2 - 4 / 2 ) + 1 
// 7 - ( 1 + 2 ) * 3 + 4 / 2



/*

tra
istream& operator>>(istream& ifstr, Stack<T>& b2)
{

	T ch;
	for (int i = 0; i <= b2.r_top(); i++)
	{
		ifstr >> ch;
		//b2.ad(atof(ch));
		b2.push(ch);
	}
	return ifstr;
}

tra
ostream& operator<<(ostream& ofstr, Stack<T>& b2)
{
	for (int i = 0; i <= b2.r_top(); i++)
	{
		ofstr << b2.line[i] << " ";
	}
	return ofstr;
}

//#endif //STACK_H*/

/*
tra
string Stack<T> ::stack_to_line(const Stack<T>& s2)
{
	string s;
	for (int i = top; i >= 0; i++)
	{
		s.push_back(s2.line[i]);
	}
	return s;
}*/
