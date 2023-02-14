#include <ctime>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;
struct node{
	int key, pri;
	node *l, *r;
};
#define pnode node *
void print(pnode root){
	if (!root) return;
	printf("k: %d\np: %d\n", root -> key, root -> pri);
	print(root -> l);
	print(root -> r);
}
void split(pnode root, int key, pnode &l, pnode &r){
	if (!root){
		l = r = NULL;
	}else if (key < root -> key){
		split(root -> l, key, l, root -> l);
		r = root;
	}else{
		split(root -> r, key, root -> r, r);
		l = root;
	}
}
void insert(pnode &root, pnode x){
	if (!root){
		root = x;
	}else if (x -> pri >= root -> pri){
		split(root, x -> key, x -> l, x -> r);
		root = x;
	}else{
		if (x -> key < root -> key){
			insert(root -> l, x);
		}else{
			insert(root -> r, x);
		}
	}
}
void join(pnode &root, pnode l, pnode r){
	if (!l){
		root = r;
	}else if (!r){
		root = l;
	}else{
		if (l -> pri > r -> pri){
			root = l;
			join(root -> r, l -> r, r);
		}else{
			root = r;
			join(root -> l, l, r -> l);
		}
	}
}
void erase(pnode &root, int key){
	if (root == NULL){
		return;
	}else if (root -> key == key){
		join(root, root -> l, root -> r);
	}else{
		if (key < root -> key){
			erase(root -> l, key);
		}else{
			erase(root -> r, key);
		}
	}
}
bool search(pnode root, int key){
	if (!root){
		return false;
	}else if (root -> key == key){
		return true;
	}else if (key < root -> key){
		return search(root -> l, key);
	}else{
		return search(root -> r, key);
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
			x -> key = t;
			x -> pri = rand();
			x -> l = x -> r = NULL;
			insert(treap, x);
		}else if (s == "erase"){
			cin >> t;
			erase(treap, t);
		}else if (s == "search"){
			cin >> t;
			bool b = search(treap, t);
			if (b){
				cout << "exists\n";
			}else{
				cout << "does not exist\n";
			}
		}else if (s == "print"){
			print(treap);
		}
	}
}
