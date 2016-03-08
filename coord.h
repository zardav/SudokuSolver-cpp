template<int N>
class coord
{
public:
	int r, c;
	coord()
	{
		r = c = 0;
	}
	coord(int r, int c)
	{
		this->r = r;
		this->c = c;
	}
	coord incOne()
	{
		return coord(r + (c + 1) / N, (c + 1) % N);
	}
};