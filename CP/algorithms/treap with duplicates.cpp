#include <ctime>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;
struct node{
	int k, p, s, c;
	node * l, * r;
};
#define pnode node *
pnode make_node(int k){
	pnode x = new node;
	x -> k = k;
	x -> p = rand();
	x -> s = 1;
	x -> c = 1;
	x -> l = x -> r = NULL;
	return x;
}
int get_s(pnode x){
	if (!x){
		return 0;
	}else{
		return x -> s;
	}
}
void upd_s(pnode x){
	if (x){
		x -> s = get_s(x -> l) + get_s(x -> r) + (x -> c);
	}
}
void print(pnode x){
	if (!x) return;
	printf("---------------\nk: %d\np: %d\ns: %d\nc: %d\n", x -> k, x -> p, x -> s, x -> c);
	print(x -> l);
	print(x -> r);
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
bool check(pnode root, int key){
	bool b;
	if (!root){
		return false;
	}else if (key < root -> k){
		b = check(root -> l, key);
	}else if (key == root -> k){
		root -> c++;
		b = true;
	}else{
		b = check(root -> r, key);
	}
	upd_s(root);
	return b;
}
void insert(pnode &root, pnode x){
	if (!root){
		root = x;
	}else if (x -> p >= root -> p){
		split(root, x -> k, x -> l, x -> r);
		root = x;
	}else if (x -> k < root -> k){
		insert(root -> l, x);
	}else{
		insert(root -> r, x);
	}
	upd_s(root);
}
int get_index(pnode root, int key, int ind){
	if (!root){
		return -1;
	}else if (key == root -> k){
		return ind + get_s(root -> l);
	}else if (key < root -> k){
		return get_index(root -> l, key, ind);
	}else{
		return get_index(root -> r, key, ind + get_s(root -> l) + root -> c);
	}
}
int main(){
	srand(time(NULL));
	pnode treap = NULL;
	while (true){
		string s;
		int t;
		cin >> s;
		if (s == "insert"){
			cin >> t;
			if (!check(treap, t)){
				pnode x = make_node(t);
				insert(treap, x);
			}
		}else if (s == "get_index"){
			cin >> t;
			cout << get_index(treap, t, 0) << endl;
		}else if (s == "print"){
			print(treap);
		}
	}
}
