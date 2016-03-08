#include "slot.h"
#include "coord.h"

class board
{
public:
	board();	
	void Solve();
	void AnimateSolve(void(*print)(int row, int col, int num));
	void Print(void (*printer)(int num));
	void Set(int row, int col, int val)
	{
		slot<N> *s = rows[row][col];
		if (!(s->isEmpty()))
			pop(s);
		if (val != 0)
			push(s, val - 1);
	}
	int Get(int row, int col){ return rows[row][col]->getNumber() + 1; }
	static const int N = 9;
	static const int K = 3;
private:
	slot<N> *rows[N][N];
	slot<N> *squares[N][N];

	bool rowContain[N][N];
	bool columnContain[N][N];
	bool squareContain[N][N];


	int currentLevel;

	bool animation;
	void(*print)(int row, int col, int num);

	bool putForced();
	void push(slot<N> *s, int num);
	void pop(slot<N> *s);
	void clearCurrentLevel();
	bool search(coord<N>& cord);
};

inline int squareOf(int r, int c)
{
	return r / board::K * board::K + c / board::K;
}
inline int rowOf(int sq, int n)
{
	return sq / board::K * board::K + n / board::K;
}
inline int cellOf(int r, int c)
{
	return r % board::K * board::K + c % board::K;
}
inline int columnOf(int sq, int n)
{
	return sq % board::K * board::K + n % board::K;
}

board::board()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			rows[i][j] = new slot<N>(i, j, squareOf(i, j));
			squares[squareOf(i, j)][cellOf(i, j)] = rows[i][j];
			rowContain[i][j] = columnContain[i][j] = squareContain[i][j] = false;
		}
	}
	currentLevel = 0;
	animation = false;
}

bool board::putForced()
{
	bool changed = true;
	while (changed)
	{
		changed = false;
		for (int r = 0; r < N; ++r)
		{
			for (int c = 0; c < N; ++c)
			{
				if (rows[r][c]->isEmpty())
				{
					int option = -1, optCount = 0;
					for (int k = 0; k < N; ++k)
					{
						if (rows[r][c]->isLegal(k))
						{
							if (++optCount > 1)
								break;
							option = k;
						}
					}
					if (optCount == 0)
						return false;
					if (optCount == 1)
					{
						push(rows[r][c], option);
						changed = true;
					}
				}
			}
		}
		for (int r = 0; r < N; ++r)
		{
			for (int k = 0; k < N; ++k)
			{
				if (!rowContain[r][k])
				{
					int option = -1, optCount = 0;
					for (int c = 0; c < N; ++c)
					{
						if (rows[r][c]->isLegal(k))
						{
							if (++optCount > 1)
								break;
							option = c;
						}
					}

					if (optCount == 0)
						return false;
					if (optCount == 1)
					{
						push(rows[r][option], k);
						changed = true;
					}
				}
			}
		}
		for (int c = 0; c < N; ++c)
		{
			for (int k = 0; k < N; ++k)
			{
				if (!columnContain[c][k])
				{
					int option = -1, optCount = 0;
					for (int r = 0; r < N; ++r)
					{
						if (rows[r][c]->isLegal(k))
						{
							if (++optCount > 1)
								break;
							option = r;
						}
					}
					if (optCount == 0)
						return false;
					if (optCount == 1)
					{
						push(rows[option][c], k);
						changed = true;
					}
				}
			}
		}
		for (int sq = 0; sq < N; ++sq)
		{
			for (int k = 0; k < N; ++k)
			{
				if (!squareContain[sq][k])
				{
					int option = -1, optCount = 0;
					for (int n = 0; n < N; ++n)
					{
						if (squares[sq][n]->isLegal(k))
						{
							if (++optCount > 1)
								break;
							option = n;
						}
					}
					if (optCount == 0)
						return false;
					if (optCount == 1)
					{
						push(squares[sq][option], k);
						changed = true;
					}
				}
			}
		}
	}
	return true;
}

void board::push(slot<N> *s, int num)
{
	assert(s->isEmpty());
	s->setNumber(num);
	s->setLevel(currentLevel);

	if (animation)
	{
		print(s->getRow(), s->getColumn(), num + 1);
	}

	int r = s->getRow(), c = s->getColumn(), sq = s->getSquare();

	rowContain[r][num] = true;
	columnContain[c][num] = true;
	squareContain[sq][num] = true;

	for (int i = 0; i < N; i++)
	{
		rows[r][i]->incTaboo(num);
		rows[i][c]->incTaboo(num);
		squares[sq][i]->incTaboo(num);
	}
}
void board::pop(slot<N> *s)
{
	int prevNum = s->getNumber();
	s->deleteNum();
	s->setLevel(-1);

	if (animation)
	{
		print(s->getRow(), s->getColumn(), 0);
	}

	int r = s->getRow(), c = s->getColumn(), sq = s->getSquare();

	rowContain[r][prevNum] = false;
	columnContain[c][prevNum] = false;
	squareContain[sq][prevNum] = false;

	for (int i = 0; i < N; i++)
	{
		rows[r][i]->decTaboo(prevNum);
		rows[i][c]->decTaboo(prevNum);
		squares[sq][i]->decTaboo(prevNum);
	}
}

void board::clearCurrentLevel()
{
	for (int r = 0; r < N; ++r)
	{
		for (int c = 0; c < N; ++c)
		{
			if (rows[r][c]->getLevel() == currentLevel)
				pop(rows[r][c]);
		}
	}
}

bool board::search(coord<N>& cord)
{
	if (cord.r >= N)
		return true;

	coord<N>& nextCord = cord.incOne();
	if (!squares[cord.r][cord.c]->isEmpty())
		return search(nextCord);

	currentLevel++;
	for (int i = 0; i < N; ++i)
	{
		if (squares[cord.r][cord.c]->isLegal(i))
		{
			push(squares[cord.r][cord.c], i);
			bool success = putForced() && search(nextCord);
			if (success)
				return true;
			clearCurrentLevel();
		}
	}
	currentLevel--;
	return false;
}

void board::Solve()
{
	putForced();
	currentLevel++;
	search(coord<N>());
	currentLevel--;
}

void board::AnimateSolve(void(*print)(int row, int col, int num))
{
	animation = true;
	this->print = print;
	putForced();
	currentLevel++;
	search(coord<N>());
	currentLevel--;
}

void board::Print(void(*printer)(int num))
{
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < N; ++j)
			printer(rows[i][j]->getNumber() + 1);
	}
}