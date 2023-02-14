#include <cstdio>
//range sum query with range update (lazy propagation)
int s[400001], a[100000], lazy[400001];
void build(int id, int l, int r){
	if (l == r){
		s[id] = a[l];
		return;
	}
	int mid = (l + r) / 2;
	build(id * 2, l, mid);
	build(id * 2 + 1, mid + 1, r);
	s[id] = s[id * 2] + s[id * 2 + 1];
}
void upd(int id, int l, int r, int x){
	lazy[id] += x;
	s[id] += (r - l + 1) * x;
}
void prop(int id, int l, int r){
	int mid = (l + r) / 2;
	upd(id * 2, l, mid, lazy[id]);
	upd(id * 2 + 1, mid + 1, r, lazy[id]);
	lazy[id] = 0;
}
void update(int id, int l, int r, int L, int R, int x){
	if (r < L || l > R){
		return;
	}else if (L <= l && r <= R){
		upd(id, l, r, x);
		return;
	}
	prop(id, l, r);
	int mid = (l + r) / 2;
	update(id * 2, l, mid, L, R, x);
	update(id * 2, mid + 1, r, L, R, x);
	s[id] = s[id * 2] + s[id * 2 + 1];
}
int query(int id, int l, int r, int L, int R){
	if (r < L || l > R){
		return 0;
	}else if (L <= l && r <= R){
		return s[id];
	}
	prop(id, l, r);
	int mid = (l + r) / 2;
	return query(id * 2, l, mid, L, R) + query(id * 2 + 1, mid + 1, r, L, R);
}
int main(){
	int n, q, x, y, z, w;
	scanf("%d %d", &n, &q);
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	build(1, 0, n - 1);
	for (int i = 0; i < q; i++){
		scanf("%d", &x);
		if (x == 0){
			scanf("%d %d %d", &y, &z, &w);
			update(1, 0, n - 1, y - 1, z - 1, w);
		}else{
			scanf("%d %d", &y, &z);
			printf("%d\n", query(1, 0, n - 1, y - 1, z - 1));
		}
	}
}
