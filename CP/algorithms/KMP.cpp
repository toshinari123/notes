#include <cstdio>
#include <string>
#include <iostream>
using namespace std;
int main(){
	string s, t;
	getline(cin, s);
	getline(cin, t);
	int n = s.size(), m = t.size();
	int pos = 0, cur = 1, lps[m];
	lps[0] = 0;
	while (cur < m){
		if (t[pos] == t[cur]){
			pos++;
			lps[cur] = pos;
			cur++;
		}else{
			if (pos == 0){
				lps[cur] = 0;
				cur++;
			}else{
				pos = lps[pos - 1];
			}
		}
	}
	cur = 0, pos = 0;
	while (cur < n){
		if (s[cur] == t[pos]){
			cur++, pos++;
			if (pos == m){
				printf("found %d\n", cur - m);
				pos = lps[pos - 1];
			}
		}else{
			if (pos == 0){
				cur++;
			}else{
				pos = lps[pos - 1];
			}
		}
	}
}
