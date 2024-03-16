#include <iostream>
#include "Stack.h"
#include <conio.h>

using namespace std;


int main()
{
	setlocale(LC_ALL, "");
	Stack<char*> st;
	char c;

	cout << "Пожалуйста, введите пример\n";
	do
	{
		char* s = new char[100];
		cin >> s;
		st.push(s);
		//if (j = _getch() == 13)break;
	} while (cin.read(&c, 1) && c != '\n');


	//st.print_stack();
	int de = st.bracket();
	if (de != 0) cout << "\nОшибок со скобками " << de << "\n";

	else
	{

		Stack<char*> post;
		post = st.postfix_form();
		post.print_stack_as_a_line();
		cout << "\nОшибок со скобками нет\n";
		if (post.calculation(post))
		{
			cout << "Постфиксная форма \n";
			post.print_stack_as_a_line();
			double ans = post.calculation(post);
			cout << "Решение " << ans << endl;
		}
	}
}
