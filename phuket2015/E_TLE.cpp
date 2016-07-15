#include <bits/stdc++.h>
using namespace std;
#define int long long
int mod = 1e9+7;

int bpow(int a,int b){
	return b ? bpow(a*a%mod,b/2) * (b&1?a:1)%mod : 1;
}

int c[110];
int s[110];

int f[100100];
int invf[100100];

void init(){
	f[0] = invf[0] = 1;
	for(int i = 1 ; i < 100100 ; i++)
		f[i] = f[i-1] * i % mod;
	//cout << f[10] << endl;
	for(int i = 1 ; i < 100100 ; i++)
		invf[i] = bpow(f[i],mod-2);
	//cout << f[333]*invf[333]%mod << endl;
}

int ncr(int n,int r){
	if( n < r ) return 0;
	return f[n] * invf[n-r] % mod * invf[r] % mod;
}

int dp[1010][110];
int dfs(int k,int d){
	if( s[d] - c[d] < k ) return 0;
	//cout << k << " " << d << endl;
	if( k == 0 ) return 1;
	if( dp[k][d] != -1 ) return dp[k][d];
	long long ans = 0;
	for(int i = 0 ; i <= min(k,c[d-1]) ; i++){
		ans += dfs(k-i,d-1) * ncr(s[d-1]-c[d-1]+i-1,i);
		ans %= mod;
	}

	return dp[k][d] = ans;
}

signed main(){
	ios::sync_with_stdio(false);
	init();
	int T;
	cin >> T;
	int tt = 1;
	while(T--){
		int n,K;
		memset(dp,0,sizeof(dp));
		cin >> n >> K;
		n = 10000;
		K = 1000;
		vector<int> a(n);
		for(int i = 0 ; i < n ; i++) cin >> a[i], a[i] = i / 1000;
		int sz = 0;
		sort(a.begin(),a.end());
		for(int i = 0 ; i < 110 ; i++) c[i] = s[i] = 0;
		for(int i = 0 ; i < n ; ){
			int j = i;
			while( j < n and a[i] == a[j] ) j++;
			c[sz++] = j - i;
			i = j;
		}
		s[0] = c[0];
		for(int i = 1 ; i < 110 ; i++)
			s[i] += s[i-1] + c[i];
		for(int k = 0 ; k <= K ; k++){
			for(int d = 0 ; d <= sz ; d++){
				if( s[d] - c[d] < k ) continue;
				
				if( k == 0 ){
					dp[k][d] = 1;
				}else{
					if( d == 1 ) continue;
					__int128 ans = 0;
					assert(d);
					for(int i = 0 ; i <= min(k,c[d-1]) ; i++){
						ans += dp[k-i][d-1] * ncr(s[d-1]-c[d-1]+i-1,i);
						//ans %= mod;
					}
					dp[k][d] = ans % mod;
					//if(ans==0 ) cout << k << " " << d << endl;
				}
			} 
		}
		

		cout << "Case " << tt++ << ": " << dp[K][sz] << endl;
		//memset(dp,-1,sizeof(dp));
		//cout << dfs(K,sz) << endl;		
		
		
		
	}
}