#include <ctime>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;
struct node{
	int k, p, s;
	node * l, * r;
};
#define pnode node *
int get_s(pnode x){
	if (!x){
		return 0;
	}else{
		return x -> s;
	}
}
void upd_s(pnode x){
	if (x) x -> s = get_s(x -> l) + get_s(x -> r) + 1;
}
void print(pnode root){
	if (!root) return;
	printf(" k: %d\np: %d\ns: %d\n", root -> k, root -> p, root -> s);
	print(root -> l);
	print(root -> r);
}
void split(pnode root, int key, pnode &l, pnode &r){
	if (!root){
		l = r = NULL;
	}else if (key < root -> k){
		split(root -> l, key, l, root -> l);
		r = root;
	}else{
		split(root -> r, key, root -> r, r);
		l = root;
	}
	upd_s(l);
	upd_s(r);
}
void insert(pnode &root, pnode x){
	if (!root){
		root = x;
	}else if (x -> p >= root -> p){
		split(root, x -> k, x -> l, x -> r);
		upd_s(x);
		root = x;
	}else if (x -> k < root -> k){
		insert(root -> l, x);
		upd_s(root);
	}else{
		insert(root -> r, x);
		upd_s(root);
	}
}
void join(pnode &root, pnode l, pnode r){
	if (!l){
		root = r;
	}else if (!r){
		root = l;
	}else if (l -> p >= r -> p){
		root = l;
		join(root -> r, l -> r, r);
		upd_s(root);
	}else{
		root = r;
		join(root -> l, l, r -> l);
		upd_s(root);
	}
}
void erase(pnode &root, int key){
	if (root == NULL){
		return;
	}else if (root -> k == key){
		join(root, root -> l, root -> r);
		upd_s(root);
	}else if (key < root -> k){
		erase(root -> l, key);
		upd_s(root);
	}else{
		erase(root -> r, key);
		upd_s(root);
	}
}
pnode get_kth(pnode root, int k){
	int ls = get_s(root -> l);
	if (k < ls){
		return get_kth(root -> l, k);
	}else if (k == ls){
		return root;
	}else{
		return get_kth(root -> r, k - ls - 1);
	}
}
int get_index(pnode root, int key, int ind){
	if (!root){
		return -1;
	}else if (key < root -> k){
		return get_index(root -> l, key, ind);
	}else if (key == root -> k){
		return ind + get_s(root -> l);
	}else{
		return get_index(root -> r, key, ind + get_s(root -> l) + 1);
	}
}
int main(){
	srand(time(NULL));
	pnode treap;
	treap = NULL;
	while (true){
		string s;
		cin >> s;
		int t;
		if (s == "insert"){
			cin >> t;
			pnode x = new node;
			x -> k = t;
			x -> p = rand();
			x -> s = 1;
			x -> l = x -> r = NULL;
			insert(treap, x);
		}else if (s == "erase"){
			cin >> t;
			erase(treap, t);
		}else if (s == "get_kth"){
			cin >> t;
			pnode res = get_kth(treap, t);
			cout << res -> k << endl;
		}else if (s == "get_index"){
			cin >> t;
			cout << get_index(treap, t, 0) << endl;
		}else if (s == "print"){
			print(treap);
		}
	}
}
