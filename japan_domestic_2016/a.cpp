#include <bits/stdc++.h>
using namespace std;

int main(){
	int N;
	while(cin >> N && N ){
		vector<int> a(N);
		for(int i = 0 ; i < N ; i++) cin >> a[i];
		int ans = 2e9;
		for(int i = 0 ; i < N ; i++) 
			for(int j = 0 ; j< N ; j++) 
				if( i != j ) ans = min(ans,abs(a[i]-a[j]));
		cout << ans << endl;
		
	}
}