#include <bits/stdc++.h>
using namespace std;
vector<int> adj[100000];
int anc[100000][20], d[100000];
void dfs1(int cur, int par){
	d[cur] = d[par] + 1;
	
	anc[cur][0] = par;
	for (int i = 1; i < 20; i++){
		if (anc[cur][i - 1] == -1) break;
		anc[cur][i] = anc[anc[cur][i - 1]][i - 1];  //split to halves
	}
	
//	for (int e : adj[cur]) dfs(e, cur); 

	for (int i = 0; i < adj[cur].size(); i++){
		int e = adj[cur][i];
		dfs(e, cur);
	}
}

int find_kth_anc(int u, int k){
	int i = 0;
	for (int b = 1; b <= k; b <<= 1){
		if ((k & b) != 0) u = anc[u][i];
		i++;
	}
	return u;
}

int LCA(int x, int y){
	if (d[x] > d[y]) swap(x, y) //assume y is deeper
	
	y = find_kth_anc(y, d[y] - d[x]); //set them to same depth

	if (x == y) return x; //check if already LCA
	
	for (int i = 19; i >= 0; i--){
		if (anc[x][i] == -1) continue;
		if (anc[x][i] != anc[y][i]){
			x = anc[x][i];
			y = anc[y][i];
		}
	}
	
	return anc[x][0]; //return direct parent
}
int main(){
	memset(anc, -1, sizeof anc);   //initialze everything as -1 (represents doesnt exist)
	int n, x, y;
	scanf("%d", &n);
	for (int i = 1; i < n; i++){
		scanf("%d %d", &x, &y), x--, y--;
		adj[x].emplace_back(y), adj[y].emplace_back(x);
	}
	dfs1(0, -1);
}
