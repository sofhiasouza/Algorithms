#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int maxn = 220, inf  = 1e9;

int n, m, h[maxn], age[maxn], d[maxn], pairs[maxn], dist[maxn];

vector < int > grafo[maxn];

bool bfs()
{
	queue < int > fila;

	//cout << "bfs:\n";
	for(int i = 1 ; i <= m ; i++)
	{
		if(!pairs[i])
		{
			//cout << i << ' ';
			fila.push(i);
			dist[i] = 0;
		}
		else dist[i] = inf;
	}
	//cout << "\n";

	dist[0] = inf;

	while(fila.size())
	{
		int u = fila.front();
		fila.pop();
		//cout << "U: " << u << endl;
		if(dist[u] < dist[0])
		{
			for(int v : grafo[u])
			{
				//cout << "V: " << v << ' ' << pairs[v] << ' ' << dist[pairs[v]] << endl;
				if(dist[pairs[v]] == inf)
				{
					dist[pairs[v]] = dist[u]+1;
					fila.push(pairs[v]);
				}
			}
		}
	}

	return dist[0] != inf;
}

bool dfs(int u)
{
	if(u != 0)
	{
		for(int v : grafo[u])
		{
			if(dist[pairs[v]] == dist[u]+1 and dfs(pairs[v]))
			{
				//cout << "ligados: " << u << ' ' << v << endl;
				pairs[u] = v;
				pairs[v] = u;
				return true;
			}
		}

		dist[u] = inf;
		return false;
	}
	return true;
}

int hk()
{
	memset(pairs, 0, sizeof pairs);

	int resp = 0;

	while(bfs())
	{
		//cout << "entrei\n";
		for(int i = 1 ; i <= m ; i++)
		{
			if(!pairs[i] and dfs(i)) resp++;
		}
	}

	return resp;
}

int main()
{
	int t, c = 0;
	cin >> t;

	while(t--)
	{
		c++;

		cin >> m >> n;

		for(int i = 1 ; i <= m ; i++)
		{
			cin >> h[i] >> age[i] >> d[i];
		}

		for(int i = 51 ; i <= n+50 ; i++)
		{
			cin >> h[i] >> age[i] >> d[i];
		}

		for(int i = 1 ; i <= m ; i++)
		{
			for(int j = 51 ; j <= n+50 ; j++)
			{
				if(abs(h[i]-h[j]) <= 12 and abs(age[i]-age[j]) <= 5 and d[i] == d[j])
				{
					grafo[i].pb(j);	
					grafo[j].pb(i);
			//		cout << i << ' ' << j << "\n";
				}
			}
		}

//		grafo[3].pb(51);
//		grafo[51].pb(3);
//		grafo[1].pb(52);
//		grafo[52].pb(1);

		int r = hk();

		cout << "Case " << c << ": " << r << "\n";
	
		for(int i = 1 ; i <= m ; i++) grafo[i].clear();
	}
}
