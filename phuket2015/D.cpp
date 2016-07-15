#include <bits/stdc++.h>
using namespace std;
#define int long long

int uf[100010];
int root(int x){
	return x == uf[x] ? x : uf[x] = root(uf[x]);
}


int id(int i,int j,int k){
	return i * 100 * 2 + j * 2 + k;
}

int unite(int x,int y){
	x = root(x);
	y = root(y);
	if( x == y ) return 0;
	if( rand() & 1 ) swap(x,y);
	uf[x] = y;
	return 1;
}
char f[110][110];

signed main(){
	int T;
	cin >> T;
	int t = 0;
	while(T--){
		for(int i = 0 ; i < 100010 ; i++) uf[i] = i;
		
		int R,C;
		cin >> R >> C;
		for(int i = 0 ; i < R ; i++){
			for(int j = 0 ; j < C ; j++){
				cin >> f[i][j];
			}
		}
		
		vector< array<int,3> > es;
		for(int i = 0 ; i < R ; i++){
			for(int j = 0 ; j < C ; j++){
				if(i+1<R){
					if( f[i][j] == '/' and f[i+1][j] == '/' ) es.push_back({0,id(i,j,1),id(i+1,j,0)});
					if( f[i][j] == '/' and f[i+1][j] == '\\' ) es.push_back({0,id(i,j,1),id(i+1,j,1)});
					if( f[i][j] == '\\' and f[i+1][j] == '\\' ) es.push_back({0,id(i,j,0),id(i+1,j,1)});
					if( f[i][j] == '\\' and f[i+1][j] == '/' ) es.push_back({0,id(i,j,0),id(i+1,j,0)});
				}
				if(j+1<C){
					if( f[i][j] == '/' and f[i][j+1] == '/' ) es.push_back({0,id(i,j,1),id(i,j+1,0)});
					if( f[i][j] == '/' and f[i][j+1] == '\\' ) es.push_back({0,id(i,j,1),id(i,j+1,0)});
					if( f[i][j] == '\\' and f[i][j+1] == '\\' ) es.push_back({0,id(i,j,1),id(i,j+1,0)});
					if( f[i][j] == '\\' and f[i][j+1] == '/' ) es.push_back({0,id(i,j,1),id(i,j+1,0)});
				}
			}
		}
		for(int i = 0 ; i < R ; i++){
			for(int j = 0 ; j < C ; j++){
				int x;
				cin >> x;
				if( f[i][j] == '/' ) es.push_back({x,id(i,j,0),id(i,j,1)});
				if( f[i][j] == '\\' ) es.push_back({x,id(i,j,0),id(i,j,1)});
			}
		}
		sort(es.begin(),es.end());
		int ans = 0;
		for( auto e : es ){
			//cout << e[0] << "=" << e[1] << " " << e[2] << endl;
			ans += unite(e[1],e[2]) * e[0];
		}
		cout << "Case " << ++t << ": " << ans << endl;

	}
}