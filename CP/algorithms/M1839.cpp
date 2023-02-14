#include <ctime>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
struct node{
	int k, p, v, mi, ma;
	bool sorted;
	node * l, * r;
};
#define pnode node *
pnode make(int k, int v){
	pnode x = new node;
	x -> k = k;
	x -> p = rand();
	x -> v = v;
	x -> mi = v;
	x -> ma = v;
	x -> sorted = true;
	x -> l = x -> r = NULL;
	return x;
}
void upd(pnode x){
	if (!x) return;
	x -> mi = x -> v;
	x -> ma = x -> v;
	x -> sorted = true;
	if (x -> l){
		x -> mi = min(x -> mi, x -> l -> mi);
		x -> ma = max(x -> ma, x -> l -> ma);
		x -> sorted = x -> sorted && x -> l -> sorted;
		x -> sorted = x -> sorted && (x -> l -> ma <= x -> v); 
	}
	if (x -> r){
		x -> mi = min(x -> mi, x -> r -> mi);
		x -> ma = max(x -> ma, x -> r -> ma);
		x -> sorted = x -> sorted && x -> r -> sorted;
		x -> sorted = x -> sorted && (x -> v <= x -> r -> mi);
	}
}
void split1(pnode root, int key, pnode &l, pnode &r){
	if (!root){
		l = r = NULL;
	}else if (key < root -> k){
		split1(root -> l, key, l, root -> l);
		r = root;
	}else{
		split1(root -> r, key, root -> r, r);
		l = root;
	}
	upd(l);
	upd(r);
}
void split2(pnode root, int key, pnode &l, pnode &r){
	if (!root){
		l = r = NULL;
	}else if (key <= root -> k){
		split2(root -> l, key, l, root -> l);
		r = root;
	}else{
		split2(root -> r, key, root -> r, r);
		l = root;
	}
	upd(l);
	upd(r);
}
bool check(pnode &root, int k, int v){
	if (!root){
		return false;
	}else{
		bool b;
		if (k < root -> k){
			b = check(root -> l, k, v);
		}else if (k == root -> k){
			b = true;
			root -> v = v;
		}else{
			b = check(root -> r, k, v);
		}
		upd(root);
		return b;
	}
}
void insert(pnode &root, pnode x){
	if (!root){
		root = x;
	}else if (x -> p >= root -> p){
		split1(root, x -> k, x -> l, x -> r);
		root = x;
	}else if (x -> k < root -> k){
		insert(root -> l, x);
	}else{
		insert(root -> r, x);
	}
	upd(root);
}
void join(pnode &root, pnode l, pnode r){
	if (!l){
		root = r;
	}else if (!r){
		root = l;
	}else{
		if (l -> p >= r -> p){
			root = l;
			join(root -> r, l -> r, r);
		}else{
			root = r;
			join(root -> l, l, r -> l);
		}
	}
	upd(root);
}
bool search(pnode root, int value){
	if (!root){
		return false;
	}else if (value < root -> v){
		return search(root -> l, value);
	}else if (value == root -> v){
		return true;
	}else{
		return search(root -> r, value);
	}
}
int main(){
	srand(time(NULL));
	int n;
	scanf("%d", &n);
	pnode treap = NULL;
	for (int i = 0; i < n; i++){
		string s;
		cin >> s;
		if (s == "write"){
			int k, v;
			scanf("%d %d", &v, &k);
			if (!check(treap, k, v)){
				pnode x = make(k, v);
				insert(treap, x);
			}
		}else if (s == "ask"){
			int x, l, r;
			scanf("%d %d %d", &x, &l, &r);
			pnode left = new node;
			pnode mr = new node;
			pnode mid = new node;
			pnode right = new node;
			split2(treap, l, left, mr);
			split1(mr, r, mid, right);
			if (!mid){
				printf("No\n");
			}else if (mid -> sorted){
				if (search(mid, x)){
					printf("Yes\n");
				}else{
					printf("No\n");
				}
			}else{
				printf("No sort, no search\n");
			}
			join(mr, mid, right);
			join(treap, left, mr);
		}
	}
}
