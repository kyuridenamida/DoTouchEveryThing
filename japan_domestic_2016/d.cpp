#include <bits/stdc++.h>
using namespace std;

int w[310];
int dp[310][310];

map< vector<int> , int > memo;
int naive(vector<int> a){
	if( memo.count(a) ) return memo[a];
	int ans = 0;
	if( a.size() % 2 == 1 ) return 0;
	if( a.size() == 0 ) return 1;
	for(int i = 0 ; i < a.size() - 1 ; i++){
		if( abs(a[i]-a[i+1]) > 1 ) continue;
		vector<int> b = a;
		b.erase(b.begin()+i+1);
		b.erase(b.begin()+i);
		ans |= naive(b);
	}

	return memo[a] = ans;


}
int dfs(int l,int r){
	//return naive(vector<int>(w+l,w+r+1));
	if( l > r ) return 1;
	if( r - l == 0 ) return 0;
	if( r - l == 1 ) return abs(w[r]-w[l]) <= 1;
	if( dp[l][r] != -1 ) return dp[l][r];
	int A = dfs(l+1,r-1) and abs(w[r]-w[l]) <= 1;
	int B = dfs(l+2,r) and abs(w[l+1]-w[l]) <= 1;
	int C = dfs(l,r-2) and abs(w[r]-w[r-1]) <= 1;
	int D = 0;
	for(int i = l+1 ; i < r ; i++)
		D |= dfs(l,i) and dfs(i+1,r);
	return dp[l][r] = A or B or C or D;
}

int dp2[310];
int N;
int dfs2(int x){
	if( x == N ) return 0;
	if( dp2[x] != -1 ) return dp2[x];
	int ans = dfs2(x+1);
	for(int i = x ; i < N ; i++)
		if( dfs(x,i) ) 
			ans = max(ans,dfs2(i+1)+i-x+1);
	return dp2[x] = ans;
}



int main(){
	memo.clear();
	/*while(true){
		int n = rand() % 20 + 1;
		vector<int> a;
		N = n;
		for(int i = 0 ; i < n ; i++) a.push_back(rand() % 3), w[i] = a[i];

		memset(dp,-1,sizeof(dp));
		memset(dp2,-1,sizeof(dp2));
		if( dfs(0,n-1) != naive(a) ){
			cout << dfs(0,n-1) << " " << naive(a) << endl;
			for(int i = 0 ; i < n ; i++) cout << a[i] << " ";
			cout << endl;
			cout << "><" << endl;
			for(int i = 0 ; i < n ; i++)
				for(int j = i ; j < n ; j++)
					if( dfs(i,j) ) cout << i << " " << j << endl;
			cout << endl;

			return 0;
		}


	}*/
	
	while(cin >> N && N ){
		memo.clear();
		memset(dp,-1,sizeof(dp));
		memset(dp2,-1,sizeof(dp2));
		for(int i = 0 ; i < N ; i++) cin >> w[i];
		cout << dfs2(0) << endl;

	}
}