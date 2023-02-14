#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
int key[100000], dis[100000], l[100000], r[100000], root = -1, c = 0;
int merge(int a, int b){
	if (a == -1 && b == -1) return -1;
	if (a == -1) return b;
	if (b == -1) return a;
	if (key[a] > key[b]) swap(a, b);
	r[a] = merge(r[a], b);
	if (r[a] != -1 && dis[r[a]] > dis[l[a]]) swap(l[a], r[a]);
	if (r[a] == -1) dis[a] = 0;
	else dis[a] = dis[r[a]] + 1;
	return a;
}
int main(){
	fill(l, l + 100000, -1);
	fill(r, r + 100000, -1);
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; i++){
		string s;
		cin >> s;
		if (s == "delete"){
			root = merge(l[root], r[root]);
		}else if (s == "extract"){
			printf("%d\n", key[root]);
		}else if (s == "add"){
			scanf("%d", &key[c]);
			root = merge(root, c);
			c++;
		}
	}
}
