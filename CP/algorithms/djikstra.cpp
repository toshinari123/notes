#include <queue>
#include <cstdio>
#include <vector>
using namespace std;
#define d first
#define x second
#define pii pair<int, int>
vector<pii> adj[100000];
int n, m, d[100000];
void input(){
	int x, y, z;
	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++){
		scanf("%d %d %d", &x, &y, &z);
		adj[x - 1].emplace_back(z, y - 1);
		adj[y - 1].emplace_back(z, x - 1);
	}
}
void djikstra(int s){
	fill(d, d + n, -1);
	d[s] = 0;
	priority_queue<pii, vector<pii>, greater<pii> > pq;
	pq.emplace(d[s], s);
	while (!pq.empty()){
		pii cur = pq.top();
		pq.pop();
		for (auto e : adj[cur.x]){
			if (d[e.x] == -1 || d[e.x] > d[cur.x] + e.d){
				d[e.x] = d[cur.x] + e.d;
				pq.emplace(d[e.x], e.x);
			}
		}
	}
}
int main(){
	input();
	djikstra(0);
	for (int i = 0; i < n; i++) printf("%d ", d[i]);
}
