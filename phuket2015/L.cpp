#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
	int n;
	cin >> n;
	int s[3] = {};
	while( n-- ){
		int t[3];
		for(int i = 0 ; i < 3 ; i++) cin >> t[i];
		for(int i = 0 ; i < 3 ; i++) s[i] += t[i];
		if( *min_element(s,s+3) < 30 ) cout << "NO" << endl;
		else {
			int u = *min_element(s,s+3);
			for(int i = 0 ; i < 3 ; i++) s[i] -= u;
			cout << u << endl;
		}
	}
}