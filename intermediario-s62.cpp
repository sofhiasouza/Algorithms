#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e5+10;

int n, k, comp[maxn];

int busca(int x)
{
	if(comp[x] == x) return x;
	return comp[x] = busca(comp[x]);
}

void join(int a, int b)
{
	if(a > b) swap(a, b);

	comp[busca(b)] = busca(a);
}

bool ok(int a, int b)
{
	if(busca(a) == busca(b)) return true;
	return false;
}

int main()
{
	cin >> n >> k;

	for(int i = 1 ; i <= n ; i++) comp[i] = i;

	for(int i = 0 ; i < k ; i++)
	{
		char x;
		int a, b;
		cin >> x >> a >> b;

		if(x == 'C')
		{
			if(!ok(a, b)) join(a, b);
		}
		else
		{
			if(!ok(a, b)) cout << "NAO\n";
			else cout << "SIM\n";
		}
	}
}
