#include <bits/stdc++.h>
#define pb push_back
#define MAXN 100010
using namespace std;
typedef long long int ll;

int n;

struct pt
{
	ll x, y, d;
}vet[MAXN];

vector < pt > mat[MAXN];

inline bool cmp1(pt a, pt b)
{
	if(a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

inline bool cmp2(pt a, pt b)
{
	if(a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

inline void comp_coord()
{
	sort(vet, vet+n, cmp2);

	map < ll, int > mapa;

	int cont = 1;
	for(int i = 0 ; i < n ; i++)
	{
		if(!mapa.count(vet[i].y))
		{
			mapa[vet[i].y] = cont++;
			vet[i].y = cont - 1;
		}
		else vet[i].y = mapa[vet[i].y];
	}

	sort(vet, vet+n, cmp1);

	mapa.clear();
	cont = 1;
	for(int i = 0 ; i < n ; i++)
	{
		if(!mapa.count(vet[i].x))
		{
			mapa[vet[i].x] = cont++;
			vet[i].x = cont - 1;
		}
		else vet[i].x = mapa[vet[i].x];
	}
}

ll bit[MAXN];

inline ll query(int y)
{
	ll resp = 0;
	for(int i = y ; i >= 1 ; i -= i&-i) resp = max(resp, bit[i]);
	return resp;
}

inline void update(int y, ll val)
{
	for(int i = y+1 ; i <= MAXN ; i += i&-i) bit[i] = max(bit[i], val);
}

int main()
{
	cin >> n;

	for(int i = 0 ; i < n ; i++)
	{
		cin >> vet[i].x >> vet[i].y >> vet[i].d;
	}

	comp_coord();

	int cont = -1;

	for(int i = 0 ; i < n ; i++)
	{
		if(i == 0 or vet[i].x != vet[i-1].x)
		{
			cont++;
			mat[cont].pb(vet[i]);
		}
		if(i != 0 and vet[i].x == vet[i-1].x)
		{
			if(vet[i].y != vet[i-1].y) mat[cont].pb(vet[i]); 
			else mat[cont][mat[cont].size()-1].d += vet[i].d; //junto os que sao iguais
		}
	}

	ll maior = 0;
	for(int i = 0 ; i <= cont ; i++)
	{
		ll aux[MAXN];
		for(int j = 0 ; j < mat[i].size() ; j++)
		{
			pt v = mat[i][j];
			ll k = query(v.y) + v.d;
			aux[j] = k;
			maior = max(maior, k);
		}
		for(int j = 0 ; j < mat[i].size() ; j++)
		{
			update(mat[i][j].y, aux[j]);
		}
	}
	cout << maior << endl;
}
