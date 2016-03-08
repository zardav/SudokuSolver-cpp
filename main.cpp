#include <iostream>
#include <assert.h>
#include "board.h"
using namespace std;


void printer(int num);
void printNumIn(int row, int col, int num);

const int BUFF_S = 81;
int main()
{
	char buff[BUFF_S] = "";
	int N = 9;
	while (strcmp(buff, "exit") != 0)
	{
		cin >> buff;
		if (strcmp(buff, "solve") == 0)
		{
			cin >> buff;
			assert(strlen(buff) == BUFF_S);
			board b = board();
			int cur = 0;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++, cur++)
				{
					int val = buff[cur] >= '1' && buff[cur] <= '9' ? buff[cur] - '0' : 0;
					b.Set(i, j, val);
				}
			}
			b.Solve();
			b.Print(printer);
			cout << endl;
		}
		else if (strcmp(buff, "animate") == 0)
		{
			cin >> buff;
			assert(strlen(buff) == BUFF_S);
			board b = board();
			int cur = 0;
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++, cur++)
				{
					int val = buff[cur] >= '1' && buff[cur] <= '9' ? buff[cur] - '0' : 0;
					b.Set(i, j, val);
				}
			}
			b.AnimateSolve(printNumIn);
		}
	}
	system("pause");
	return 0;
}

void printer(int num)
{
	cout << num;
}
void printNumIn(int row, int col, int num)
{
	cout << row << ' ' << col << ' ' << num << endl;
}
