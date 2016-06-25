#include <bits/stdc++.h>
using namespace std;


int d[10000010];

int check(int n){

	for(int i = 2 ; i * i <= n ; i++)
		if( n % i == 0 ){
			if( d[n/i] ) return true;
			if( d[i] ) return true;
		}
	return false;
}
void insert(int n){
	//cout << n << " inserted" << endl;
	d[n] = true;
}
int main(){
	int m,n;
	while(cin >> m >> n and m ){
		memset(d,0,sizeof(d));
		//__gcd(a,b)
		long long p = m;
		long long c = m+1;
		insert(m);
		for(int i=0; i < n ; i++){
			while( check(c) ) c++;
			//cout << i << ": " << c << endl;
			insert(c);
			c++;
		}
		cout << c-1 << endl;

	}
}