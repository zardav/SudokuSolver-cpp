template<int N>
class slot
{
	const int row, col, square;
	int number;
	int level;
	int taboo[N];
public:
	slot(int row, int col, int square) : row(row), col(col), square(square)
	{

		number = -1;
		level = -1;
		for (int i = 0; i < N; ++i)
			taboo[i] = 0;
	}
	void setNumber(int num){ number = num; }
	int getNumber() { return number; }

	int getRow(){ return row; }
	int getColumn(){ return col; }
	int getSquare(){ return square; }

	bool isEmpty() { return number == -1; }
	void deleteNum() { number = -1; }

	void setLevel(int level) { this->level = level; }
	int getLevel() { return level; }

	void incTaboo(int num) { taboo[num]++; }
	void decTaboo(int num) { taboo[num]--; }
	bool isLegal(int num) { return number == -1 && taboo[num] == 0; }
};