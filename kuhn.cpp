#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxn = 155;

int m, n, h[maxn], age[maxn], d[maxn], vist[maxn], tempo, pairs[maxn];

vector < int > grafo[maxn];

bool kuhn(int u)
{
	if(vist[u] == tempo) return false;
	vist[u] = tempo;

	for(int v : grafo[u])
	{
		if(pairs[v] == -1 or kuhn(pairs[v]))
		{
			pairs[v] = u;
			return true;
		}
	}

	return false;
}

int main()
{
	int t, w = 0;
	cin >> t;

	while(t--)
	{
		w++;
		memset(pairs, -1, sizeof pairs);

		cin >> m >> n;

		for(int i = 1 ; i <= m ; i++)
		{
			cin >> h[i] >> age[i] >> d[i];
		}

		for(int i = 51 ; i <= n+50 ; i++)
		{
			cin >> h[i] >> age[i] >> d[i];
		
			for(int j = 1 ; j <= m ; j++)
			{
				if(abs(h[i]-h[j]) <= 12 and abs(age[i]-age[j]) <= 5 and d[i] == d[j])
				{
					grafo[j].pb(i);
				}
			}
		}

		tempo = 1;
		int cont = 0;
		for(int i = 1 ; i <= m ; i++)
		{
			tempo++;
			if(kuhn(i)) cont++;
		}

		cout << "Case " << w << ": " << cont << endl;

		for(int i = 0 ; i < maxn ; i++) grafo[i].clear();
		memset(vist, 0, sizeof vist);
	}
}
