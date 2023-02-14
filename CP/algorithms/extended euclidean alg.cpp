#include <bits/stdc++.h>
using namespace std;
int gcd(int a, int b, int &x, int &y){		//a < b
	if (a == 0){
		x = 0, y = 1;
		return b;
	}
	int xx, yy, g = gcd(b % a, a, xx, yy);
	x = yy - b / a * xx, y = xx;
	return g;
}
int main(){
	while (true){
		int a, b, x, y;
		scanf("%d %d", &a, &b);
		int g = gcd(a, b, x, y);
		printf("%d %d %d\n", g, x, y);
	}
}
/*
p[i] = b[i] / a[i];
a[i] = b[i - 1] - p[i - 1] * a[i - 1], b[i] = a[i - 1];

base case: a[0] = a, b[0] = b

iterate from small to big i to find the a[i]s and the b[i]s
when a[i] is 0, gcd is found and is b[i]

a[i] * x[i] + b[i] * y[i] = gcd

x[i] = y[i + 1] - p[i] * x[i + 1], y[i] = x[i + 1];

base case: x[m] = 0, y[m] = 1    (where a[m] == 0)

iterate back from big to small i to find the x[i]s and the y[i]s
the final result get a * x + b * y == gcd
*/
