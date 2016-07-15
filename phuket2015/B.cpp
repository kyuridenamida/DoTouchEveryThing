#include <bits/stdc++.h>
using namespace std;

signed main(){
	int T;
	cin >> T;
	
	int t = 1;
	while(T--){
		int n,e;
		cin >> n >> e;
		int a[20];
		for(int i = 0 ; i < n ; i++) cin >> a[i];
		sort(a,a+n);
		vector<int> v = {0,0,0};
		for(int i = 0 ; i < (1<<n) ; i++){
			int tot = 0;
			int slv = 0;
			int mx = 0;
			for(int j = 0 ; j < n ; j++){
				if( i >> j & 1 ) 
					slv++, mx += a[j], tot += mx;
			}
			if( mx <= e ) v = min(v,{-slv,tot,mx});
		}
		
		cout << "Case " << t++ << ": " << -v[0] << " " << v[2] << " " << v[1] << endl;
	}
}
