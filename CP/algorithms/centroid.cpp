#include <cstdio>
#include <vector>
using namespace std;
vector<int> a[100000];
int sz[100000];
bool cened[100000];
void dfs(int c, int p){
	sz[c] = 1;
	for (int e : a[c]){
		if (cened[e] || e == p) continue;
		dfs(e, c);
		sz[c] += sz[e];
	}
}
int cen(int v, int h, int p){
	int big = -1, ma = -1;
	for (int e : a[v]){
		if (cened[e] || e == p) continue;
		if (sz[e] > ma) big = e, ma = sz[e];
	}
	if (ma <= h) return v;
	return cen(big, h, v);
}
void solve(int v){
	dfs(v, -1);
	int c = cen(v, sz[v] / 2, -1);
	cened[c] = true;
	//solve 
	for (int e : a[c]){
		if (!cened[e]) solve(e);
	}
}
int main(){
	int n, x, y;
	scanf("%d", &n);
	for (int i = 1; i < n; i++){
		scanf("%d %d", &x, &y);
		a[x - 1].emplace_back(y - 1);
		a[y - 1].emplace_back(x - 1);
	}
	solve(0);
}
