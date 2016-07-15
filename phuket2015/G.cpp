#include <bits/stdc++.h>
using namespace std;
#define int long long

vector<long long> X[64];
int mod = 1e9 + 7;
int lim = 1e14;
int bpow(int a,int b){
	return b ? bpow(a*a%mod,b/2) * (b&1?a:1)%mod : 1;
}

int bpow2(int a,int b){
	return b ? bpow2(a*a,b/2) * (b&1?a:1) : 1;
}

bool isp[10000150];

signed main(){
	int t = 0;	
	for(int i = 0 ; i < 10000150 ; i++) isp[i] = true;
	isp[0] = isp[1] = false;
	vector<int> p;
	for(int i = 0 ; i < 10000150 ; i++){
		if( isp[i] ){
			p.push_back(i);
			for(int j = i*i ; j < 10000150 ; j += i)
				isp[j] = false;
		}
	}
	
	for(int i = 2 ; i < 60 ; i++){
		int u;
		long long ml = 1;

		int x = pow(lim,1./i);
		//cout << x << " " << i << ":= " << bpow2(x,i) << endl;
		while( pow(x+1,i) < 1e15 and bpow2(x+1,i) <= lim ) x++;
		while( bpow2(x,i) > lim ) x--;
		//cout << bpow2(x,i) << endl;
		X[i].resize(x+1,1ll);
		for(int j_ = 0 ; (u=bpow2(p[j_],i-1), u*p[j_] <= lim) and pow(p[j_],i) <= 1e15 ; j_++){
			//cout << i << "|" << u*p[j_] << "|" << lim << endl;
			if( p[j_] > x ) cout << "><" << x << " " << p[j_] << "(" << i << ")" << endl;
			X[i][p[j_]] = u % mod;
		}
		for(int j = 1 ; j < X[i].size() ; j++){
			X[i][j] *= X[i][j-1];
			X[i][j] %= mod;
		}
		
			
		//cout << u << " " << x << endl;
		
		//cout << "OK" << endl;
	}
	int T;
	cin >> T;
	while(T--){
		int n;
		scanf("%lld",&n);
		int v[60] = {};
		for(int i = 2 ; i < 51 ; i++){
			int x = pow(n,1./i);
			while( pow(x+1,i) < 1e15 and bpow2(x+1,i) <= n ) x++;
			while( bpow2(x,i) > n ) x--;
			v[i] = x;
		}
		long long ans = 1;
		for(int i = 2 ; i < 51 ; i++){
			int u = v[i];
			int l = v[i+1];
			if( u == l ) continue;
			ans *= X[i][u];
			ans %= mod;
			ans *= bpow(X[i][l],mod-2);
			ans %= mod;
		}
		printf("Case %lld: %lld\n",++t,ans);
	}
}