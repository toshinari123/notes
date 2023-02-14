#include <cstdio>
int main(){
	printf("Find square root of N using O(log N) time. Input -1 to exit.\n");
	while (true){
		int n;
		scanf("%d", &n);
		if (n == -1){
			break;
		}
		double l = 0, r = n;
		while (r - l > 0.0000001){
			double mid = l + (r - l) / 2;
			if (mid * mid > n){
				r = mid;
			}else{
				l = mid;
			}
		}
		printf("%.6lf\n\n", l);
	}
}
