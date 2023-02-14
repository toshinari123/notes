#include <cstdio>
#include <vector>
using namespace std;
int main(){
	int n;
	scanf("%d", &n);
	int mobius[n + 1];
	bool is_prime[n + 1];
	vector<int> prime;
	for (int i = 2; i <= n; i++){
		mobius[i] = 0;
		is_prime[i] = true;
	}
	mobius[1] = 1;
	is_prime[1] = false;
	for (int i = 2; i <= n; i++){
		if (is_prime[i]){
			mobius[i] = -1;
			prime.push_back(i);
		}
		for (int j = 0; j < prime.size() && i * prime[j] <= n; j++){
			is_prime[i * prime[j]] = false;
			if (i % prime[j] == 0){
				break;
			}else{
				mobius[i * prime[j]] = -mobius[i];
			}
		}
	}
	for (int i = 1; i <= n; i++){
		printf("%d: %d\n", i, mobius[i]);
	}
}
