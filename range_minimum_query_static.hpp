template <class T, class U = int>
class RangeMinimumQuery
{
public:
	static const int maxn = 1000000;
	static const int maxh = 20;

	int n;
	T a[maxn];
	U f[maxn][maxh];

	U select(const U & lhs, const U & rhs) const
	{
		return a[lhs] <= a[rhs] ? lhs : rhs;
	}

	RangeMinimumQuery(void)
	{
		clear();
	}

	void clear(void)
	{
		n = 0;
	}

	void resize(const int & n)
	{
		this->n = n;
	}

	void update(const int & i, const bool & rht = false)
	{
		f[i][0] = i;
		if (!rht)
		{
			for (int k = 1, b; (b = 1 << k) <= i + 1; k++)
				f[i + 1 - b][k] = select(f[i + 1 - b][k - 1], f[i + 1 - (b >> 1)][k - 1]);
		}
		else
		{
			for (int k = 1, b; (b = 1 << k) <= n - i; k++)
				f[i][k] = select(f[i][k - 1], f[i + (b >> 1)][k - 1]);
		}
	}

	void push_back(const T & x)
	{
		a[n] = x;
		update(n++, false);
	}

	void build(void)
	{
		for (int i = 0; i < n; i++)
			update(i, false);
	}

	U query(const int & l, const int & r) const
	{
		int k = 31 - __builtin_clz(r - l);
		return select(f[l][k], f[r - (1 << k)][k]);
	}
};

